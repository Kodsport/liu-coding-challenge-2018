#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);

    int N, K;
    cin >> N >> K;

    long long ans = 0;
    vi P(N);
    rep(i,0,N) cin >> P[i];
    rep(i,0,N) {
        rep(j,i+1,N) {
            ll earn = (P[i] - P[j]) * 100 - K * (j - i + 1);
            ans = max(earn, ans);
        }
    }
    cout << ans << endl;
}
