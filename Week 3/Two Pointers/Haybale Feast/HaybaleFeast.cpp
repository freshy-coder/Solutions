#include<bits/stdc++.h>
#define MAXN 100005 //change. SET A SPACIOUS MAXN WHEN TESTING SO YOU DONT MESS UP WITH GARBAGE VALS OR SHIT
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pi;
ll N,M;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

// how to keep track of one max over entire interval?
// EXTREMELY BASIC TWO POINTERS
// PLEASE BE CAREFUL WITH YOUR DATASTRUCTS WHEN TRAVERSING. Sets don't allow duplicates, and if you want to do multiset so you can keep track of all values and do remove() for one element, must do multiset.erase(multiset.find)
// multiset.erase(multiset.find) erases one element
// multiset.erase(val) erases all elements with that val.

// immediately saw it as TP because we are testing valid ranges. However, you must see how increasing RP and LP fits in. In this case, its because we want to find the rightmost LP that may work for some RP, because that may lower maximum spiciness. So you have to implement that way.
// Alternatively, for the classic TP, it was leftmost LP for some RP
// That was still RP-major implementation

// Will we ever have to do LP-major implementation? rightmost/leftmost RP for some LP

// So for different problems, will it be LP-major, RP-major, rightmost, leftmost?

vector<pi> bales;

multiset<ll> maxSps;
ll totalFlavor = 0;

void add(int rp) {
  maxSps.insert(bales[rp].second);
  totalFlavor += bales[rp].first;
}

void remove(int lp) {
  maxSps.erase(maxSps.find(bales[lp].second));
  totalFlavor -= bales[lp].first;
}

int main() { 
  FIO;
  freopen("hayfeast.in", "r", stdin);
  ofstream fout("hayfeast.out");

  cin >> N >> M;

  for (ll i =0; i< N; i++) {
    ll a, b; cin >> a >> b; bales.push_back({a,b});
  }

  ll lp = 0; ll minSp = 1E18;
  for (ll rp = 0; rp < N; rp++) {
    add(rp);
    while (lp < rp && totalFlavor-bales[lp+1].first >= M) {
      remove(lp);
      lp++;
    }
    if (totalFlavor < M) continue;

    minSp = min(minSp, *maxSps.rbegin()); 

    // if (*maxSps.rbegin() == 9964 && rp-lp < 3000) {
    //   cout << "valid range: " << lp << " to " << rp << endl;
    // cout << "range flavor: " << totalFlavor << endl;
    // cout << "max range spicy: " << *maxSps.rbegin() << endl;
    // }
  }
  fout << minSp; 

}


    // while (totalFlavor < M && rp < N-1) {
    //   add(rp);
    //   rp++;
    // }
    // if (lp == rp) continue;

    // // cout << "valid range: " << lp << " to " << rp << endl;
    // // cout << "range flavor: " << totalFlavor << endl;
    // // cout << "max range spicy: " << *maxSps.rbegin() << endl;
    
    // minSp = min(minSp, *maxSps.rbegin());
    // remove(lp);