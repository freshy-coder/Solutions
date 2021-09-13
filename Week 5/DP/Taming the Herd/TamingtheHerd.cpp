#include<bits/stdc++.h>
#define MAXN 105
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll N;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);


ll dp[MAXN][MAXN][MAXN];
ll arr[MAXN];

ll calcMismatch(ll last, ll cur, bool place) { // last idx with a breakout, up to current idx, place = whether or not we place a breakout at cur
  ll mis = 0;
  ll num = 0;
  for (ll i = last+1; i <= cur; i++) {
    num++;
    if (i == cur && place) num = 0;
    if (arr[i] != num) mis++;
  }
  return mis;
}

main() { 
  FIO;
  freopen("taming.in", "r", stdin);
  ofstream fout("taming.out");
  cin >> N;

  for (ll i =1; i <= N; i++) { 
    cin >>arr[i];
  }

  for (ll i = 1; i <= N; i++) { // idx
    for (ll j = 1; j <= N; j++) { // # breakouts
      for (ll k = 1; k <= N; k++) { // last breakout idx
        if (j > i || k > i || j > k){
          continue;
        }
        
        // cout << "index: " << i << ", breakouts req: " << j << ", last breakout: " << k << " --------------------------------------"<<endl;
        
        if (k < i) { // not take case
          // cout << "take case: " << "dp of [" << k << "][" << j << "][" << k << "]" << endl;
          dp[i][j][k] = dp[k][j][k] + calcMismatch(k, i, false); 
        } 

        if (k == i) {// take case
          ll a = 1E9;
          // take case -> must go backwards to find a minimal case to add on this new breakout
          // j becomes j-1, k scans backwards, i scans backwards too because we want to build UP to current i
          
          if (i > 1) { // we can only scan backwards if we're not on the first index
          // cout << "testing: TAKE breakout at i, j-1 backwards. last breakouts " << i-1 << " to " << j-1 << endl;
            for (ll x = i-1; x >= j-1; x--) {
              if (x <= 0) continue;
              a = min(a, dp[x][j-1][x] + calcMismatch(x, i, true) );
            }
          }
          // if we ARE on the first index, then it probably is [1][1][1]
          if (i == 1) {
            // cout << "first index. calcluating mismatch if we had a breakout on day 1" << endl;
            a = (0 != arr[1]);
          }
          dp[i][j][k] = a;
        }
        if (j == 1 && i == k && i > 1) {
          dp[i][j][k] = 1E9;
        }
        // cout << "final set: " << dp[i][j][k] << endl;
        
      }
    }
  }

  for (ll j = 1; j <= N; j++) {
    ll m = 1E9;
    for (ll k = j; k <= N; k++) {
      m = min(dp[N][j][k], m);
    }
    fout << m << endl;
  }

}


 // [i][j] = {minimum mismatches with j breakouts up to point i, last breakout idx}
// afraid of equals/maybe not optimal -> have dp table have both of it!

// THINKING PROCESS
// at each step, we are trying to find the minimum mismatches that could have occured per breakout amount
// => you can pretty easily sense DP is involved, and see its application in "ONE type of breakout"
// at each step, could you maybe decide whether or not to have a breakout?
// => [i][j] - min mismatches at index i, j breakouts exactly 
// => can try setting state to min mismatches at index i, j breakouts exactly including one at i (requiring a breakout) => you would look at minimums from states [i-1, i-2, ... 0][j-1] to see what's the minimum mismatches we can get
// => then it gets hard to find an answer state
// => requiring a breakout is not a good idea => consider both taking a breakout at i and not taking one, take the minimum
// => our consideration of all i-1, i-2... gives us the idea to also keep track of the LAST time a breakout occured in an [i][j] state
// => [i][j] = {min mismatches, last breakout idx occured} = MIN([i-1][j-1] + (0 == seq[i]), [i-1][j] + (seq[i] == appropriate day amount after last breakout occured))
// working through test case makes us realize TAKE or NOT TAKE breakout may be equal
// =>***IF YOU ARE NOT SURE IF YOU SHOULD TAKE MINIMUM BETWEEN CHOICES, OR IF YOU SHOULD EVEN GREEDILY CHOOSE BETWEEN CHOICES, CONSIDER THEM ALL. Like in gas pipeline, considering both building up and down
// => [i][j][2] = {stats if we had a breakout here, stats if we didn't}
//*** => but now the "last idx we had a breakout" just becomes a weird stat, but remember how we used this to help us when putting down breakouts?
//*** also N = 100, can't we have more state dims? Also, our state storage is just getting weird and too complex
//*** => TRY MOVING A PART OF THE STATE CELL INTO THE STATE ITSELF => [i][j][k], k = last cell with a breakout
//*** Once you have state, go to transitions. Find Answer or Base case first if it helps. ALWAYS KEEP THE MANTRA OF TAKE OR NOT TAKE? when doing transitions
// => [i][j][k] = min(TAKE: dp[i][j-1][k->j], NOT TAKE: dp[i][j][k->j]) + according mismatches
// And once you think you've figured out the order, see if there's a cleverer way. ***Analyze state to see if it offers more clues
// Why scan k->j? And isn't "TAKE" when i == k? and "NOT TAKE" when k < i?
// So we can just for loop through the table with that in mind
