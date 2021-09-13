#include<bits/stdc++.h>
#define MAXN 1005
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;

ll N;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll dp[MAXN][MAXN][2];
vector<ll> cows;


main() { 
  FIO;
  freopen("cowrun.in", "r", stdin);
  ofstream fout("cowrun.out");
  cin >> N;
  for (ll i = 0; i < N; i++) {
    ll a; cin >> a;cows.push_back(a);
  }
  sort(cows.begin(), cows.end());

  

  for(ll i = 0; i < N; i++) {
    dp[i][i][0] = abs(cows[i])*N; 
    dp[i][i][1] = abs(cows[i])*N;
  }

  

  for (ll i = N-1; i >= 0; i--) {
    for (ll j = 0; j < N; j++) {
      if (i >= j) continue;
      dp[i][j][0] = min(abs(cows[j]-cows[i]) * (N-(j-i)) + dp[i+1][j][1], abs(cows[i+1]-cows[i]) * (N-(j-i)) + dp[i+1][j][0]);
      if (j > 0) {
        dp[i][j][1] = min(abs(cows[j]-cows[j-1]) * (N-(j-i)) + dp[i][j-1][1], abs(cows[j]-cows[i]) * (N-(j-i)) + dp[i][j-1][0]);
      }
    }
  }

  // for (ll i = 0; i < N; i++) {
  //   for (ll j = 0; j < N; j++) {
  //     cout << dp[i][j][0]<< "," << dp[i][j][1] << " ";
  //   }
  //   cout << endl;
  // }
  

  fout << min(dp[0][N-1][0],dp[0][N-1][1]); 
}