#include<bits/stdc++.h>
#define MAXN 200009 //change. SET A SPACIOUS MAXN WHEN TESTING SO YOU DONT MESS UP WITH GARBAGE VALS OR SHIT
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pi;
ll T, N, a, b;
string s;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

// don't forget <= when doing 1-based
// don't forget to update both action array and dp (common theme)

// Alg & DP thought process
// The edge case factor in this case was the infinity I set - it wasn't high enough. Use 1E18? I think that's as high as you can go without overflow (or it just worked in this case)
// DP Details - made state your index, but that was too greedy and didn't work
// realized what's min cost at one point might not help later. Decision is to build to level 1 or 2 => must do a NX2 array that encompasses every single possibility - getting to point [i] with height 1 - [0] or height 2 - [1]
// Previous state wasn't comprehensive of all possibilities
// In this case built DP state by looking backwards and taking minimums. It might be different in other cases. 


ll dp[MAXN][2];
// ll pill[MAXN];

int main() { 
  FIO;
  // freopen("in", "r", stdin);
  cin >> T;

  for (ll t = 0; t < T; t++) {// ONLY DOING 1 T FOR NOW
    cin >> N >> a >> b >> s;

    for (ll r = 0; r < MAXN; r++) {
      for (ll c = 0; c < 2; c++) dp[r][c] = 0;
    }

    dp[0][0] = b; dp[0][1] = 1E18; 
    dp[N][1] = 1E18; 

    for (ll i = 1; i <= N; i++) {
      // cout << "on spot: " << i << endl;
      
      // Case 1: There's a crosswalk here, must build to level 2 
      if (s.substr(i,1) == "1" || s.substr(i-1,1) == "1") {
        dp[i][0] = 1E18;
        dp[i][1] = min(dp[i-1][0] + 2*b + 2*a, dp[i-1][1] + 2*b + a);
        // cout << "required crosswalk. level 2 cost: " << dp[i][1] << endl;
        continue;
      } 

      // Case 2: Building to level 1
      dp[i][0] = min(dp[i-1][0] + b + a, dp[i-1][1] + b + 2*a);
      // min(build across from previous lvl 1, build down from previous lvl 2)

      // Case 3: Building to Level 2
      dp[i][1] = min(dp[i-1][0] + 2*b + 2*a, dp[i-1][1] + 2*b + a);
      // min(build up from previous lvl 1, build across from previous level 2)

      // cout << "min cost at level 1: " << dp[i][0] << endl;
      // cout << "min cost at level 2: "<< dp[i][1] << endl;
      
    }

    // for (ll c = 1; c >= 0; c--) {
    
    //    for (ll r = 0; r < MAXN; r++) cout << dp[r][c] << " ";
    //   cout << endl;
    // }

    cout << dp[N][0] << endl;

  }

}   