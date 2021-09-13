#include<bits/stdc++.h>
#define MAXN 1005
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll dp [MAXN][MAXN];
ll pos_fj[MAXN][2];
ll pos_b[MAXN][2];

// this is one of the example problems
// it is possible to set the dp to like a 0, 1E9, -1, etc. while looping thru it
// can use an array with [2] as a dimension to store points

main() { 
  FIO;
  freopen("radio.in", "r", stdin);
  ofstream fout("radio.out");

  ll n, m;
  cin >> n >> m;
  pi fjp; cin >> fjp.first >> fjp.second;
  pos_fj[0][0] = fjp.first; pos_fj[0][1] = fjp.second;
  pi bp; cin >> bp.first >> bp.second;
  pos_b[0][0] = bp.first; pos_b[0][1] = bp.second;

  string s; cin >> s;
  for (ll i = 0; i < n; i++) {
    if (s.substr(i,1) == "N") {
      pos_fj[i+1][0]=fjp.first; pos_fj[i+1][1] = fjp.second+1;
    }
    if (s.substr(i,1) == "E") {
      pos_fj[i+1][0]=fjp.first+1; pos_fj[i+1][1] = fjp.second;
    }
    if (s.substr(i,1) == "S") {
      pos_fj[i+1][0]=fjp.first; pos_fj[i+1][1] = fjp.second-1;
    }
    if (s.substr(i,1) == "W") {
      pos_fj[i+1][0]=fjp.first-1; pos_fj[i+1][1] = fjp.second;
    }
    fjp = {pos_fj[i+1][0], pos_fj[i+1][1]};
    // cout << pos_fj[i+1][0] << ", " << pos_fj[i+1][1] << endl;
  }
  cout << endl;
  cin >> s;
  for (ll i = 0; i < m; i++) {
    if (s.substr(i,1) == "N") {
      pos_b[i+1][0]=bp.first; pos_b[i+1][1] = bp.second+1;
    }
    if (s.substr(i,1) == "E") {
      pos_b[i+1][0]=bp.first+1; pos_b[i+1][1] = bp.second;
    }
    if (s.substr(i,1) == "S") {
      pos_b[i+1][0]=bp.first; pos_b[i+1][1] = bp.second-1;
    }
    if (s.substr(i,1) == "W") {
      pos_b[i+1][0]=bp.first-1; pos_b[i+1][1] = bp.second;
    }
    bp = {pos_b[i+1][0], pos_b[i+1][1]};
    // cout << pos_b[i+1][0] << ", " << pos_b[i+1][1] << endl;
  }

  dp[0][0] = 0; 

  for(ll i = 0;i <= n; i++) {
    for(ll j = 0;j <= m; j++) { 

      if (i != 0 || j != 0) {
        // cout << "checking: " << i << ", " << j << endl;
        dp[i][j] = 1E9;
        if(i != 0) {
          dp[i][j] = min(dp[i][j], dp[i-1][j]); 
        } 
        if(j != 0) {
          dp[i][j] = min(dp[i][j], dp[i][j-1]); 
        } 
        if(i != 0 && j != 0) {
          dp[i][j] = min(dp[i][j], dp[i-1][j-1]); 
        } 
        // cout << "before add: "<< dp[i][j] << endl;
        dp[i][j] += (pos_fj[i][0] - pos_b[j][0])*(pos_fj[i][0] - pos_b[j][0]) + (pos_fj[i][1] - pos_b[j][1])*(pos_fj[i][1]-pos_b[j][1]);
        // cout << "two cows: (" << pos_fj[i][0] << "," << pos_fj[i][1] << "); (" << pos_b[i][0] << "," << pos_b[i][1] << ")" << endl;
        // cout << (pos_fj[i][0] - pos_b[j][0])*(pos_fj[i][0] - pos_b[j][0]) << " and " << (pos_fj[i][1] - pos_b[j][1])-(pos_fj[i][1]-pos_b[j][1]) << endl;
        // cout << dp[i][j] << endl;
    }
  }
}
// for(int i = 0;i <= n; i++) {
//     for(int j = 0;j <= m; j++) {
//       cout << dp[i][j] << " ";
//     }
//     cout << endl;
//   }
fout << dp[n][m];




}


// initialize everything and debug with ideone