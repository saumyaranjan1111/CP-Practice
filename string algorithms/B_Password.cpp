// https://codeforces.com/contest/126/problem/B
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
auto z_algo(string &s){
    ll n = s.size();
    vector<ll> z(n);
    z[0] = 0;
    ll l = 0, r = 0;
    for(ll i = 1; i<n; i++){
        if(i>r){
            l=r=i;
            while(r<n && s[r]==s[r-l]) r++;
            z[i] = r-l;
            r--;
        } else {
            ll idx = i-l;
            if(i + z[idx] <= r){
                z[i] = z[idx];
            } else {
                l = i;
                while(r<n && s[r]==s[r-l]) r++;
                z[i] = r-l;
                r--;
            }
        }
    }
    return z;
}
void solve(){
    string s; cin>>s;
    ll n = s.size();
    auto z = z_algo(s);
    
    ll len = 0;
    // len : length of the longest prefix-suffix
    for(ll i = 1; i<n; i++){
        if(i + z[i] < n){
            // we found a prefix in the middle of the string which is not a suffix
            // update len
            len = max(len, z[i]);
        } else {
            len = max(len, z[i] - 1);
        }
    }
    // cout<<len<<endl;
    for(ll i = 1; i<n; i++){
        if(i + z[i] == n){
            // we are present at a suffix which is also a prefix
            // now check if the len of the max prefix found in the middle of the string is >= to z[i] or not
            // if len >= z[i]
            // that means that we can find this suffix in that middle part of the string too
            // else if len < z[i] that means we cant completely find this suffix in that middle part of the string
            if(len >= z[i]){
                // the suffix starting from i is the biggest (since we are iterating from the left) suffix which is also a prefix ( since z[i] + i == n)
                // and this suffix also appears atleast once in the middle of the string somewhere ( since the biggest substring which is also a prefix also contains this (since len >= z[i]))
                // so print the first z[i] characters of the string and return
                cout<<s.substr(0, z[i]);
                return;
            }
        }
    }
    cout<<"Just a legend"<<endl;
}
 
signed main() {
    fastio();
    solve();
}