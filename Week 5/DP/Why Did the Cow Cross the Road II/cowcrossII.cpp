#include<bits/stdc++.h>
#define MAXN 1005
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll N;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll R[MAXN];
ll L[MAXN];
ll dp[MAXN][MAXN];

bool check(ll a, ll b) {
  return (abs(R[a]-L[b]) <= 4);
}

int main() { 
  FIO;
  freopen("nocross.in", "r", stdin);
  ofstream fout("nocross.out");

  cin >> N;
  for (ll i = 0; i < N; i++) cin >> R[i];
  for (ll i = 0; i < N; i++) cin >> L[i];

  dp[0][0] = check(0,0);

  for (ll i = 0; i < N; i++) {
    for (ll j = 0; j < N; j++) {
      ll a = -1; ll b = -1; ll c = -1;
      if (i > 0) a = dp[i-1][j]; 
      if (j > 0) b = dp[i][j-1];
      if (i > 0 && j > 0) c = dp[i-1][j-1] + check(i,j);
      if (i == 0 || j == 0) c = check(i,j);
      if (i > 0 || j > 0) dp[i][j] = max(max(a,b), c);
    }
  }

  // for (ll i = 0; i < N; i++) {
  //   for (ll j = 0; j < N; j++) {
  //     cout << dp[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  fout << dp[N-1][N-1];
}
/*
JUST GO FORTH AND TRY APPLYING DIFFERENT DP TYPES TO THE PROBLEM
=> We clearly see that [i][j] might represent max # of crosswalks between indices i and j => Let's try RANGE DP! 
=> Different trains of thoughts:
=> maybe like 248, we could do [i][j] = max([i][i+1] + [i+1][j], [i][i+2] + [i+2][j]...)
=> based on our state, intuitively, our base case could be [i][i] = 1
=> ***this state is wrong, but please remember that when finding base case just be intuitive and think what's obvious to find from the beginning, or try working out the DP table and seeing what you need to calculate.

=> This state doesn't seem to be working. Please try a different one. Aren't we working with two lists?
=> [i][j] = max # of friendly crossroads we can make with first i cells on the left crossroad and j cells on the right one
=> clearly, it isn't SCAN DP and can be constant transitions
[i][j] = ?
how do we consider a new path from idx i -> j? (TAKE CASE)
   -> [i-1][j-1] + 1 if path exists
consider [i-1][j] - we can consider this, but we can't add any new path from idx i to j. or any new paths at all.
consider [i][j-1] - same problem as above

so i guess max([i-1][j-1] + 1, [i-1][j], [i][j-1])?

COMPREHENSIVENESS CHECK - DOES YOUR DP COVER AS MANY CASES AS NEEDED? (Is the state comprehensive enough)
Does it cover all possible paths idx i -> idx j? If these questions worry you, manipulate your state to see
answer: you just the right [i][j] and YES, you can cover all possible idx i -> idx j crossroads
Like Taming the Herd, analyze your state to see if it is correct and offers any other clues
another mantra - if you have [x][y], try considering transitions from [x-1][y], [x][y-1], [x-1][y-1]. extend that to N dimensions


ld returned 1 exit status => make it "int main"
*/

