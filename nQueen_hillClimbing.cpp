#include <bits/stdc++.h>

using namespace std;

const int nMax = 100000 + 5 ;


clock_t begin_time;
int n ;
int iq[nMax];
int queen[nMax]; // con hau o hang i nam o cot queen[i]
int dSw[nMax*2]; // dsw[i] dem so con hau nam tren duong cheo xuoi thu i
int dRe[nMax*2]; // dre[i] dem so con hau nam tren duong cheo nguoc thu i
int getSw(int i){ return i+ queen[i] - 1; }
int getRe(int i){ return i- queen[i] + n; }
int steps ;
int tmp[nMax] ;

void next_per(){
	int i=n;
	while(iq[i]<iq[i-1]) i--;
	i--;
	int k=n;
	while(iq[i]>iq[k])  k--;
	swap(iq[i], iq[k]);
	int r=i+1, s=n;
	while(r<=s){ swap(iq[r],iq[s]); r++;s--;}
}

void answer(){
	int a[n+1][n+1];
	for (int i = 1; i<=n; i++){
		for (int j = 1; j<=n; j++){
			a[i][j] = 0 ;	
		}
	}
	for (int i=1; i<=n; i++) a[i][queen[i]] = 1;
	for (int i=1; i<=n; i++) {
		for (int j = 1; j<=n; j++){
			cout << a[i][j] <<' ';
		}
		cout << endl;
	}
} 
void answer(int check){
//	cout << endl;
//	for (int i=1; i<=n; i++){
//		cout << dSw[getSw(i)] << ' ' << dRe[getRe(i)] <<endl;
//	}
	if (check == 0){
		cout << "die" <<endl;
		cout << "Steps :" << steps << endl;
		cout << "Time :" << float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s" <<endl;
		return ;
	}
	
	cout << "Steps :" << steps << endl;
	cout << "Time :"<< float( clock () - begin_time ) /  CLOCKS_PER_SEC << "s" <<endl;
	for (int i=1; i<=n; i++) {
		cout << i << ' ' << queen[i] <<endl;
	}
	cout << "========================================="<< endl ;
//	cout << endl;
//	answer();
//	cout << endl;
}

void init(){
	for (int i = 1; i<=n; i++){
		dSw[getSw(i)] = 0;
		dRe[getRe(i)] = 0;
	}
	for (int i = 1; i<=n; i++) {
		queen[i] = iq[i] ;
		//cout << queen[i] <<' ' ;
		dSw[getSw(i)]++;
		dRe[getRe(i)]++;	
	}
	//cout << endl;
}

int __swapQ(int u,int v){
	int u_idSw ,u_idRe,v_idSw,v_idRe ;
	
	u_idSw = getSw(u);
	u_idRe = getRe(u);
	dSw[u_idSw] --;
	dRe[u_idRe] --;
	v_idSw = getSw(v);
	v_idRe = getRe(v);
	dSw[v_idSw] --;
	dRe[v_idRe] --;
		
	swap (queen[u], queen[v]);
	
	u_idSw = getSw(u);
	u_idRe = getRe(u);
	dSw[u_idSw] ++;
	dRe[u_idRe] ++;
	v_idSw = getSw(v);
	v_idRe = getRe(v);
	dSw[v_idSw] ++;
	dRe[v_idRe] ++;
}

int calcHeuristic(int u, int v){
	//int sum_att = calcAtt();
	// check di xuong
	
	int d ;
	int sum_att = 0 ;
	d = dSw[getSw(u)];
	sum_att+= (d-1);
	
	d = dRe[getRe(u)];
	sum_att+= (d-1);
	
	d = dSw[getSw(v)];
	sum_att+= (d-1);
	
	d = dRe[getRe(v)];
	sum_att+= (d-1);
	
	if (getSw(u) == getSw(v)) sum_att -- ;
	if (getRe(u) == getRe(v)) sum_att -- ;
	
	
	__swapQ(u,v);
	//int sum_new = calcAtt();
	int sum_new = 0;
	d = dSw[getSw(u)]; sum_new+= (d-1);
	
	d = dRe[getRe(u)]; sum_new+= (d-1);
	
	d = dSw[getSw(v)]; sum_new+= (d-1);
	
	d = dRe[getRe(v)]; sum_new+= (d-1);	
	if (getSw(u) == getSw(v)) sum_new -- ;
	if (getRe(u) == getRe(v)) sum_new -- ;
	
	__swapQ(u,v);
	
	return sum_att - sum_new;
}


int Hill_Climbing(){
	while(true){
		int swaps = 0 ;
		int u = 0;
		int v = 0;
		int dmax = 0 ;
		for (int i = 1; i< n ; i++){
			for (int j = i+1; j<=n; j++){
				int d = calcHeuristic(i,j) ;
				if (d > dmax){
					dmax = d;
					u = i ; 
					v = j ;
					swaps = 1;
				}
			}
		}
		if (swaps == 0){
			//answer(1);
			for (int i = 1; i<=n; i++){
				if (dSw[getSw(i)] >1){
					answer(0);
					return 0;
				}
				if (dRe[getRe(i)] >1){
					answer(0);
					return 0;
				}
			}
			answer(1);
			return 1;
		}
		steps++ ;
		__swapQ(u,v);
	}
}

int Hill_Climbing_Random(){
	while(true){
		int swaps = 0 ;
		int u , v;
		int nt = 0 ;
		for (int i = 1; i<= n; i++){
			if (dSw[getSw(i)] >1 || dRe[getRe(i)] >1){
				nt++;
				tmp[nt] = i;
			}
		}
		if (nt >0)
			for (int i = 1; i<= n; i++){
				steps++ ;
				u = tmp[rand()%nt + 1] ;
				v = rand()%(n-1)+ 1;
				if (v >= u) v++;
				if (calcHeuristic(u,v) > 0){
					swaps = 1;
					break ;
				}
			}
		if (swaps == 0){
			//answer(1);
			for (int i = 1; i<=n; i++){
				if (dSw[getSw(i)] >1){
					answer(0);
					return 0;
				}
				if (dRe[getRe(i)] >1){
					answer(0);
					return 0;
				}
			}
			answer(1);
			return 1;
		}
		__swapQ(u,v);
	}
}

int Simulated_Annealing(){
	int temperature = n*n;
	while(temperature>0){
		int u , v;
		int nt = 0 ;
		for (int i = 1; i<= n; i++){
			if (dSw[getSw(i)] >1 || dRe[getRe(i)] >1){
				nt++;
				tmp[nt] = i;
			}
		}
		if (nt >0){
			u = tmp[rand()%nt + 1] ;
			v = rand()%(n-1)+ 1;
			steps++;
			if (v >= u) v++;
			int delta = calcHeuristic(u,v);
			if (delta > 0){	
				__swapQ(u,v);
			}
			else{
				float rd = (float) ( rand()%1000) / (float)1000;
				//cout <<"delta" << delta <<' ' <<temperature <<endl;
				float pr = (float)exp((double)delta / (double)temperature);
				//cout << rd << ' ' <<pr<<endl;
				if (rd > pr){	
					__swapQ(u,v);
				}
			}
		}
		else{
			break ;
		}
		temperature--;
	}
	for (int i = 1; i<=n; i++){
		if (dSw[getSw(i)] >1){
			answer(0);
			return 0;
		}
		if (dRe[getRe(i)] >1){
			answer(0);
			return 0;
		}
	}
	answer(1);
	return 1;
}

int solve(int sol){
	if (sol == 0) return Hill_Climbing();
	if (sol == 1) return Hill_Climbing_Random();
	if (sol == 2) return Simulated_Annealing();
}

int main(){
	
	clock_t bgcl = clock();
//	cout << "Enter n = ";
//	cin >> n ;
	n = 1000;
	
	int sol = 2;
	// 0 : Hill Climbing              leo doi
	// 1 : Hill Climbing Random       leo doi ngau nhien
	// 2 : Simulated Annealing        toi thep  
	
	freopen("00.an","w",stdout);
	int t = 0;
	for (int i = 1; i<=n; i++) iq[i] = i ;
	while (true){
		t++ ;
		steps = 0 ;
		cout <<endl << "Iter :" << t << "----------------------------------"<<endl;
    	begin_time = clock();
		init();
		next_per();
		int k = solve(sol);
		if (k == 1) break ;
	}
	cout << endl << "All time    : " << (float) (clock() - bgcl )/  CLOCKS_PER_SEC<<"s"<<endl;
	cout << "Iter counts : " << t ;
	
}
