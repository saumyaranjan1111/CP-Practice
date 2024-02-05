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
ll mod_div(ll a, ll b, ll m) {a = a % m; b = b % m; return mod_mul(a, expo(b, m-2, m), m) % m;}

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
    ll t;
    cin>>t;
    while(t--){
        ll n, m; cin>>n>>m;
        vector<ll> a(n);
        for(ll i = 0; i<n; i++) cin>>a[i];
        sort(all(a));

        map<ll, ll> mp;
        for(auto x: a){
            mp[x]++;
        }

        vector<ll> b;
        for(auto it = mp.begin(); it!= mp.end(); it++){
            b.pb(it->first);
        }

        vector<ll> preprod(b.size());
        preprod[0] = mp[b[0]];
        for(ll i = 1; i<m; i++){
            preprod[i] = max(1LL, mod_mul(preprod[max(0LL, i-1)], mp[b[i]], MOD));
        }
        for(ll i = m; i<b.size(); i++){
            preprod[i] = max(1LL, mod_mul(mod_div(preprod[max(0LL, i-1)], mp[b[max(0LL, i-m)]], MOD), mp[b[i]], MOD));
        }

        n = b.size();
        if(n == 1){
            if(m>1) cout<<0<<endl;
            else cout<<b[0]<<endl;

            continue;
        }

        ll ans = 0;
        ll l = 0, r = 1;
        while(r<n){
            r = max(r, l+1);
            while(r<n && r-l<m && b[r]-b[l]<m){
                r++;
            }
            ll curr = preprod[r-1];
            if(r-l == m && b[r-1] - b[l] < m){
                ans = mod_add(ans, curr, MOD);
            }
            l++;
        }
        cout<<ans%MOD<<endl;
    }
}
 
signed main() {
    fastio();
    solve();
}