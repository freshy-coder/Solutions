#include<bits/stdc++.h>
#define MAXN 2002
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll Hx, Gx;

// Algorithm: this is just most clearly a two-list DP problem, and once you have that, it is a simple task to figure out transitions
// Also used a static column with two dynamic columns to represent whether we are on H or G - COMMON THING TO DO! Intricate positioning
// if you do the above, it is easier to use two or three or more for loops for each of the static column's cells instead of another for loop in that dimension
// Pay attention to the problem to create your DP grid, and be nitpicky about how you handle zero or one indexed - we're starting on the first H in this problem; we don't need to consider row 0 in the DP table for H
// Fatal error was not setting MAXN correctly. Check that first above all else. c++ might not throw an error in this case.

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

pi H[MAXN];
pi G[MAXN];

ll dp[MAXN][MAXN][2];

ll dist(pi a, pi b) {
  return (a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second);
}

main() { 
  FIO;
  freopen("checklist.in", "r", stdin);
  ofstream fout("checklist.out");

  cin >> Hx >> Gx;

  for (ll i = 1; i <= Hx; i++) {
    ll a, b; cin >> a >> b; H[i] = {a,b};
  }

  for (ll i = 1; i <= Gx; i++) {
    ll a, b; cin >> a >> b; G[i] = {a,b};
  }

  for (ll i = 0; i <= Hx; i++) {
    for (ll j = 0; j <= Gx; j++) {
      dp[i][j][0] = 1E10;
      dp[i][j][1] = 1E10;
    }
  }

  dp[1][0][0] = 0;
  // cout << dist(H[1], G[1]) + dist(G[1], G[2]) + dist(G[2], G[3]) + dist(G[3], G[4]) + dist(G[4], G[5]) + dist(G[5], H[2]) + dist(H[2], H[3]) + dist(H[3], H[4]);


  for (ll i = 1; i <= Hx; i++) {
    for (ll j = 0; j <= Gx; j++) {
        ll a = 1E10; ll b = 1E10; ll c = 1E10; ll d = 1E10;

        if (i > 1) { // arriving at H
          a = dp[i-1][j][0] + dist(H[i-1], H[i]); // arriving from a previous H
          b = dp[i-1][j][1] + dist(G[j], H[i]); // arriving from a previous G

          // cout << "test: " << dist(G[j], H[i]) << endl;
          // cout <<"a: " << a << " and b: "<< b << endl;

          dp[i][j][0] = min(a,b);
        }

        if (j > 0) { // arriving at G
          if (j > 1) c = dp[i][j-1][1] + dist(G[j-1], G[j]); // arriving from a previous G
          d = dp[i][j-1][0] + dist(H[i], G[j]); // arriving from a previous H

          // cout << "test: " << dist(G[j-1], G[j]) << ", "<< dist(H[i], G[j]) << endl;
          // cout << "c: " << c << " and d: "<< d << endl;

          dp[i][j][1] = min(c,d);
        }
    }
  }
  
  fout << dp[Hx][Gx][0];
  // for (ll i = 1; i <= Hx; i++) {
  //   for (ll j = 0; j <= Gx; j++) {
  //     cout << dp[i][j][0] << "," << dp[i][j][1] << " ";
  //   }
  //   cout << endl;
  // }
  // cout << dp[Hx][Gx][0] << " and " << dp[Hx][Gx][1];
 
}