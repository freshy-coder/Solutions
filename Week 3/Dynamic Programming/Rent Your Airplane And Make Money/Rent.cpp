#include<bits/stdc++.h>
#define MAXN 10005 //change. SET A SPACIOUS MAXN WHEN TESTING SO YOU DONT MESS UP WITH GARBAGE VALS OR SHIT
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll T, N;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
ll dp[MAXN];

int main() { 
  FIO;
  // freopen("in", "r", stdin);
  
  cin >> T;

  for (ll i = 0; i < T; i++) { // only one test case atm - this is a good tactic to use when writing code at first
    cin >> N;

    // vector<pi> ends; // <end, ID>
    vector<vector<ll>> rents; // at index ID: <end, start, cost>
    rents.push_back({0,0,0});
    // READING AND SORTING INPUT BY END POINT
    for (ll i = 0; i < N; i++) {
      ll a, b, c; cin >> a >> b >> c;
      rents.push_back({a+b, a, c}); 
    }
    sort(rents.begin(), rents.end());

    // PRINTING INTPUT
    // for (auto item : rents) {
    //   for (auto i : item) {
    //     cout << i << " ";
    //   }
    //   cout << endl;
    // }

    // FINDING PRE: index of last interval ending before it
    vector<ll> pre;
    pre.push_back(0);

    for (ll i = 1; i <= N; i++) {
      ll s = rents[i][1];
      // cout << i << ": " << s << endl;
      ll a = 0; ll b = N-1; ll mid;
      while (a != b) {
        mid = (a+b+1)/2;
        if (rents[mid][0] < s) {
           a = mid;
        }
        else {
          b = mid-1;
        }
      }
      // cout <<"prev of: " << i << " is: " << a << endl;
      pre.push_back(a);
    }
    // for (auto item : pre) {
      // cout << item << " ";
    // }
  
    // DP DP DP DP
    ll dp[MAXN]; fill(dp, dp+MAXN, 0);
    for (ll i = 1; i <= N; i++) {
      dp[i] = max(dp[i-1], dp[pre[i]] + rents[i][2]);
    }

    // cout << endl << "ans: " << dp[N]; 
    cout << dp[N] << endl;

  }
}   