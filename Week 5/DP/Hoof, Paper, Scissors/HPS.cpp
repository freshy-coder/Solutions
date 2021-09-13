#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

/*
exemplary problem. pay attention to:
if you get an error like <weird file path> Error: value of something too large for field of 4 bytes at etc. etc. -> this is making an array or something that is way too large
so on that note, CHECK YOUR DIMENSIONS! if you're doing N*K, DO NOT DO N*N!!!
Check dimensions both in array creation and in your for loop - pay attention if you need to start at 1 or 0 (don't need to do 1 if you have a whole 0 base case filled in), if you are 1 or 0 indexed, and if you are traversing on the correct amount N, M, K, etc.
*/

ll N, K;

ll FJ[MAXN];
ll dp[MAXN][21][3];

main() { 
  FIO;
  freopen("hps.in", "r", stdin);
  ofstream fout("hps.out");
  cin >> N >> K;

  for (ll i = 1; i <= N; i++) {
    string a; cin >> a; 
    if (a == "H") FJ[i] = 0; 
    if (a == "P") FJ[i] = 1;
    if (a == "S") FJ[i] = 2;
    // cout << FJ[i] << endl;
  }

  for (ll j = 0; j <= N; j++) {
    for (ll k = 0; k < K; k++) {
      dp[0][j][k] = 0;
    }
  }
  
  for (ll i = 1; i <= N; i++) {
    for (ll j = 0; j <= K; j++) {

      for (ll c = 0; c < 3; c++) {
        for (ll k = 0; k < 3; k++) {
          if (c == k) dp[i][j][c] = max(dp[i][j][c], dp[i-1][j][k] + (FJ[i] == c));
          else {
            if (j>0) dp[i][j][c] = max(dp[i][j][c], dp[i-1][j-1][k] + (FJ[i] == k));
          }
        }
      }

    }
  }
// for (ll i = 0; i <= N; i++) {
//   for (ll j = 0; j <= K; j++) {
//     for (ll k = 0; k < 3; k++) {
//       cout << dp[i][j][k] << ",";
//     }
//     cout << " ";
//   }
//   cout << endl;
// }
  ll ans = 0;
  
  for (ll j = 0; j <= K; j++) {
    for (ll k = 0; k < 3; k++) {
      ans = max(ans, dp[N][j][k]);
    }
  }
  fout << ans;


}