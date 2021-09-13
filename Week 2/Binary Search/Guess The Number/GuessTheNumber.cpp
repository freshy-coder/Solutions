#include<bits/stdc++.h>
#define MAXN 200005 //change. SET A SPACIOUS MAXN WHEN TESTING SO YOU DONT MESS UP WITH GARBAGE VALS OR SHIT
using namespace std;
typedef pair<long long,long long> pi;
typedef long long ll;
typedef long double ld;
ll N, D, M;
 
#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
 
 
int main() { 
  // freopen("in", "r", stdin); // comment out
  FIO;
 
  ll a = 1; ll b = 1E6; ll mid;// what should be the best params to avoid inf loops? one off outside?
  // if just trying to find "the one," is that smallest or largest?

  // this is a largest x binsearch! hard to realize. we need to find the largest x that outputs >=
  while (a != b) {
    mid = (a+b+1)/2;
    // cout << a << " and " << mid << " and " << b<< endl;
    cout << mid << endl;
    fflush(stdout);
    string c; cin >> c;
    if (c == ">=") {
      a = mid;
    }
    else {
      b = mid-1;
    }
  }
 
  cout << "! " << a;
 
 
}   
 
// 648712