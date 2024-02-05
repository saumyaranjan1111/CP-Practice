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
void _print(vector<double> &arr){for(auto &x:arr)cout<<x<<" ";cout<<endl;}

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

ll check(ll mid, vector<double> &vals, vector<ll> &p){
    ll money = 0;
    multiset<double> st;
    for(ll i = 0; i<mid; i++){
        st.insert(-vals[i]);
    }

    ll ind = 0;
    for(auto it = st.begin(); it!= st.end(); it++){
        // cout<<-(*it)<<" "<<p[ind]<<endl;
        money += -(*it)*p[ind];
        ind++;
    }

    return money;
}
void solve(){
    ll t;
    cin>>t;
    while(t--){
        ll n; cin>>n;
        vector<ll> p(n);
        for(ll i = 0; i<n; i++) cin>>p[i];

        vector<double> vals(n, 0);
        ll x, a;
        cin>>x>>a;
        
        ll y, b;
        cin>>y>>b;
        
        ll k; 
        cin>>k;

        for(ll i = a-1; i<n; i+=a){
            vals[i] += (double)x/(double)100;
        }

        for(ll i = b-1; i<n; i+=b){
            vals[i] += (double)y/(double)100;
        }

        sort(p.begin(), p.end(), greater<ll>());
        // _print(p);
        // _print(vals);

        ll low = 1, high = n; 
        ll ans = n+1;
        while(low<=high){
            ll mid = low + (high - low)/2;
            // cout<<"mid"<<endl;
            // cout<<low<<" "<<mid<<" "<<high<<endl;
            // cout<<check(mid, vals, p)<<endl;
            if(check(mid, vals, p) < k){
                // check(mid) : how much max value can we get if we sell mid tickets in an optimal way
                // we need to sell more tickets than mid
                low = mid+1;
            }
            else {
                // these much tickets are sufficient, check for a smaller no of tickets
                ans = mid;
                high = mid-1;
            }
        }
        ans == n+1 ? cout<<-1<<endl : cout<<ans<<endl;
    }
}
 
signed main() {
    fastio();
    solve();
}