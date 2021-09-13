#include<bits/stdc++.h>
#define MAXN 505
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll N, K;

// done!
// Marathon is another scan DP problem - see what's the best distance you can achieve arriving at [i] with EXACTLY [j] skips - you have to scan backwards and see if you do x skips to get to i, what was the distance from point [i-x] with [j-x] skips. something like that.
// At each point, the mantra is still a take or no take - take no skip, where the x = 0, or take a skip or more, where the x is = j.
// VERY IMPORTANT to have your limits between i and j and other moveable variables like x! look at lines 35 and 40 - 35: we can't have more skips than we have points. 40: we can't have more skips than we have points when we are scanning backwards.

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll pts[MAXN][2];
ll dp[MAXN][MAXN];

ll dist(ll a, ll b) {
  return abs(pts[a][0] - pts[b][0]) + abs(pts[a][1] - pts[b][1]);
} 

main() { 
  FIO;
  freopen("marathon.in", "r", stdin);
  ofstream fout("marathon.out");
  cin >> N >> K;

  for (ll i = 0; i < N; i++) {
    cin >> pts[i][0] >> pts[i][1];
  }
 
  for (ll i = 0; i < N; i++) {
    for (ll j = 0; j <= K; j++) {
      if (j >= i) continue;
      ll fill = 1E9;
      // cout << "check i: " << i << " with max skips j: " << j << endl;
      for (ll x = 0; x <= j; x++) { // for all possible # of skips made right before to get to this check   
        // cout << "expected skips for before: "   << j-x << endl;
        if (j-x < i-x-1 || j-x == 0) {
          // cout << "using " << x << " skips, from " << i-x-1 << " to " << i << " with distance: " << dist(i-x-1, i)  << endl;
          fill = min(fill, dp[i-x-1][j- x] + dist(i-x-1, i));
          dp[i][j]= fill;
        }
      }
      cout << "final dp dist: " << dp[i][j] << endl;
      

    }
  }

  // for (ll i = 0; i < N; i++) {
  //   for (ll j = 0; j <= K; j++) {
  //     cout << dp[i][j] << " ";
  //   }
  //   cout << endl; 
  // } 

  ll ans = 1E9;
  for (ll i = 0; i <= K; i++) {
    ans = min(ans, dp[N-1][i]);
  }
  fout << ans;
}