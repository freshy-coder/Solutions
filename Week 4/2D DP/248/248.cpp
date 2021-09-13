#include<bits/stdc++.h>
#define MAXN 250
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll N;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll seq[MAXN];
ll dp[MAXN][MAXN];

// :DD
// a cool DP problem
// didn't know where to start, but since we're combining things over a range, just tried the range 2D DP setup to see where it would lead us
// dp[i][j] = something resultant of combining everything from i->j
// A CASE OF SCAN DP (isn't an O(1) computation to get the DP cell, but must scan a whole range). Did the intuitive and just tried looking at each of dp[i][k] and dp[k+1][j], worked because N is very low
// Each dp[i][j] only has to store the max of combining from i->j! and only has to store a value if i->j can be combined at all!! This seems counterintuitive and there won't be one SINGLE ANSWER STATE.  But it makes sense, is "specific," and we can scan to find the max answer.

// just like in Cow Hopscotch, if it is a DP problem and N is quite low, it might be some sort of Scan Dp
// remember to only look at i < j if that's what you want. make sure to have those types of conditions or else it really screws stuff up
main() { 
  FIO;
  freopen("248.in", "r", stdin);
  ofstream fout("248.out");

  cin >> N;

  for (ll i = 0; i < MAXN; i++) {
    for (ll j = 0; j < MAXN; j++) {
      dp[i][j] = -1;
    }
  }

  for (ll i = 0; i < N; i++) {
    cin >> seq[i];
    dp[i][i] = seq[i];
  }
  for (ll i = N-1; i >= 0; i--) {
    for (ll j = 0; j< N; j++) {
      if (i >= j) continue;
      // filling dp[i][j]
      ll fill = -1;
      // cout << i << ", " << j << endl;
      for (ll k = i; k < j; k++) {
        ll a = dp[i][k];
        ll b = dp[k+1][j];
        // cout << "test: " << i <<"," << k <<": " << a << " and " << k+1 << "," << j << ": " << b << endl;
        if (a == b) {
          fill = max(fill, a+1);
        }
      }
      dp[i][j] = fill;
    }
  }
  ll ans = -1;
  for (ll i = 0; i < N; i++) {
    for (ll j = 0; j < N; j++) {
      // if (dp[i][j] < 0) cout << " " << dp[i][j];
      // else cout <<  "  " << dp[i][j];
      ans = max(dp[i][j], ans);
    }
    // cout << endl;
  }
  fout << ans;
}