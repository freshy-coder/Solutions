#include<bits/stdc++.h>
#define MAXN 505 //change
#define FIO ios::sync_with_stdio(0); cin.tie(0); 

using namespace std;
typedef pair<long long,long long> pi;
typedef long long ll;
typedef long double ld;
ll N;

ll field[MAXN][MAXN];
bool visited[MAXN][MAXN];
ll ffsize = 0;

void floodFill (ll r, ll c, ll d) {
  
  visited[r][c] = true;
  ffsize++;

  pi exp[4] = {{r+1, c}, {r-1, c}, {r, c+1}, {r, c-1}};

  for (auto item : exp) {
    ll x = item.first; ll y = item.second;
    if (x < 0 || y < 0 || x >= N || y >= N || visited[x][y]) continue;
    if (abs(field[x][y] - field[r][c]) > d) continue;
    // cout << "from: " << r << "," << c << ", visit " << x << "," << y<< endl;
    floodFill(x,y,d);
  }

}

bool works (ll d) {
  fill( &visited[0][0], &visited[0][0] + sizeof(visited), false);

  ll maxSize = 0;

  for (ll r = 0; r < N; r++) {
    for (ll c = 0; c < N; c++) {
      if (!visited[r][c]) {
        ffsize = 0;
        floodFill(r, c, d);
        // cout << "comp found with start: " << r <<"," <<c <<", size: " << ffsize << endl;
        maxSize = max(maxSize, ffsize);
      }
    }
  }

  return (maxSize >= round((N*N)/2.0)); // N^2 is not the same as N*N, so use the second to be safe. And if you need an expression to become float, use a decimal in there! I need to use 2.0 so it becomes float so it can actually round
}
 

int main() { 
  FIO; 
  ofstream fout("tractor.out");
  freopen("tractor.in", "r", stdin);

  cin >> N;

  for (ll r = 0; r < N; r++) {
    for (ll c = 0; c < N; c++) {
      cin >> field[r][c];
    }
  }

  ll a = 0; ll b = 1E9+1; ll mid;
  while (a != b) {
    
    mid = (a+b) / 2;
    
    if (works(mid)) {
      b = mid;
    }
    else {
      a = mid+1;
    }  

  }
  // cout << works(3);
  fout << a;



}

