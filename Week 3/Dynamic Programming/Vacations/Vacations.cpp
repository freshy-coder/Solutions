#include<bits/stdc++.h>
#define MAXN 105 //change. SET A SPACIOUS MAXN WHEN TESTING SO YOU DONT MESS UP WITH GARBAGE VALS OR SHIT
using namespace std;
typedef pair<int, int> pi;
typedef int ll;
ll N, D, M;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
ll dp[MAXN]; 
ll op[MAXN]; // 0 means rest, 1 means contest, 2 means sport/gym
ll conf[MAXN];

// Algorithm: assign each spot the "ideal" activity - gym if only gym's open, contest if only contest's open, if both open then NOT what we did yesterday, if both close then just rest
// dp[i] = min number of rests needed up to day i
// op[i] = activity on day i
// ref(idx, act) function is to backtrack O(N) and see if we can really implement the ideal activity. takes advantage of the fact that dp[i] is already optimal; it doesn't want to add new breaks or even remove breaks from previous.
// => this addition and then backtracking/pruning will increase our runtime, but seems to be a theme
// This theme of going back O(N) backwards also shows up in Wifi Setup

// Thought process:
// recursive method: f(N): on day N, try setting a rest & do f(N-1), try setting a contest & do f(N-1), try setting a gym & do f(N-1)
// => clearly duplicate work => dp
// tried setting index as state, tried setting dp[i] = answer
// dp[i] can clearly be based on dp[i-1] and op[i-1]. Seems like greedy works? NO.
// TRIED MAKING PROBLEMATIC INPUT, one where we would have to backtrack and complex dp calcs are necessary. Tried backtracking common sensically. Simplified backtracking because we don't need to care about adding/subtracting breaks and changing any dp[1..i]


bool ref(ll idx, ll act) {
  // cout << "reform called on: " << idx << " to have " << act << endl;

  if (idx == 0) return true;

  else if (act == 2) {
    if (conf[idx] == 0 || conf[idx] == 1) return false;
    if (op[idx-1] != 2) { // check if this move is valid based on previous
      op[idx] = act; return true;
    } // if the previous move is identical, try continue reforms
    else {
      return (ref(idx-1, 1));
    }
  }

  else if (act == 1) {
    if (conf[idx] == 0 || conf[idx] == 2) return false;
    if (op[idx-1] != 1) {
      op[idx] = act; return true;
    }
    else {
      return ref(idx-1, 2);
    }
  }

  return true;
}

int main() { 
  FIO;
  freopen("in", "r", stdin);
  cin >> N;

  for (ll i = 0; i < N; i++) {
    cin >> conf[i+1];
    // cout << conf[i+1] << " ";
  }
  // cout << endl;

  for (ll i = 1; i <= N; i++) {
    for (auto item : op) {
    // cout << item << " ";
  }
  // cout << endl;

    if (conf[i] == 3) {
      // cout << "all open" << endl;
      if (op[i-1] == 1) {
        dp[i] = dp[i-1];
        op[i] = 2; 
        // cout << "setting " << i << " to " << 2 << endl;
      }
      else {
        dp[i] = dp[i-1];
        op[i] = 1;
        // cout << "setting " << i << " to " << 1 << endl;
      }
    }
    else if (conf[i] == 1) {
      // cout << "only 1 open" << endl;
      if (ref(i, 1)) {
        dp[i] = dp[i-1];
        op[i] = 1;
        // cout << "no new breaks, setting " << i << " to " << 1 << endl;
      } 
      else {
        dp[i] = dp[i-1] + 1;
        op[i] = 0;
        // cout << "new break, setting " << i << " to " << 0 << endl;
      }
    }
    else if (conf[i] == 2) {
      // cout << "only 2 open" << endl;
      if (ref(i, 2)) {
        dp[i] = dp[i-1];
        op[i] = 2;
        // cout << "no new breaks, setting " << i << " to " << 2 << endl;
      }
      else {
        dp[i] = dp[i-1] + 1;
        op[i] = 0;
        // cout << "new break, setting " << i << " to " << 0 << endl;
      }
    }
    else { // conf[i] == 0
      // cout << "both closed. new break at: " << i << endl;
      dp[i] = dp[i-1] + 1;
      op[i] = 0;
    }
  }

  // cout << "skip first: " << endl;
  // for (auto item : op) {
  //   cout << item << " ";
  // }
  // cout << endl;

  // for (auto item : dp) {
  //   cout << item << " ";
  // }

  // cout << endl << "ans: " << endl;
  cout << dp[N];
  
}   