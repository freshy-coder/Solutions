#include<bits/stdc++.h>
#define MAXN 155 //change. SET A SPACIOUS MAXN WHEN TESTING SO YOU DONT MESS UP WITH GARBAGE VALS OR SHIT
using namespace std;
typedef pair<long long,long long> pi;
typedef long long ll;
typedef long double ld;
ll N;
 
#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
 
 
int main() { 
  // freopen("in", "r", stdin); // comment out
  FIO;
  cin >> N;
 
  ll assigns[MAXN]; fill(assigns, assigns+MAXN, 1);
 
  bool unique[MAXN]; fill(unique, unique+MAXN, false);
  
  vector<ll> ref;
  ref.push_back(1); unique[1] = true; assigns[1] = 1;
 
  ll res;
 
  ll prev = 1;
  for (ll i = 2; i <= N; i++) {
    cout << i << " ";
    for (ll j = 1; j <= i; j++) {
      cout << j << " ";
    }
    cout << endl; // MUST CALL AN ENDL BEFORE DOING FLUSH!
    fflush(stdout);
    cin >> res;
    if (res > prev) {
      ref.push_back(i);
      unique[i] = true;
    //   // cout << "assigning " << i << endl;
      assigns[i] = i;
    }
    prev = res;
      
  }
  // // cout << endl;
  // // for (auto item : ref) {
  // //   cout << item << endl;
  // // }
 
 
  for (ll i = 2; i <= N; i ++) {
    if (unique[i]) continue;
    ll a = 0; ll b = ref.size(); ll mid;
    while (a != b) {
      mid = (a + b) / 2;
      
      // test party a->mid and i
      // cout << "building output: " << endl; 
      cout << mid-a+2 << " ";
      for (ll x = a; x <= mid; x++) {
        cout << ref[x] << " ";
      }
      cout << i << endl;
 
      fflush(stdout);
      cin >> res;
 
      if (res == mid-a+1) {
        // cout << "testing lower half " << endl;
        b = mid;
      }
      else {
        // cout << "testing upper half" << endl;
        a = mid + 1;
      }
       
    }
    // cout << i << " belongs to: " << ref[a] << endl;
    assigns[i] = ref[a];
  }
  // cout <<"ans: ";
  // for (ll i = 1; i <= N; i++) {
  //   cout << assigns[i] << " ";
  // }
  // cout << endl;
 
  cout << "0 ";
  map<ll,ll> x;
  ll count = 0;
  for (ll i = 1; i <= N; i++) {
    if (x.find(assigns[i]) == x.end()) {
      x[assigns[i]] = ++count;
      // cout << "assigining " << x[assigns[i]] << " to " << assigns[i] << endl;
    }
    cout << x[assigns[i]] << " "; 
  }
 
  cout << endl;
  fflush(stdout);
 
 
 
}