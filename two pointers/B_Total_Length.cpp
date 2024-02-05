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
        ll n, s;
        cin>>n>>s;
        vector<ll> a(n);
        for(ll i = 0; i<n; i++) cin>>a[i];

        // let the largest good segment starting at any index l be : sum(a[l], ... , a[r])<=s and sum(a[l, ..., r+1]) > s where r is the last true
        // TTTTTF
        // then all the segments starting from l, and ending <= r are also good segments 
        // add all of their lengths : i.e. : 1 + 2 + 3 + ... + (r - l + 1)
        // therefore sum of lenghts = n*(n+1)/2 = (r-l+1)*(r-l+2)/2
        // since the no of terms = r - l + 1

        // so for every l, find the farthest r such that sum(a[l...r]) <= s
        // then add this ls contribution and increase l
        // if(sum(a[l...r]) <= s) then sum(a[l+1 ... r]) <= s also
        // since the elements are all positive
        // therefore as soon as we are done couting the contribution for a particular l, we can readily move onto l+1, without needing to roll back r and can continue searching for the farthest true for this new l, from the current r itself

        ll l = 0, r = 0;
        ll total = 0;
        ll currsum = 0;
        while(l<n){
            // search for the farthest true( farthest value of r, such that sum(a[l, ... , r]) <= s)
            while(r<n && (currsum + a[r] <= s)){
                currsum += a[r];
                r++;
            }
            // r now points to the first false
            // all the subarrays starting at l, and ending before or at r-1 will be valid
            // add all of their lengths
            total += ((r-l)*(r-l+1))/2;
            
            currsum = max(0LL, currsum - a[l]);
            l++;

            r = max(r, l);
        }   
        cout<<total<<endl;
}
 
signed main() {
    fastio();
    solve();
}