
// headers
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

// #define endl "\n"
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

/*--------------------------------------------------------------------------------------------------------------------------*/

void _print(vector<ll> &arr){
    for(auto x:arr) cout<<x<<" ";
    cout<<endl;
}

struct Interactor{
    vector<ll> arr;

    Interactor(){
        // generating a random permutation
        arr = {4, 8, 15, 16, 23, 42};
        // _print(arr);
        for(ll i = 5; i>=1; i--){
            ll ind = getRandomNumber(0, i-1);
            swap(arr[ind], arr[i]);
        }
        // _print(arr);
    }

    ll make_query(ll l, ll r){
        return arr[l-1]*arr[r-1];
    }

    bool isValidResult(vector<ll> &ans){
        for(ll i = 0; i<arr.size(); i++){
            if(arr[i] != ans[i]){
                cout<<"Actual Output : ";
                _print(arr);
                cout<<"Result : ";
                _print(ans);
                return false;
            }
        }

        // cout<<"Passed for : ";
        // _print(arr);
        return true;
    }
};

void query(ll i, ll j){
    cout<<"? "<<i<<" "<<j<<endl;
}

void solve(){

    // ll tests = 500000;
    // ll pass = 0, fail = 0;

    // while(tests--){
        // Interactor it = Interactor();

        ll product = 4*8*15*16*23*42;
        // cout<<product;
        vector<ll> ans;
        // vector<ll> &arr = it.arr;
        // _print(arr);
        ll x, y, z, w;
        
        query(1, 2);
        // x = it.make_query(1, 2);
        cin>>x;

        query(1, 3);
        // y = it.make_query(1, 3);

        cin>>y;

        // z = it.make_query(1, 4);
        query(1, 4);
        cin>>z;

        // w = it.make_query(1, 5);
        query(1, 5);
        cin>>w;

        // pair : x, y 
        vector<ll> nums = {4, 8, 15, 16, 23, 42};
        for(int i = nums.size()-1; i>=0; i--){
            ll num = nums[i];
            if(x%num == 0 && y%num == 0 && z%num == 0 && w%num == 0){
                ans.pb(num);
                // cout<<ans[0]<<endl;
                break;
            }
        }

        ans.pb(x/ans[0]);
        ans.pb(y/ans[0]);
        ans.pb(z/ans[0]);
        ans.pb(w/ans[0]);

        ll ansprod = 1;
        for(auto x:ans) ansprod*=x;

        ans.pb(product/ansprod);

        cout<<"! ";
        for(auto x:ans) cout<<x<<" ";
        cout<<endl;

        // it.isValidResult(ans) ? pass++ : fail++;
    // }
    
    // cout<<pass<<" passed, "<<fail<<" failed"<<endl;
}
 
int main() {

    fastio();
    solve();

}