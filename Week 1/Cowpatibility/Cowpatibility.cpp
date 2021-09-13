#include<bits/stdc++.h>
#define MAXN 50005 //change
#define FIO ios::sync_with_stdio(0); cin.tie(0); 

using namespace std;
typedef pair<long long,long long> pi;
typedef long long ll;
typedef long double ld;
ll n, m, k;
ll cows[MAXN][5]; // stores where each node will be after M steps

int main() { 
  FIO; 
  ofstream fout("cowpatibility.out");
  freopen("cowpatibility.in", "r", stdin);
  
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> cows[i][0] >> cows[i][1] >> cows[i][2] >> cows[i][3] >> cows[i][4];
  }

  map<ll, ll> ones;

  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j < 5; j++) {
      ones[cows[i][j]]++;
    }
  }

  map<vector<ll>, ll> twos;

  for (ll i = 0; i < n; i++) {
    for (auto a : cows[i]) {
      for (auto b : cows[i]) {
        if (!(a < b)) continue;
        vector<ll> x = {a,b}; twos[x]++;
      }
    }
  }

  map<vector<ll>, ll> threes;

  for (ll i = 0; i < n; i++) {

    for (auto a : cows[i]) {
      for (auto b : cows[i]) {
        for (auto c : cows[i]) {
          if (!(a < b && b < c)) continue;
          vector<ll> x = {a,b, c}; threes[x]++;
        }
      }
    }
  }

  map<vector<ll>, ll> fours;

  for (ll i = 0; i < n; i++) {
    
    for (auto a : cows[i]) {
      for (auto b : cows[i]) {
        for (auto c : cows[i]) {
          for (auto d : cows[i]) {
            if (!(a < b && b < c && c < d)) continue;
            vector<ll> x = {a,b,c,d}; fours[x]++;
          }
        }
      }
    }
  }

  map<vector<ll>, ll> fives;

  for (ll i = 0; i < n; i++) {
    
    vector<ll> x;
    for (auto a : cows[i]) { x.push_back(a); }
    sort(x.begin(), x.end()); fives[x]++;
  }
  
  ll oneP = 0, twoP = 0, threeP = 0, fourP = 0, fiveP = 0;
  for (auto x : ones) {
    oneP += ((x.second)*(x.second-1))/2;
  }
  for (auto x : twos){ 
    twoP += ((x.second)*(x.second-1))/2;
  }
  for (auto x : threes) {threeP += (x.second)*(x.second-1)/2;}
  for (auto x : fours) {fourP += (x.second)*(x.second-1)/2;}
  for (auto x : fives) {fiveP += (x.second)*(x.second-1)/2;}

  // cout << oneP << " " << twoP << " " << threeP << " " <<fourP << " " << fiveP << endl;
  fout << (n)*(n-1)/2 - (oneP - twoP + threeP - fourP + fiveP);
}

