//headers 
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

typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll getRandomNumber(ll l, ll r) {return uniform_int_distribution<ll>(l, r)(rng);} 
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}

void _print(vector<ll> &arr){for(auto &x:arr)cout<<x<<" ";cout<<endl;}

void djikstra(ll root, vector<vector<pair<ll, ll>>>& graph, vector<ll> &dist){
    priority_queue <pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;

    pq.push({0, root});
    dist[root] = 0;
    while(!pq.empty()){
        ll pathwt = pq.top().first;
        ll node = pq.top().second;
        pq.pop();
        for(auto child : graph[node]){
            ll childnode = child.first;
            ll edgewt = child.second;

            if(dist[childnode] > dist[node] + edgewt){
                dist[childnode] = dist[node] + edgewt;
                pq.push({dist[childnode], childnode});
            }
        }
    }
}
/*--------------------------------------------------------------------------------------------------------------------------*/
bool check(ll mid, vector<ll> &a, ll k, vector<ll> &suffixsum){
    // can sum(a) <= k in atmost mid operations?
    // both operations should total to mid no of operations
    ll n = a.size();
    ll sum = 0;
    for(auto x:a) sum+=x;

    ll first_op = 0, second_op = min(n-1, mid-first_op);
    
    for(; first_op<=mid; first_op++){
        
        second_op = min(n-1, mid-first_op);

        ll newsum = sum - first_op - suffixsum[n - second_op] + second_op*(a[0] - first_op);

        if(newsum <= k) {
            return true;
        }
    }
    
    return false;
}
void solve(){
    ll t;
    cin>>t;
    for(ll test = 0; test<t; test++){
        
        ll n, k; cin>>n>>k;
        vector<ll> a(n);
        for(ll i = 0; i<n; i++) cin>>a[i];
        ll sum = 0;
        for(auto x:a) sum+=x;
        sort(a.begin(), a.end());
        
        // if(test + 1 == 929){
        //     // cout<<"#"<<test + 1<<":";
        //     // cout<<n;
        //     for(auto x:a) cout<<x<<0;
        //     cout<<k<<endl;
        // }

        vector<ll> suffixsum(n+1, 0);
        for(ll i = n-1; i>=0; i--){
            suffixsum[i] = suffixsum[i+1] + a[i];
        }
        if(sum <= k) {
            cout<<0<<endl;
            continue;
        } else {
            ll low = 0, high = INF;
            ll ans = high;
            while(low <= high){
                ll mid = low + (high - low)/2;
                if(check(mid, a, k, suffixsum)){
                    ans = mid; 
                    high = mid-1;
                } else {
                    low = mid+1;
                }
            }
            cout<<ans<<endl;
        }
    }
}
 
signed main() {
    fastio();
    solve();
}