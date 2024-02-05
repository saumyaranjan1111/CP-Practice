//  https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2421
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
void fill_phi(vector<ll>& phi){
    // nlogn

    phi[1] = 1;
    for(ll i = 2; i<phi.size(); i++){
        phi[i] = i;
    }

    for(ll i = 2; i<phi.size(); i++){
        // for each i, if i is a prime, then reduce all the nos for which i is a prime factor
        if(phi[i] == i){
            // if phi(i) != i, then it means it must have been modified by this loop itself, which means that it is not a prime, since a prime would not be a multiple of any no smaller than that, and therefore we could not have arrived at a prime, so the fact that we have arrived at a no and it is unchanged means that it is a prime since it is untouched
            // and hence if phi[i] = i, then it means than 'i' is a prime
            // so first mark phi[i] = i-1
            // then iterate through all of its multiples and reduce them
            phi[i] = i-1;
            for(ll j = 2*i; j<phi.size(); j+=i){
                phi[j] = phi[j] - phi[j]/i;
            }
        }
    }
}
void solve(){
    // 1 < N < 4000001
    vector<ll> phi(4000010);
    fill_phi(phi);

    vector<ll> dp(4000010, 0);
    // dp[j] : sum of the gcds of all the pairs which have j as the second number : (x, j), where x < j

    // for ex : dp[5] = g(1,5)+g(2,5)+g(3,5)+g(4,5)
    for(ll i = 1; i<dp.size(); i++){
        // (i, j) : how many pairs will have a gcd of i with j
        // for ex : (3, 9) : how many pairs will have a gcd = 3 such that their second element is 9 : (3, 9), (6, 9)
        // question : how many numbers are there which are smaller than 9 , and when paired with 9 will give a gcd of 3 ?
        // answer : all the numbers which have a single 3 in their prime factorization : ie. 3 and 6
        // so how to find out these numbers ?
        // all of these nos have a single factor 3 in common with 9, so if we remove that 3, we can say that these nos will have a gcd of 1 with 9/3, so we just need to find out the no of such nos which have a gcd of 1 with 9/3 
        // or in general terms, we have to find out the no of such nos which have a gcd of 1 with (i/j) : this is simply phi[i/j] 
        // and the contribution of each of these nos would be equal to i
        // ie. the gcd they have in common
        // so for every i, find out the no of numbers which will have i as the gcd with j
        // so contribution of i to j : i*phi(j/i)
        // sum up the contributions of all such i's to a j
        // dp[j] : sum of gcd of all such pairs which end in j
        for(ll j = 2*i; j<dp.size(); j+=i){
            dp[j] = dp[j] + i*phi[j/i];
        }
    }

    for(ll i = 2; i<dp.size(); i++){
        dp[i] = dp[i-1] + dp[i];
    }

    while(true){
        // input terminates when encountering a 0
        ll n; cin>>n;
        if(n == 0) break;
        cout<<dp[n]<<endl;
    }
}
 
signed main() {
    fastio();
    solve();
}