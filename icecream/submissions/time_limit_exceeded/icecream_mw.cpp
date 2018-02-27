#include <bits/stdc++.h>
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
ll ansp, ansq;

void updateAns(ll p, ll q){
	if(double(p)/double(q) > double(ansp)/double(ansq)){
		assert(double(p)/double(q) > double(ansp)/double(ansq));
		ansp=p;
		ansq=q;
	}
}

int main(){
	ansp=0; ansq=1;
	cin >> n >> k >> a >> b;
	bool write=0, read=1;
	rep(i,0,k){
		cin >> t[i];
		dp[write][i]=t[i];
		updateAns(t[i], a+b);
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
		rep(l,0,k){
			rep(j,0,k){
				ll newVal=dp[read][j]+u[j][l]+t[l];
				if(newVal > dp[write][l]){
					dp[write][l]=newVal;
				}	
			}
			updateAns(dp[write][l], b+a*(i+1));
		}
	}
	if(!ansp){
		puts("0");
		return 0;
	}
	printf("%.9lf\n", double(ansp)/double(ansq));
}
