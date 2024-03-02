// https://codeforces.com/problemset/problem/154/B
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
vector<ll> spf(1e6);

void SPF(){
    for(ll i = 0; i<1e6; i++){
        spf[i] = i;
    }
    for(ll i = 2; i*i<1e6; i++){
        if(spf[i] == i){
            for(ll j = i*i; j<1e6; j+=i){
                spf[j] = min(i, spf[j]);
            }
        }
    }
}

auto PF(ll n){
    vector<ll> primes;
    while(n>1){
        ll prime = spf[n];
        primes.pb(prime);
        while(n%prime == 0){
            n = n/prime;
        }
    }
    return primes;
}
void solve(){
    SPF();
    ll n, m;
    cin>>n>>m;
    map<ll, set<ll>> primes;
    vector<bool> vis(n+1, false);

    for(ll i = 0; i<m; i++){
        char sign;
        ll num;
        cin>>sign>>num;

        if(sign == '+'){
            if(vis[num] == true){
                cout<<"Already on"<<endl;
                continue;
            } else {
                // check for its prime factors in the already present elements
                auto factors = PF(num);
                bool flag = true;

                for(auto p : factors){
                    if(primes.find(p)!=primes.end() && primes[p].size() > 0){
                        cout<<"Conflict with "<<*(primes[p].begin())<<endl;
                        flag = false;
                        break;
                    }
                }

                // if a prime factor is already found, then just move on to the next query
                if(flag == false){
                    continue;
                }

                // if the prime factors are not found in the existing numbers, then insert the number into all the prime factors of num
                vis[num] = true;
                for(auto p : factors){
                    primes[p].insert(num);
                }

                cout<<"Success"<<endl;
            }
        } else {
            if(vis[num] == false){
                cout<<"Already off"<<endl;
                continue;
            } else {
                vis[num] = false;

                auto factors = PF(num);
                for(auto p : factors){
                    primes[p].erase(num);
                }
                cout<<"Success"<<endl;
            }
        }
    }

    
}
 
signed main() {
    fastio();
    solve();
}