/*

Solution 1: DP[N][T] - erroneous but would have worked.
Solution 2: DP[N][W] = max T - the thinking strategy here is that in the previous solution, it's hard to guarantee the correctness because W has a requirement. In this case, we can just focus on one value of W
In addition, we can treat all weights above W as just W; it doesn't matter what they are because their inclusion satisfies the weight req.
Solution 3: binary search on possible ratio, use DP to see if you can make that ratio. Lies in doing some math and realizing beccause you are minimizing the ratio, you can binary search on it

go back in your notes too

got memory error again = array way to big
make sure to put int main
and make the memory a BIT higher if needed

*/

#include<bits/stdc++.h>
#define MAXN 252
using namespace std;
typedef int ll;
typedef pair<ll, ll> pi;
typedef long double ld;
ll N, W;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

#define DIM 250002


ll dp[MAXN][DIM];
vector<pi> cows;

int main() { 
  FIO;
  freopen("talent.in", "r", stdin);
  ofstream fout("talent.out");

  cin >> N >> W;
ll total = 0;
  for (ll i = 0; i < N;i ++) {
    ll a, b; cin >> a>>b; cows.push_back({b, a}); // talent then weight
    total += b;
  }

  sort(cows.begin(), cows.end());
  cows.insert(cows.begin(), {0,0});
  

  for (ll i = 0; i < MAXN; i++) { // OOB errors most definitely - both on high end and low/negative end
    for (ll j = 0; j < DIM; j++) {
      dp[i][j] = 1E9;
    }
  }

  // we are going by TALENT, trying to MINIMIZE weight
  for (ll i  =1; i <=N; i++) {
    for (ll j = 1; j <= total; j++) {
      // dp[i][j] = 1E9;
      // if (i == 0 || j == 0) {
      //   dp[i][j] = 0;
      // }
      // else {
      ll a = 1E9;
      ll b = 1E9; 
      // we can only consider possible cells

      if (dp[i-1][j] != 1E9) {
        a = dp[i-1][j];
      }
      if ((j >= cows[i].first && dp[i-1][j-cows[i].first] != 1E9)) {
        b = dp[i-1][j-cows[i].first] + cows[i].second;
      }
      if (cows[i].first == j) {
        b = cows[i].second;
      }
      dp[i][j] = min(a,b);
        
      // }

      // cout << "i, j: " << i << ", " << j << ", setting: " << dp[i][j] << endl;
      
    } 
  }
  
  ll ratio = -1E9;
  for (ll i = 0; i <= N; i++) {
    for (ll j = 0; j <= total; j++) {
      ll t = j;
      ll w = dp[i][j];
      if (w >= W && dp[i][j] != 1E9 && ((float) t/w)*1000 > ratio) {
        ratio =   ((float) t/w)*1000;
        // cout << "t: " << t << " and w: " <<  w << endl;
      }
    }
  }
  
  fout << ratio;

}