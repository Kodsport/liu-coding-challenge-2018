#include <bits/stdc++.h>
#define MAXN 10000000
#define MAXK 100
#define MAXA 200
#define MAXB 200
#define MAXT 200
#define MAXU 200

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

ll t[MAXK];
ll u[MAXK][MAXK];
int n, k, a, b;

int getRandCost(int limit, bool negative){
	if(rand()%10 == 0)
		return 0;
	if(rand()%10 == 0)
		return limit;
	if(negative && rand()%10 == 0)
		return -limit;
	if(negative){
		return -limit+(rand()%(2*limit+1));
	}
	return rand()%(limit+1);
}

void shuffle_flavours(){
	int p[MAXK];
	ll tmp[MAXK];
	rep(i,0,k)
		p[i]=i;
	random_shuffle(p, p+k);
	rep(i,0,k)
		tmp[i]=t[i];
	rep(i,0,k)
		t[i]=tmp[p[i]];
	rep(i,0,k){
		rep(j,0,k)
			tmp[j]=u[i][j];
		rep(j,0,k)
			u[i][j]=tmp[p[j]];
	}
	rep(i,0,k){
		rep(j,0,k)
			tmp[j]=u[j][i];
		rep(j,0,k)
			u[j][i]=tmp[p[j]];
	}
}

void print(){
	printf("%d %d %d %d\n", n, k, max(1, a), max(1, b));
	rep(i,0,k){
		printf("%d", t[i]);
		if(i == k-1)
			printf("\n");
		else
			printf(" ");
	}
	rep(i,0,k){
		rep(j,0,k){
			printf("%d", u[i][j]);
			if(j == k-1)printf("\n");
			else printf(" ");
		}
	}
}

void random(int argc, char ** argv){
    	if(argc < 6) fprintf(stderr, "not enough arguments");
    	else {
      		int seed = atoi(argv[2]);
      		srand(seed);
      		n = atoi(argv[3]);
      		k = atoi(argv[4]);
      		a = atoi(argv[5]);
		b = getRandCost(MAXB, false);
		if(!b)b=1;
		rep(i,0,k){
			t[i]=getRandCost(MAXT, true);
		}
		rep(i,0,k){
			rep(j,0,k){
				u[i][j]=getRandCost(MAXU, true);
			}
		}
		print();
    	}
}

void just_cone(int argc, char ** argv){
    	if(argc < 6) fprintf(stderr, "not enough arguments");
    	else {
      		int seed = atoi(argv[2]);
      		srand(seed);
      		n = atoi(argv[3]);
      		k = atoi(argv[4]);
      		a = atoi(argv[5]);
		b = getRandCost(MAXB, false);
		if(!b)b=1;
		rep(i,0,k){
			t[i]=-getRandCost(MAXT, false);
		}
		rep(i,0,k){
			rep(j,0,k){
				u[i][j]=getRandCost(MAXU, true);
				while(u[i][j] > -t[i])
					u[i][j]=getRandCost(MAXU, true);
			}
		}
		print();
    	}
}

void one_scoop(int argc, char ** argv){
    	if(argc < 6) fprintf(stderr, "not enough arguments");
    	else {
      		int seed = atoi(argv[2]);
      		srand(seed);
      		n = atoi(argv[3]);
      		k = atoi(argv[4]);
      		a = atoi(argv[5]);
		b = getRandCost(MAXB, false);
		if(!b)b=1;
		if(b > a)
			b=a;
		rep(i,0,k){
			t[i]=getRandCost(MAXT, false);
			if(!t[i])t[i]=1;
		}
		rep(i,0,k){
			rep(j,0,k){
				u[i][j]=-MAXU;//-getRandCost(MAXU, false);
			}
		}
		print();
    	}
}

// 1 <= m <= k
void msmall_scoops(int argc, char ** argv){
    	if(argc < 6) fprintf(stderr, "not enough arguments");
    	else {
      		int seed = atoi(argv[2]);
      		srand(seed);
      		n = atoi(argv[3]);
      		k = atoi(argv[4]);
      		int m = atoi(argv[5]);
		a = getRandCost(MAXA, false);
		b = rand()%2+1;
		if(!b)b=1;
		rep(i,0,k){
			t[i]=MAXT;
		}
		rep(i,0,k){
			rep(j,0,k){
				if(j == i+1 && j < m)
					u[i][j]=MAXU;
				else
					u[i][j]=-MAXU;//getRandCost(MAXU, true)/2;
			}
		}
		shuffle_flavours();
		print();
    	}
}

void mlarge_scoops(int argc, char ** argv){
    	if(argc < 6) fprintf(stderr, "not enough arguments");
    	else {
      		int seed = atoi(argv[2]);
      		srand(seed);
      		n = atoi(argv[3]);
      		k = atoi(argv[4]);
      		int m = atoi(argv[5]);
		a = 1;
		b = 1+2*(m%k);
		if(b > MAXB)
			b=MAXB;
		rep(i,0,k){
			if(i < m%k)
				t[i]=2;
			else
				t[i]=1;
		}
		rep(i,0,k){
			rep(j,0,k){
				if(j == (i+1)%k){
					u[i][j]=0;
				}
				else
					u[i][j]=-MAXU;
			}
		}
		shuffle_flavours();
		print();
    	}
}

void cycles(int argc, char ** argv){
    	if(argc < 6) fprintf(stderr, "not enough arguments");
    	else {
      		int seed = atoi(argv[2]);
      		srand(seed);
      		n = atoi(argv[3]);
      		k = atoi(argv[4]);
		a = getRandCost(MAXA, false);
		b = getRandCost(MAXB, false);
      		int cycleN = atoi(argv[5]);
		rep(i,0,k){
			t[i]=getRandCost(MAXT, true)/3;
			
		}
		rep(i,0,k){
			rep(j,0,k){
				u[i][j]=-MAXU+rand()%4;
			}
		}
		rep(i,0,cycleN){
			int start=rand()%k;
			int cur=start;
			rep(j,0,rand()%(k/2)){
				int to=rand()%k;
				u[cur][to]=MAXU-rand()%10;
				cur=to;
			}
			u[cur][start]=MAXU-rand()%10;
		}
		shuffle_flavours();
		print();
    	}
}

int main(int argc, char **argv){
  if(argc == 1) fprintf(stderr, "no method");
  else if(!strcmp(argv[1], "random")){
	  random(argc, argv);
  } else if(!strcmp(argv[1], "just_cone")){
	  just_cone(argc, argv);
  } else if(!strcmp(argv[1], "one_scoop")){
	  one_scoop(argc, argv);
  } else if(!strcmp(argv[1], "msmall_scoops")){
	  msmall_scoops(argc, argv);
  } else if(!strcmp(argv[1], "mlarge_scoops")){
	  mlarge_scoops(argc, argv);
  } else if(!strcmp(argv[1], "cycles")){
	  mlarge_scoops(argc, argv);
  } else {
  	fprintf(stderr, "invalid method");
  }
}
