#include<bits/stdc++.h>
#define MAXN 2005 //change. SET A SPACIOUS MAXN WHEN TESTING SO YOU DONT MESS UP WITH GARBAGE VALS OR SHIT
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll N, a, b;

// I got the 1e+0x error again when outputting answer.
// 1) COUT.PRECISION()! JUST SET THIS TO A BIG VALUE. OR FOUT.PRECISION()
// I guess you should always do this, but especially in cases where they specify numbers will be pretty big OR WHEN YOU'RE DEALING WITH DECIMALS!!!
// it should tell you but if it doesn't and it seems like you need it (read above) then just put it in
// 1) NEVER. EVER. USE. INTS. Doesn't quite fix the problem.
// 2) Try Cast to larger data type when outputting to avoid scientific notation! Casting to (ll) seemed to fix the issue with Bessie Slows Down. Not here though. Tried (ld) too. We need to output a decimal in this case.


// HOW DO I AVOID SCIENTIFIC NOTATION?

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
ll dp[MAXN];

int main() { 
  FIO;
  freopen("wifi.in", "r", stdin);
  ofstream fout("wifi.out");
  cin >> N >> a >> b;
  
  vector<ll> pos; 
  pos.push_back(0); // filler. AVOID USING INDICES TO INSERT WITH VECTORS.

  // If you're doing the thing where you multiply by 2 to avoid decimals, GET EVERYTHING x2!!! Look at my notes.

  dp[0]=0; // base case

  for (ll i = 0; i < N; i++) {
    ll x; cin >> x; pos.push_back(2*x); // X2 HERE WITH THE DISTANCES
  }
  sort(pos.begin(), pos.end());

  for (ll i = 1; i <= N; i++) {
    dp[i] = 1E9;
    for (ll s = 1; s <= i; s++) {
      dp[i] = min(dp[i], dp[s-1] + 2*a + (b*(pos[i]-pos[s])/2)); // X2 HERE WITH VALUE OF a VARIABLE. the b*(pos) doesn't have to be multiplied up because the pos[i]'s themselves are already multiplied up in line #23
    }
  }

  fout.precision(10); // sig figs. must set if printing out, casting isn't as reliable
  fout << dp[N]/ ((ld) 2.0); // Everything was multipled with a factor of 2. Make it a decimal again here.
  
}   