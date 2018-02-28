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
    long long bestCash = 0;
    rep(i,0,N) {

        long long price;
        cin >> price;

        bestCash = max(bestCash, 100 * price);
        bestCash -= K;
        bestCash = max(bestCash, 0LL);

        // Try repurchasing the stock
        ans = max(ans, bestCash - price * 100);
    }
    cout << ans << endl;
}
