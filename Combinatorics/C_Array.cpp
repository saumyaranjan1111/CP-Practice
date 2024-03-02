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

/*--------------------------------------------------------------------------------------------------------------------------*/
ll combination(ll n, ll r, ll m){
    // O(r)
    ll p = 1;
    ll q = 1;
    for(ll i = n; i>=n-r+1; i--){
        p = mod_mul(p, i, m);
    }
    for(ll i = r; i>=1; i--){
        q = mod_mul(q, i, m);
    }
    
    return mod_mul(p, expo(q, m-2, m), m);
}
void solve(){
    ll n; cin>>n;
    // x1 : no of 1s in the arrangement
    // xi : no of is in the arrangement
    // x1 + x2 + ... + xn = n
    // one configuration of the no of elements that we are choosing of each type fixes the no of permutations for that which will be valid
    // for ex: 111339999 and 999933111 are the only two valid permutations 
    // if our choice is x1 = 3, x3 = 2, x9 = 4
    // and n == 9
    // so no of selections = no of solutions for the above equation = C(n+k-1, n) = C(n+n-1, n)
    // and there are two valid permutations for each selection 
    // therefore ans == C(2n-1, n)*2
    // but we have overcounted, since for some of the selections the valid permutations would just be 
    // for example : for x1 = 9; x2 = 9 and so on, in all these cases, where all the elements that we choose are of the same type
    // then there will just be 1 permutation which satisfies the beautiful array condition since the other permutation is the same as this one
    // there are n such permutations which we need to remove from our final answer
    // C(2n-1, n)*2 - n
    cout<<mod_mul(combination(2*n-1, n, MOD), 2, MOD) - n<<endl; 
}
 
signed main() {
    fastio();
    solve();
}