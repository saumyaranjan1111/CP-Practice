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
    ll n, k;
    cin>>n>>k;
    vector<ll> a(n);
    for(ll i= 0; i<n; i++) cin>>a[i];
    map<ll,ll> mp;
    ll i = 0, j = 0;
    // starting at any i, look for TTTTTTFFFF (first false), which means every index before it will be a possible subarray which has the no of unique elements <= k

    ll count = 0;
    while(i<n){
        while(j<n && mp.size() < k || (mp.size() == k && mp.find(a[j]) != mp.end())){
            // no of unique elements is <= even after adding the jth element
            mp[a[j]]++; j++;
        }

        // TTTTF
        // j is now pointing to the first element whose addition to the current subarray from i to j would result in the no of unique elements to be > k
        // therefore the biggest subarray starting at i having <= k elements ends at j-1
        // define this as a good subarray, then all the subarrays from i ending at i, i+1, ..., j-1 will all be subarrays such that the unique elements in them will be <=k 
        // good sequence(increasing concept)
        count += j-i;
        
        // remove the ith element from the map, if the ith element becomes zero then we need to reduce the size of the map to correctly track the no of unique elements in the current subarray
        if(mp.find(a[i]) != mp.end()) mp[a[i]]--;
        if(mp[a[i]] == 0) mp.erase(a[i]);

        i++;
        j = max(j, i);
    }
    cout<<count<<endl;
}
 
signed main() {
    fastio();
    solve();
}