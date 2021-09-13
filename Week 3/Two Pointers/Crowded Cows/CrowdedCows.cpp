#include<bits/stdc++.h>
#define MAXN 100005 //change. SET A SPACIOUS MAXN WHEN TESTING SO YOU DONT MESS UP WITH GARBAGE VALS OR SHIT
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pi;
ll N, D;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

// don't care about cow identities, make things a lot easier

// GONNA SAY THIS RQ: Line 40 shouldn't work properly. I only wanted to remove one item from multiset. should do multiset.erase(multiset.find)

// ALG & THOUGHT PROCESS: asks us to look at a range of distance D for each cow in the line => must use two pointer to traverse & keep track of the ranges as we go across for each different cow. Came up with a two pointer scan that is item-major, changes the item then adjusts the lp and rp accordingly.
// some more things:
// when keeping track of range stats, used two different data structs to look at right side and left side. don't forget to update both when going to a new cow! (purely add & remove is not enough)
// when keeping track of range stats, just kept track of heights and not IDs. no actual identities needed! duplicate values OK -> so used multiset not set.
// prioqueue could have been used too
// also traversed items from idx 1 to N-1, because the outer stuff cannot be crowded.

// TRAVERSING THROUGH ARRAY, KEEPING TRACK OF TWO POINTERS, not going by two pointers.

// thinking strategy: simplification per range
// more or less just found TP and went for it.

// what's this solution?
/*
Alternatively, we can scan the cows in decreasing order of height, using a pair of sweep lines that move in lock step so that the upper sweep line is always at twice the height as the lower sweep line. Whenever the upper sweep line visits a cow, the position of that cow is inserted into a set data structure (i.e., a balanced binary search tree). When the lower sweep line visits a cow (say, at position x), we query this structure for the positions immediately preceding and following x (in an STL set, for example, we could use the lower_bound method to do this). The data structure contains the positions of all cows at least twice the height of the current cow, so if the predecessor and successor based on her position x are within the range x-d to x+d, then the current cow is crowded.
*/

multiset<ll> rheights; // NEED MULTIPLE OF ONE VALUE!
multiset<ll> lheights; // NEED MULTIPLE OF ONE VALUE!
vector<pi> cows;

void add(int rp) {
  rheights.insert(cows[rp].second);
}

void remove(int lp) {
  lheights.erase(cows[lp].second);
}

int main() { 
  FIO;
  freopen("crowded.in", "r", stdin);
  ofstream fout("crowded.out");
  
  cin >> N >> D;

  for (auto i = 0; i < N; i++) {
    ll x, h; cin >> x >> h; cows.push_back({x,h});
  }

  sort(cows.begin(), cows.end());
  
  ll lp = 0; ll rp = 0; ll ans = 0;
  for (ll i = 1; i < N-1; i++) {

    // while cow at left pointer isn't in left-range of subject yet, keep removing and advancing it.
    while (cows[lp].first < cows[i].first-D) { 
      remove(lp);
      lp++;
    }
    
    // while the NEXT cow is still in the right-range, keep extending it. We need to get to the largest rp possible.
    while (rp+1 < N && cows[rp+1].first <= cows[i].first+D) { 
      add(++rp);
    }

    // remove the previous cow from the right side, it is now on the left, so add it accordingly.
    rheights.erase(cows[i-1].second);
    lheights.insert(cows[i-1].second);

    if (lp == i || rp == i || lp == rp) { // if this happens, then there IS no valid range.
      continue;
    }
    
    // cout << "valid range for " << i << " : " << lp << " to " << rp << endl;
    // for (auto item : lheights) {cout << item << " ";};
    // cout << endl;
    // for (auto item: rheights) {cout << item << " ";};
    // cout << endl;
    if (lheights.lower_bound(cows[i].second*2) != lheights.end() && rheights.lower_bound(cows[i].second*2) != rheights.end()) {
      // cout << ":::: "<< i << endl;
      
      ans++;
    }
  }
  fout << ans;

}   