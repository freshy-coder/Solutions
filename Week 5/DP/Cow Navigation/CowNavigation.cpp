#include<bits/stdc++.h>
#define MAXN 20
using namespace std;
typedef pair<long long, long long> pi;
typedef int ll;
typedef long double ld;
ll N;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

// can read in character by character if you can't process whole string at once
// BFS + DP. BFS on i, j, x, y, rotation, length of path
// i, j is the coordinates if bessie started upwards, x,y is if bessie started rightwards
// at first glance, this DOES seem like DP! parts of the path that might not be used, exploring path lengths to get to a destination
// They key was that you had to keep track of where BOTH orientations would be. Four dimensions, N=20, makes perfect sense there would be multiple powers of N. But because it is nodes on a graph and rotations/movements between, you can apply a BFS
// in the future, algs like BFS, DFS, FF can be used with DP
// *WE DIDN'T NEED A DP TABLE! We were just bfs-ing, our BFS WAS the DP. having DP table would have exceeded memory
// *CHOSE BFS BECAUSE IT BY DEFINITION will get you the shortest path to any point. You can use similar logic when choosing graph algs for DP
// SIMPLIFYING THE PROBLEM would have also shown you BFS is needed. Just one starting orientation -> BFS to destination. Two starting -> BFS on a larger graph
// *DP "state"/what we saved as the distance is ALL VARIABLES except the length one/nonpositional one(s). This is also what we BFS on.
// Things from implementation:
// if you're seemingly on the right algorithm, it passes a couple test cases here and there, please go back and read the problem statement. Those were the snags in this problem
// Also, if you're doing a DP, or some sort of search like BFS in here, MINIMIZE OVERLAP/REPEAT CASES! From each point, you only need to consider turning right once, turning left once, NOT turning right TWICE (that will be covered when we BFS to the point that turned right once.) If you include that, you might visit too early ig, there might be an erroneous distance. It's just repetitive.
// Again, the DP solution state in this case was NOT one cell, but a range.
// Ask - Confirm state, how did we know l would be long enough? How did we know size large enough?  Confirm BFS, confirm error


ll grid[MAXN][MAXN];
// ll dp[MAXN][MAXN][MAXN][MAXN][4][100]; // i, j, x, y, rotation, length
ll dist[MAXN][MAXN][MAXN][MAXN][4]; // i, j, x, y, rot = length
queue<vector<ll>> q; 

void add(vector<ll> a, vector<ll> og) { // only adds if not stepping on some haybale
  if (a[0] >= N || a[0] < 0 || a[1] >= N || a[1] < 0 || grid[a[0]][a[1]] == 1 || (og[0] == 0 && og[1] == N-1)){
    a[0] = og[0]; a[1] = og[1];
  }
  if (a[2] >= N || a[2] < 0 || a[3] >= N || a[3] < 0 || grid[a[2]][a[3]] == 1 || (og[2] == 0 && og[3] == N-1)){
    a[2] = og[2]; a[3] = og[3];
  }
  q.push(a);
  // cout << "adding forwards: " << a[0]<<" " <<a[1]<<" " <<a[2]<<" " <<a[3]<<" " <<a[4] <<" " << a[5] << endl;
}

ll distAcc(vector<ll> x) {
  return dist[x[0]][x[1]][x[2]][x[3]][x[4]];
}

void bfs() {
  
  dist[N-1][0][N-1][0][0] = 0;
  q.push({N-1, 0, N-1, 0, 0, 0}); // same as dp. i, j, x, y, rotation, length
  ll count = 0;
  while (!q.empty()) {
    count++;

    vector<ll> x = q.front();
    
    q.pop();

    if (distAcc(x) != -1 && count != 1) {
      // cout << "quitting: " << distAcc(x) << endl;
      continue;
    }
    // cout << count << endl;
    // cout << "investigating: " << x[0]<<" " <<x[1]<<" " <<x[2]<<" " <<x[3]<<" " <<x[4] <<" " << x[5] << endl;
    dist[x[0]][x[1]][x[2]][x[3]][x[4]] = x[5];
    // cout << "setting dist: " << x[5] << endl;

    ll inc = 0;
    for (ll k = 1; k < 4; k++) { // all other possible rotations - 1,2,3
      if (k == 2) continue; // no too many overlapping cases!!! used to consider this rotation too, not sure why that was bad
      else inc = 1;
      q.push({x[0],x[1],x[2],x[3],   (x[4]+k) % 4   , x[5]+(inc)});
      // cout << "adding rotation: " << x[0]<<" " <<x[1]<<" " <<x[2]<<" " <<x[3]<<" " <<(x[4]+k) % 4 <<" " <<x[5]+(inc) << endl;
    }

    // going forward
    if (x[4] == 0) {
      add({x[0],  x[1]+1  ,  x[2]-1  ,x[3],x[4],  x[5]+1  }, x); // A goes RIGHT, B goes UP
    }
    else if (x[4] == 1) {
      add({  x[0]+1  ,x[1],x[2],  x[3]+1  ,x[4],  x[5]+1  }, x); // A goes DOWN, B goes RIGHT
    }
    else if (x[4] == 2) {
      add({x[0],  x[1]-1  ,  x[2]+1  ,x[3],x[4],  x[5]+1  }, x); // A goes LEFT, B goes DOWN
    }
    else if (x[4] == 3) {
      add({  x[0]-1  ,x[1],x[2],  x[3]-1  ,x[4],  x[5]+1  }, x); // A goes UP, B goes LEFT
    }
    
  }
} 

int main() { 
  FIO;
  freopen("cownav.in", "r", stdin);
  ofstream fout("cownav.out");

  cin >> N;
  for (ll i = 0; i < N; i++) {
    for (ll j =0; j < N; j++) {
      char x; cin >> x;
      if (x == 'H') grid[i][j] = 1;
      else grid[i][j] = 0;
    }
  }

  for (ll i = 0; i < MAXN; i ++) {
    for (ll j = 0; j < MAXN; j++) {
      for (ll x = 0; x < MAXN; x ++) {
        for (ll y = 0; y < MAXN; y++) {
          for (ll k = 0; k < 4; k++) {
            dist[i][j][x][y][k] = -1;
          }
        }
      }
    }
  }
  bfs();
  ll ans = 1E9;
  for (ll k = 0; k < 4; k++) {
    if (dist[0][N-1][0][N-1][k] == -1) continue;
    ans = min(ans, dist[0][N-1][0][N-1][k]);
  }
  if (ans == 1E9) ans = -1;
  fout << ans;

}