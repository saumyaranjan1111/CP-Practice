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

typedef tree<pair<ll, ll>, null_type, less<pair<ll, ll>>, rb_tree_tag, tree_order_statistics_node_update > pbds; // find_by_order, order_of_key
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll getRandomNumber(ll l, ll r) {return uniform_int_distribution<ll>(l, r)(rng);} 
ll gcd(ll a, ll b) {if (b > a) {return gcd(b, a);} if (b == 0) {return a;} return gcd(b, a % b);}
ll expo(ll a, ll b, ll mod) {ll res = 1; while (b > 0) {if (b & 1)res = (res * a) % mod; a = (a * a) % mod; b = b >> 1;} return res;}
ll mod_add(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a + b) % m) + m) % m;}
ll mod_mul(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a * b) % m) + m) % m;}
ll mod_sub(ll a, ll b, ll m) {a = a % m; b = b % m; return (((a - b) % m) + m) % m;}

void _print(vector<ll> &arr){for(auto &x:arr)cout<<x<<" ";cout<<endl;}

/*--------------------------------------------------------------------------------------------------------------------------*/
ll calculateContri(ll rem){
    return expo(2, rem, MOD1);
}
void solve(){
    ll n; cin>>n;
    vector<ll> a(n);
    for(ll i = 0; i<n; i++){ cin>>a[i];}

    map<ll, ll> maxi;
    for(ll i = 0; i<n; i++){
        ll num = i+1;
        vector<ll> factors;
        for(ll j = 1; j*j<=num; j++){
            if(num % j == 0){
                if(num/j != j){
                    factors.pb(j);
                    factors.pb(num/j);
                } else {
                    factors.pb(j);
                }
            }
        }
        for(auto factor: factors){
            if(maxi.find(factor) != maxi.end()){
                maxi[factor] = max(maxi[factor], a[i]);
            } else {
                maxi[factor] = a[i];
            }
        }
    }
    // for(auto it = maxi.begin(); it!= maxi.end(); it++){
    //     cout<<it->first<<" "<<it->second<<endl;
    // }

    ll ans = 0;
    pbds st;
    // set<pair<ll, ll>> st;
    for(auto it = maxi.begin(); it!=maxi.end(); it++){
        st.insert({it->second, it->first});
    }

    for(auto it = st.begin(); it!=st.end(); it++){
        ll num = (*it).second;
        ll contri = (*it).first;
        pair<ll, ll> key = {contri, num};

        ll lessthannum = st.order_of_key(key);
        contri = mod_mul(contri, calculateContri(lessthannum), MOD1);
        ans = mod_add(ans, contri, MOD1);
    }
    cout<<ans<<endl;
}
 
signed main() {
    fastio();
    solve();
}