#include <bits/stdc++.h>
 
constexpr int N = sqrt(1E9);
using namespace std;

vector<int> isprime(N + 1, 1);
vector<int> primes;
 
void solve() {
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    set<int> s;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        for (auto p : primes) {
            if (p * p > x) {
                break;
            }
            if (x % p == 0) {
                if (s.find(p)!=s.end()) {
                    cout << "YES\n";
                    return;
                }
                s.insert(p);
                while (x % p == 0) {
                    x /= p;
                }
            }
        }
        if (x > 1) {
            if (s.find(x)!=s.end()) {
                cout << "YES\n";
                return;
            }
            s.insert(x);
        }
    }
    
    cout << "NO\n";
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    for (int i = 2; i <= N; i++) {
        if (isprime[i]) {
            primes.push_back(i);
        }
        for (auto p : primes) {
            if (i * p > N) {
                break;
            }
            isprime[i * p] = 0;
            if (i % p == 0) {
                break;
            }
        }
    }
    
    int t;
    cin >> t;
    
    while (t--) {
        solve();
    }
    
    return 0;
}