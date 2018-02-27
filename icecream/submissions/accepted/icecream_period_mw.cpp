#include <bits/stdc++.h>
#define MAXN 10000000
#define MAXK 100
#define INF 2000000000LL

using namespace std;

#define rep(i, a, b) for(int i = (a); i < int(b); ++i)
#define rrep(i, a, b) for(int i = (a) - 1; i >= int(b); --i)
#define trav(it, v) for(typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
#define all(v) (v).begin(), (v).end()

typedef double fl;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpi;

ll n, k, a, b;
ll t[MAXK];
ll u[MAXK][MAXK];
ll dp[2][MAXK];
ll best[MAXN];
long double ans=0;

void updateAns(ll p, ll q){
	long double val = p;
	val /= q;
	ans = max(ans, val);
}

int main(){
	cin >> n >> k >> a >> b;
	bool write=0, read=1;
	best[0]=-INF;
	rep(i,0,k){
		cin >> t[i];
		dp[write][i]=t[i];
		updateAns(t[i], a+b);
		best[0]=max(best[0], dp[write][i]);
	}
	rep(i,0,k)
		rep(j,0,k){
			cin >> u[i][j];
		}
	rep(i,1,n){
		write^=1;
		read^=1;
		rep(j,0,k){
			dp[write][j]=-INF;
		}
		best[i]=-INF;
		rep(l,0,k){
			rep(j,0,k){
				ll newVal=dp[read][j]+u[j][l]+t[l];
				if(newVal > dp[write][l]){
					dp[write][l]=newVal;
				}
			}
			updateAns(dp[write][l], b+a*(i+1));
			best[i]=max(best[i], dp[write][l]);
		}
		bool stop=0;
		for(int period=1; period <= 100; ++period){
			int j;
			for(j=i; j >= 2*period; --j){
				if(best[j]-best[j-period] != best[j-period]-best[j-2*period])
					break;
			}
			if(i-j > period*4+100){
				stop=1;
				for(j=n-k; j < n; ++j){
					int c=i-period-(i-j)%period;
					ll val=best[c]+((j-c)/period)*(best[c]-best[c-period]);
					updateAns(val, b+a*(j+1));
				}
			}
		}
		if(stop)
			break;
	}
	if(ans == 0){
		puts("0");
		return 0;
	}
	cout.precision(9);
	cout << fixed << ans << endl;
}

