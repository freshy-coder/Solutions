#include<bits/stdc++.h>
#define MAXN 105
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll R, C, K;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

// where to mod?
// did the very simple and intuitive DP state: each cell is # of ways to get to that cell.
// then the brute force of the DP: N = 100 =>  N^4 => for each cell, we can go through every other one to the right and down to increment it.

ll grid[MAXN][MAXN];
ll dp[MAXN][MAXN];

main() { 
  FIO;
  freopen("hopscotch.in", "r", stdin);
  ofstream fout("hopscotch.out");

  cin >> R >> C >> K;
  for (ll r = 0; r < R; r++ ) {
    for (ll c = 0; c < C; c++) {
      cin >> grid[r][c];
    }
  }
  dp[0][0] = 1;
  for (ll r = 0; r < R; r++ ) {
    for (ll c = 0; c < C; c++) {
      for (ll x = r+1; x < R; x++ ) {
        for (ll y = c+1; y < C; y++) {
          if (grid[x][y] != grid[r][c]) {
            dp[x][y]+= dp[r][c] % 1000000007;
          }
        }
      }
    }
  }
  // for (ll r = 0; r < R; r++ ) {
  //   for (ll c = 0; c < C; c++) {
  //     cout << dp[r][c] << " ";
  //   }
  //   cout << endl;
  // }
  fout << dp[R-1][C-1] % 1000000007;
}