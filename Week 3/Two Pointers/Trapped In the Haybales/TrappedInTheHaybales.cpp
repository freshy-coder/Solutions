
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <string.h>
#include <iterator> 
#include <list>
#include <cmath>
#include <math.h>
#include <unordered_map>
#define MAXN 100005 //change. 

/*
If code working locally but not usaco, it is 90% probably memory - too much usage, or segfault
OR not intialzting properly: global things are set to zero, in-function variables are set to garbage (this is true for both ide & usaco, but always good practice to initialize everything). Also might be easier to make everything global
Also integer/long long overflow is also an issue that might cause to fail on usaco

and for some reason, you can also try running it on repl or ideone instead, that might reveal an error.

The nemesis in this problem were all those segfaults I kept getting when incrementing/decrementing the two pointers.
1) Two pointers, and just dealing with inc/dec indices are very prone to OOB errors.
2) Sometimes you NEED to increment the pointer down to out of bounds to satisfy some case - Do NOT prevent this inc/dec from happening, just block any array accesses and catch it as soon as it happens
// There were many conditions in this problem like lines 90-105. Do they build on each other? Do you need to track them all? or should some break out of the loop as soon as it is found?
3) Didn't really work out, but can try to get around by adding extra items to ends of the arrays. Trace and find out how to work with these first or else it might get tricky.
*/
// also below i show how to do LOWER BOUND/UPPER BOUND ON PAIRS
// Also an interesting note is how you can turn this problem from looking at lower/upper points with lower and upper bounds, which would be log N time, but it can actually be O(1), just incrementing/decrementing pointers. 
// See if you can make something linear in this fashion; you're just dealing with an expanding range

// Algorithm: Made observation that if D = distance between nearest right and nearest left haybale, that determines if bessie can break through a haybale nearby
// Can declare LP and RP to haybales right next to her
// find farthest "stuck" RP haybale if bessie just keeps crashing left. as in, on which RP can bessie can not pass anymore for each LP? D increases as she gets farther and farther away
// then find how much hay you need to add to the LP. Keep decrementing LP
// repeat vice versa; increment RP and find the leftmost LP

// => TWO POINTERS CAN BE LP-MAJOR, RP-MAJOR, I-MAJOR, OR OTHER. CAN BE FINDING RIGHTMOST, LEFTMOST, ANYTHING.

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pi;
ll N, B;


#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

int main() { 
  FIO;
  freopen("trapped.in", "r", stdin);
  ofstream fout("trapped.out");

  cin >> N >> B;

  // can see why its linear!
  // lower bound on pairs? dont forget to cast

  vector<pi> bales;
  for (ll i = 0; i < N; i++) {
    ll a,x; cin >> a >> x;
    bales.push_back({x,a});
  }
  sort(bales.begin(), bales.end());

  auto lb = lower_bound(bales.begin(), bales.end(), make_pair(B,(ll) 0)); // use make_pair, not {}
  
  if (lb == bales.begin()) {
    fout << "-1";
    return 1;
  }
  lb--;
  ll lp = lb-bales.begin();

  auto ub = lower_bound(bales.begin(), bales.end(), make_pair(B, (ll) 0));
  if (ub == bales.end()) {
    fout << "-1";
    return 1;
  }
  ll rp = ub-bales.begin();
  
  // // cout << lp << " & " << rp << endl;
  ll ans = 1E18;
  ll stopped = 0;
  ll pass = 0;
  // finding rightmost stuck LP for increasing RP
  // ll count = 0;
  for (; rp < N; rp++) {
    ll D = bales[rp].first-bales[lp].first;

    while(lp >= 0 && D > bales[lp].second) {
      if (lp > 0) D += bales[lp].first - bales[lp-1].first;
      lp--;
      if (lp < 0) break;
    }

    bool getOut = false;
    if (rp == ub-bales.begin() && lp < 0) { // if we are on first iteration and bessie has already gotten all the way to the end of left
      pass++;
      getOut = true;
    }
    if (D <= bales[rp].second)  {
      getOut = true; // if stopped here
      stopped++;
    }
    if (lp < 0) getOut = true;
    if (getOut) break;
    

    ans = min(ans, D-bales[rp].second);
    
    // cout << "LP: " <<lp << ", RP: "<< rp << ", D: " << D << endl;
    
  }

  lp = lb-bales.begin(); rp = ub-bales.begin(); // reset
  // cout << lp << " and " << rp;
  // Finding leftmost stuck RP for decreasing LP
  for (; lp >= 0; lp--) {
    
    ll D = bales[rp].first-bales[lp].first;
    while(D > bales[rp].second) {
      if (rp < N-1) D += abs(bales[rp].first - bales[rp+1].first);      
      rp++;
      if (rp > N-1) break;
    }
    bool getOut = false;
    if (lp == lb-bales.begin() && rp > N-1) { // if we are on first iteration and bessie has already gotten all the way to the end of right
      pass++;
      getOut = true;
    }
    if (D <= bales[lp].second)  {
      getOut=true; // if stopped here
      stopped++;
    }
    
    if (rp > N-1) {
      getOut = true;
    }

    if (getOut) break;
    

    ans = min(ans, D-bales[lp].second);

  //   cout << "LP: " <<lp << ", RP: "<< rp << ", D: " << D << endl;
  }
  // // fout << "4";
  if (stopped == 2) {
    fout << "0";
    return 1;
  }
  else if (pass == 2) {
    fout << "-1";
    return 1;
  }

  fout << ans;
  return 1;

}
