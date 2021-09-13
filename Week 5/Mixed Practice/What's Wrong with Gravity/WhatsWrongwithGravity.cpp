#include<bits/stdc++.h>
#define MAXN 505
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

// Algorithm:
// Precompute places every single node can fall to for either direction of gravity
// run dijkstra, each node-move is either a right, left, or gravity flip, in which case the path length increases by 1.

// Thinking:
// See how you can interpose a graph! it is pretty obvious that this is dijkstra, on a graph. - we have nodes, we have moves, we are trying to get somewhere
// once you have such a lead just go with it.
// the transfer from one node to the next may be complex (gravity flip). PRECOMPUTATION may be very useful for these sort of cases.
// what NEEDS to be precomputed? All nodes? Do we need to dijkstra all nodes? (In this case we found that no we don't)

// little things:
// code not doing anything may also because of infinite loop. check your for increments
// you're still messing up your sets of if/else if/ifelse/ifelse etc. trace each possible case and see if you get your expected output
// just set distances to the value the problem wants you to output if you cant reach the destination: -1 in most cases. EITHER WAY DO NOT FORGET THIS CASE! IT'S A BIG WASTE OF TIME
// you can still do return 0 without an "int" main
// and make sure you test edge cases you think of! you often forget

ll N, M;
ll grid[MAXN][MAXN];
pi falls0[MAXN][MAXN];
pi falls1[MAXN][MAXN];
bool visited[MAXN][MAXN];
ll distances[MAXN][MAXN];
priority_queue<vector<ll>> pq;


main() { 
  FIO;
  freopen("gravity.in", "r", stdin);
  ofstream fout("gravity.out");

  cin >> N >> M; 
  pi start; pi end;
  for (ll i = 0; i < N; i++) {
    for (ll j = 0; j < M; j++) {
      visited[i][j] = false;
      char x; cin >> x;
      if (x == 'C') {start = {i,j};}
      else if (x == 'D') end = {i,j};
      if (x == '#') grid[i][j] = 1;
      else {
        if (i == N-1) grid[i][j] = -1;
        else if (i == 0) grid[i][j] = -2; // watch. again
        else grid[i][j] = 0;
      }
    }
  }

  // Type 1 gravity: on the i axis, you fall down to i+1
  // Type 0 gravity: on the i axis, you fall up to i-1

  // // setting falls for Type 0 gravity
  for (ll i = 0; i < N; i++) {
    for (ll j = 0; j < M; j++) {
      if (visited[i][j]) continue;
      ll k =i;
      while (k < N && grid[k][j] != 1) {
        falls0[k][j] = {i,j};
        visited[k][j] = true;
        k++; 
      }
    }
  }

  for (ll i = 0; i < N; i ++) { for (ll j = 0; j < M; j++) visited[i][j] = false;}

  // // setting falls for Type 1 gravity
  for (ll i = N-1; i >= 0; i--) {
    for (ll j = 0; j < M; j++) {
      if (visited[i][j]) continue;
      ll k = i;
      while (k >= 0 && grid[k][j] != 1) { 
        // cout << "fall from: " << k << "," << j << endl;
        falls1[k][j] = {i,j};
        visited[k][j] = true;
        k--;
      }
    }
  }
 
  // for (ll i = 0; i < N; i++) {
  //   for (ll j = 0; j < M; j++) {
  //     cout << grid[i][j] << " ";
  //   } 
  //   cout << endl;
  // } 

  // for (ll i = 0; i < N; i++) {
  //   for (ll j = 0; j < M; j++) {
  //     cout << falls0[i][j].first << "," << falls0[i][j].second << " ";
  //   }
  //   cout << endl;
  // }

  for (ll i = 0; i < N; i ++) { for (ll j = 0; j < M; j++) {visited[i][j] = false;  distances[i][j] = -1; }} // set -1 !

  pq.push({0, 1, start.first, start.second}); // add start state (-moves, (x, y) ) 
  while (!pq.empty()) {
    

      // extract item from pq
      int moves = pq.top()[0];
      int dir = pq.top()[1];
      int px = pq.top()[2];
      int py = pq.top()[3];

  
      pq.pop();
      if ( grid[px][py] == 1) continue;
      // cout << "investigating: " << px <<"," << py << "  dir=" << dir << ", fall to: ";
      ll x, y;
      if (dir == 0) {
        pi a = falls0[px][py]; 
        x = a.first; y = a.second;
      }
      else if (dir == 1) {
        pi a = falls1[px][py];
        x = a.first; y = a.second;
      }
      if ((px <= end.first && end.first <= x) || (px >= end.first && end.first >= x)) { // px <= end.x <= fall x OR px >= end.x >= fall x
        if (y == end.second) {
          fout << -moves;
          return 0;
        }
      }

      // cout << x <<"," << y << endl;
      if (visited[x][y] || (grid[x][y] == -1 && dir == 1) || (grid[x][y] == -2 && dir == 0)) { // don't visit if already done so
          continue;
      }
      visited[x][y] = true; // current spot is visited
      distances[x][y] = -moves;
 
      

      // cout << "registering moves: " << -moves << " for " << x << ", " << y << endl; 
      // transitions - check add function
      if (y > 0 && !visited[x][y-1]) {
        pq.push({moves, dir, x, y-1});
      }
      if (y < M-1 && !visited[x][y+1]) {
        pq.push({moves, dir, x, y+1});
      }
      pq.push({moves-1, (dir + 1) % 2, x, y});

  }

  // for (ll i = 0; i < N; i++) { 
  //   for (ll j = 0; j < M; j++) {
  //     if (distances[i][j] == -1) cout  << " "<< distances[i][j];  
  //     else cout << "  "<< distances[i][j] ; 
  //   }
  //   cout << endl;
  // }

  fout << distances[end.first][end.second];

 
}