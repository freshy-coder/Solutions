#include<bits/stdc++.h>
#define MAXN 1000000 //change. SET A SPACIOUS MAXN WHEN TESTING SO YOU DONT MESS UP WITH GARBAGE VALS OR SHIT
using namespace std;
typedef pair<int, int> pi;
typedef int ll;
#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll N, K;


int main() { 
  FIO;
  ofstream fout("paint.out");
  freopen("paint.in", "r", stdin);
  cin >> N >> K;

  map<ll, ll> indc;

  ll pos = 0;

  for (int i = 0; i < N; i++) {
    ll mv; char s; cin >> mv >> s;

    if (s == 'L') mv = -mv;

    ll a = pos;
    ll b = pos + mv;

    // cout << mv << " " << s << ", so a: "<< a << ", " << b <<" - -- - - - - -" << endl;

    indc[min(a,b)]++;
    indc[max(a,b)]--;
    pos = b;
  }
  // cout << "now printing " << endl;

  ll prevLoc = indc.begin()->second;
  ll layer = 0;
  ll dist = 0;
  for (auto x : indc) {
    // cout << x.first << " : " << x.second << endl;
    
    if (layer >= K) dist += x.first-prevLoc;

    layer += x.second;

    prevLoc = x.first;


  }
  fout << dist;
}   