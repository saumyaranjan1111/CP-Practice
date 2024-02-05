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
ll N = 1e6;
vector<ll> spf(N + 1);

void smallestPrimeFactor() {
    // Nloglog(N)
    for(ll i = 0; i<=N; i++){
        spf[i] = i;
    }

    for(ll i = 2; i*i <= N; i++){
        if(spf[i] == i){
            ll j = i;
            while(i*j <= N){
                spf[i*j] = min(spf[i*j], i);
                j++;
            }
        }
    }
}

vector<ll> PrimeFactorization(ll x){
    // log(n)
    vector<ll> factors;

    while(x > 1){
        ll prime = spf[x];
        // ll count = 0;
        while(x % prime == 0){
            x = x/prime; 
            // count++;
        }
        factors.pb(prime);
    }
    return factors;
}

void insertIntoMap(ll num, map<ll, multiset<ll>>& mp){
    vector<ll> factors = PrimeFactorization(num);
    for(auto pfactor : factors){
        mp[pfactor].insert(num);
    }
}

void deleteFromMap(ll num, map<ll, multiset<ll>>& mp){
    vector<ll> factors = PrimeFactorization(num);
    for(auto pfactor : factors){
        if(mp[pfactor].find(num) != mp[pfactor].end()){
            mp[pfactor].erase(mp[pfactor].find(num));
        }
    }
}
void solve(){
    smallestPrimeFactor();

    ll t;
    cin>>t;
    while(t--){
        ll n; cin>>n; 
        vector<ll> a(n+1);
        for(ll i = 1; i<=n; i++) cin>>a[i];
        
        multiset<ll> elements;
        for(ll i = 1; i<=n; i++){
            elements.insert(a[i]);
        }

        map<ll, multiset<ll>> mp;
        
        for(ll i = 1; i<=n; i++){
            ll num = a[i];
            insertIntoMap(num, mp);
        }
        ll q; cin>>q;
        while(q--){
            ll x; cin>>x;
            ll mini = INT_MAX;
            vector<ll> factors = PrimeFactorization(x);
            // for each prime factor of x, find the smallest remaining element of the array that is divisible by that prime factor
            for(auto factor: factors){
                if(mp[factor].size() > 0){
                    mini = min(*(mp[factor].begin()), mini);
                }   
            }

            if(mini != INT_MAX){
                cout<<mini<<" ";
                deleteFromMap(mini, mp);
                elements.erase(elements.find(mini));
            } else {
                // no element exists such that gcd(x, e) > 1
                // so print the smallest element from the whole array
                cout<<*elements.begin()<<" ";
                deleteFromMap(*elements.begin(), mp);
                elements.erase(elements.begin());
            }
        }
        cout<<endl;
    }
}
 
signed main() {
    fastio();
    solve();
}