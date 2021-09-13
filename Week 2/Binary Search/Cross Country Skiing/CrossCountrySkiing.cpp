#include<bits/stdc++.h>
#define MAXD 505 //change
#define FIO ios::sync_with_stdio(0); cin.tie(0); 

using namespace std;
typedef pair<long long,long long> pi;
typedef long long ll;
typedef long double ld;
ll M,N;

ll field[MAXD][MAXD];
ll ways[MAXD][MAXD];
bool visited[MAXD][MAXD];

ll waysMet = 0;

void floodFill (ll r, ll c, ll d) {
  
  visited[r][c] = 1;
  if (ways[r][c] == 1) waysMet++;

  pi exp[4] = {{r+1, c}, {r-1, c}, {r, c+1}, {r, c-1}};

  for (auto item : exp) {
    ll x = item.first; ll y = item.second;
    if (x < 0 || y < 0 || x >= M || y >= N || visited[x][y]) continue;
    if (abs(field[x][y] - field[r][c]) > d) continue;
    // cout << "from: " << r << "," << c << ", visit " << x << "," << y<< endl;
    floodFill(x,y,d);
  }

}

int main() { 
  FIO; 
  ofstream fout("ccski.out");
  freopen("ccski.in", "r", stdin);

  cin >> M >> N;



  for (ll r = 0; r < M; r++) {
    for (ll c = 0; c < N; c++) {
      cin >> field[r][c];
    }
  }

  pi aWayPtLoc; ll numWays = 0;
  for (ll r = 0; r < M; r++) {
    for (ll c = 0; c < N; c++) {
      cin >> ways[r][c];
      if (ways[r][c] == 1){
        aWayPtLoc = make_pair(r,c);
        numWays++;
      }
      
    }
  }
  
  ll a = 0; ll b = 1E9+1; ll mid;
  // binary search time out may be caused by infinite loop caused by incorrect a & b. set mid to nothing, not to zero
  // try the configuration/parts of it above for a, b, mid.
  while (a != b) {
    
    mid = (a+b) / 2;

    
    for (ll i = 0; i < MAXD; i++) {
      for (ll j = 0; j < MAXD; j++) visited[i][j] = false;
    }
    waysMet = 0;

    floodFill(aWayPtLoc.first, aWayPtLoc.second, mid);
    
    if (waysMet == numWays) {
      b = mid;
    }
    else {
      a = mid+1;
    }  

  }
  fout << a;

}

