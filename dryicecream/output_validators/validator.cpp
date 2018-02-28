// usage: ./a.out input_file correct_output < contestants_output

#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define trav(a, x) for (auto& a : x)
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;

string input_file, answer_file;

void die(const string& msg) {
    cout << msg << endl;
    exit(43);
}

void accept() {
    exit(42);
}

void assert_done(istream& is) {
    try {
        string dummy;
        is >> dummy;
		if (is) die("extraneous data: " + dummy);
    } catch(...) {}
}

struct UF {
	vi v;
	UF(int n) : v(n, -1) {}
	int find(int x) { return v[x] < 0 ? x : v[x] = find(v[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (-v[a] < -v[b]) swap(a, b);
		v[a] += v[b];
		v[b] = a;
		return true;
	}
};

int main(int argc, char** argv) {
    if (argc < 4) exit(1);
    cin.sync_with_stdio(0);
    cin.tie(0);

    input_file = argv[1];
    answer_file = argv[2];

    ifstream fin(input_file);
    fin.exceptions(cin.failbit | cin.badbit | cin.eofbit);

    int N, target;
    fin >> N;
	vi cap(N), bottle(N);
	rep(i,0,N) fin >> cap[i];
	fin >> target;
    assert_done(fin);
    fin.close();

    fin.open(answer_file);
	string word;
	fin >> word;
    fin.close();

    try {
		if (word == "impossible") {
			cin >> word;
			trav(c, word) c = (char)tolower(c);
			if (!cin || word != "impossible") die("did not output impossible");
			assert_done(cin);
			accept();
		}

		int cmdrem = 100000;
		string cmd;
		while (cin >> cmd) {
			if (cmd == "impossible") die("claimed impossible but was not");
			int x, y = 0;
			cin >> x;
			if (cmd == "transfer") cin >> y;
			--x, --y;
			if (!cin) die("unexpected eof");
			if (--cmdrem < 0) die("more moves than allowed");
			if (x < 0 || x >= N) die("invalid source bottle");
			if (cmd == "fill") {
				bottle[x] = cap[x];
			}
			else if (cmd == "discard") {
				bottle[x] = 0;
			}
			else if (cmd == "transfer") {
				if (y < -1 || y >= N) die("invalid target bottle");
				if (x == y) die("same source and target");
				if (y == -1) {
					if (bottle[x] > target) die("poured too much");
					target -= bottle[x];
					bottle[x] = 0;
				} else {
					int use = min(bottle[x], cap[y] - bottle[y]);
					bottle[y] += use;
					bottle[x] -= use;
				}
			}
		}

		if (target != 0) die("did not hit target");

        accept();
    } catch(...) {
        die("IO failure");
    }
}
