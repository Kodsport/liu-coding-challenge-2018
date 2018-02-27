#include <bits/stdc++.h>
#define MAXK 100
#define INF 1000000000000000000LL

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

struct Matrix{
	ll v[MAXK][MAXK];
	Matrix operator*(Matrix other){
		Matrix res;
		rep(i,0,k)
			rep(j,0,k){
				res.v[i][j]=-INF;
				rep(l,0,k){
					res.v[i][j]=max(res.v[i][j],v[i][l]+other.v[l][j]);	
				}
			}
		return res;
	}

	ll getBest(){
		ll ret=0;
		rep(i,0,k)
			rep(j,0,k)
				ret=max(ret, v[i][j]+t[j]);
		return ret;
	}
} M, unity, tmp;
	
ll ansp=0, ansq=1;
ll debugBestNum=0;

void check(Matrix m, ll num){
	if(num > n)
		return;
	ll p=m.getBest();
	ll q=b+a*num;
	if(double(p)/double(q) > double(ansp)/double(ansq)){
		ansp=p;
		ansq=q;
		debugBestNum=num;
	}
}

int main(){
	scanf("%lld%lld%lld%lld", &n, &k, &a, &b);
	rep(i,0,k)
		scanf("%lld", t+i);
	rep(i,0,k)
		rep(j,0,k){
			scanf("%lld", u[i]+j);
			M.v[i][j]=t[i]+u[i][j];
			if(i != j)
				unity.v[i][j]=-INF;
		}
	tmp=unity;
	rep(i,0,k){
		check(tmp, i+1);
		tmp=tmp*M;
	}
	if(k < n){
		tmp=unity;
		ll target=n-k;
		ll t=target;
		for(int i=50; i >= 0; --i){
			tmp=tmp*tmp;
			if(t&(1LL<<i))
				tmp=tmp*M;
		}
		rep(i,target,n){
			check(tmp, i+1);
			tmp=tmp*M;
		}
	}
	if(!ansp){
		puts("0");
		return 0;
	}
	printf("%.9lf\n", double(ansp)/double(ansq));
}
