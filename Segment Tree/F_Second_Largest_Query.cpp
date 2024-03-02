// https://atcoder.jp/contests/abc343/tasks/abc343_f

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

#define endl "\n"
#define fastio() ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define MOD 1000000007
#define MOD1 998244353
#define INF 1e18
#define pb push_back
#define ppb pop_back
#define mp make_pair
#define ff first
#define ss second
#define PI 3.141592653589793238462
#define set_bits(x) __builtin_popcountll(x)
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()

using namespace std;
using namespace chrono;
using namespace __gnu_pbds;
using ll = long long;
using ull = unsigned long long;
using lld = long double;

typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll getRandomNumber(ll l, ll r) {return uniform_int_distribution<ll>(l, r)(rng);} 
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}

void _print(vector<ll> &arr){for(auto &x:arr)cout<<x<<" ";cout<<endl;}
/*--------------------------------------------------------------------------------------------------------------------------*/
// segment tree (point update type) + pbds + binary search
ll maxN = 2e5;
vector<pair<ll, ll>> t(4*maxN);

void build(vector<ll> &a, ll v, ll tl, ll tr){
    if(tl == tr){
        t[v] = {a[tl], 0};
    } else {
        ll tm = (tl + tr)/2;
        build(a, v*2 + 1, tl, tm);
        build(a, v*2 + 2, tm+1, tr);

        set<ll> temp; auto left = t[v*2 + 1]; auto right = t[v*2 + 2]; 
        temp.insert(left.first); temp.insert(left.second); temp.insert(right.first); temp.insert(right.second);

        auto it = temp.end(); it--;
        ll maxi = *it;
        ll mini = 0;
        if(temp.size() > 1){
            it--; 
            mini = *it;
        }
        t[v] = {maxi, mini};
    }
}

pair<ll, ll> seclargest(ll v, ll tl, ll tr, ll l, ll r){
    if(l > r){
        return {0, 0};
    }
    if(l == tl && r == tr){
        return t[v];
    }
    ll tm = (tl + tr)/2;
    
    auto left = seclargest(v*2 + 1, tl, tm, l, min(r, tm));
    auto right = seclargest(v*2 + 2, tm+1, tr, max(l, tm+1), r);

    set<ll> temp;
    temp.insert(left.first); temp.insert(left.second); temp.insert(right.first); temp.insert(right.second);

    auto it = temp.end(); it--;
    ll maxi = *it;
    ll mini = 0;
    if(temp.size() > 1){
        it--; 
        mini = *it;
    }
    return {maxi, mini};
}

void update(ll v, ll tl, ll tr, ll pos, ll new_val, vector<ll> &a){
    if(tl == tr){
        t[v] = {new_val, 0};
        a[pos] = new_val;
    } else {
        ll tm = (tl + tr)/2;
        if(pos <= tm){
            update(v*2 + 1, tl, tm, pos, new_val, a);
        } else {
            update(v*2 + 2, tm+1, tr, pos, new_val, a);
        }
        
        set<ll> temp; auto left = t[v*2 + 1]; auto right = t[v*2 + 2]; 
        temp.insert(left.first); temp.insert(left.second); temp.insert(right.first); temp.insert(right.second);

        auto it = temp.end(); it--;
        ll maxi = *it;
        ll mini = 0;
        if(temp.size() > 1){
            it--; 
            mini = *it;
        }
        t[v] = {maxi, mini};
        a[pos] = new_val;
    }
}

void solve(){
    ll n, q; cin>>n>>q;
    vector<ll> a(n); 
    for(ll i = 0; i<n; i++) cin>>a[i];

    // the segment tree will contain the pair{max, secondmax} for any range l to r, 
    // t[0] : contains the {max, secondmax} for the range 0, to n-1(i.e. the whole array)
    build(a, 0, 0, n-1);

    // freqs[val] stores the indices where the val is present in the array
    map<ll, pbds> freqs;
    for(ll i = 0; i<n; i++){
        freqs[a[i]].insert(i);
    }

    for(ll i = 0; i<q; i++){
        ll query; cin>>query;
        if(query == 1){
            // update
            ll pos, new_val; cin>>pos>>new_val;
            pos--;

            // remove the current index from the indices list of the current value present at pos
            auto &st = freqs[a[pos]];
            st.erase(st.find(pos));

            // perform a point update to indicate the new value that has now been placed at pos
            update(0, 0, n-1, pos, new_val, a);

            // add this index to the indices list of the new_val
            auto &st2 = freqs[new_val];
            st2.insert(pos);
        } else {
            // find the frequency of the secondlargest element in the range l to r
            ll l, r; cin>>l>>r;
            l--; r--;

            // num contains the {max, secondmax} in the range l to r
            auto num = seclargest(0, 0, n-1, l, r);
            // val : secondmax
            ll val = num.second;
            auto &indices = freqs[val];

            // on the indices of val, find how many times is val present within the indices l and r
            ll big = indices.order_of_key(r+1);
            // big : order_of_key(r+1): no of indices strictly less than r+1
            ll small = indices.order_of_key(l);
            // small : no of indices less than l

            // big - small contains the no of indices where val is present
            cout<<big-small<<endl;
        }
    }
}
 
signed main() {
    fastio();
    solve();
}