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
    int tot = 0;
    int ae = 0;

    string w;
    while (cin >> w) {
        ++tot;
        rep(i,0,w.size() - 1) {
            if (w[i] == 'a' && w[i + 1] == 'e') ++ae;
        }
    }
    if (10 * ae >= tot * 4 - 1) {
        cout << "dae ae ju traeligt va" << endl;
    } else {
        cout << "haer talar vi rikssvenska" << endl;
    }
}
