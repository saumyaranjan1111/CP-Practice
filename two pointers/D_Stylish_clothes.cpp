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

void solve(){
    ll n1, n2, n3, n4;
    
    set<pair<ll,ll>> st;
    cin>>n1;
    for(ll i = 0; i<n1; i++){
        ll x; cin>>x;
        st.insert({x, 0});
    }
    cin>>n2;
    for(ll i = 0; i<n2; i++){
        ll x; cin>>x;
        st.insert({x, 1});
    }
    cin>>n3;
    for(ll i = 0; i<n3; i++){
        ll x; cin>>x;
        st.insert({x, 2});
    }
    cin>>n4;
    for(ll i = 0; i<n4; i++){
        ll x; cin>>x;
        st.insert({x, 3});
    }

    vector<pair<ll, ll>> all;
    for(auto it = st.begin(); it!= st.end(); it++){
        all.pb(*it);
    }

    ll l = 0, r = 0;
    ll n = all.size();
    map<ll, ll> typesize;
    // vector<ll> ans;
    pair<ll, ll> finalinds = {0, n-1};
    ll res = all[n-1].first - all[0].first;
    while(l<n){
        while(r<n && typesize.size() < 4){
            typesize[all[r].second]++;
            r++;
        }

        if(typesize.size() == 4 && all[r-1].first - all[l].first < res){
            res = all[r-1].first - all[l].first;
            finalinds = {l, r-1};
        }

        typesize[all[l].second]--;
        if(typesize[all[l].second] == 0) typesize.erase(all[l].second);

        l++;
    }

    vector<ll> ans(4);
    l = finalinds.first;
    r = finalinds.second;
    ll count = 0;

    for(ll i = l; i<=r; i++){
        ans[all[i].second] = all[i].first;
    }
    _print(ans);
}
 
signed main() {
    fastio();
    solve();
}