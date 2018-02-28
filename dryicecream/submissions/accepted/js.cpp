#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi bot, ebot, has;

int transfer(int from, int to) {
    int cantransfer = min(has[from], bot[to] - has[to]);
    cout << "transfer " << (from + 1) << " " << (to + 1) << endl;;
    has[from] -= cantransfer;
    has[to] += cantransfer;
    return cantransfer;
}

int fill(int x) {
    cout << "fill " << (x + 1) << endl;
    has[x] = bot[x];
    return bot[x];
}

void discard(int x) {
    cout << "discard " << (x + 1) << endl;
    has[x] = 0;
}

int fillBottle(int x) {
    if (x == sz(bot) - 1) return fill(x);
    discard(x + 1);
    fillBottle(x + 1);
    while (true) {
        transfer(x + 1, x);
        if (has[x] == ebot[x]) return ebot[x];
        if (has[x] == bot[x]) discard(x);
        if (!has[x + 1]) fillBottle(x + 1);
    }
}

int dispose() {
    int ret = has[0];
    cout << "transfer 1 0" << endl; 
    has[0] = 0;
    return ret;
}

int main() {
	cin.sync_with_stdio(0); cin.tie(0);
	cin.exceptions(cin.failbit);
    int N;
    cin >> N;
    bot.resize(N);
    ebot.resize(N);
    has.resize(N);
    rep(i,0,N) cin >> bot[i];
    ebot[N - 1] = bot[N - 1];
    for (int i = N - 2; i >= 0; --i) {
        ebot[i] = __gcd(bot[i], ebot[i + 1]);
        if (ebot[i] == ebot[i + 1]) {
            bot.erase(bot.begin() + i);
            ebot.erase(ebot.begin() + i);
            has.erase(has.begin() + i);
            --N;
        }
    }
    int T;
    cin >> T;
    if (T % ebot[0]) cout << "impossible" << endl;
    else {
        while (T) {
            fillBottle(0);
            T -= dispose();
        }
    }
}
