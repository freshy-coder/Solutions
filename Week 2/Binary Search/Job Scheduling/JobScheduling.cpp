#include<bits/stdc++.h>
#define MAXN 1000000 //change. SET A SPACIOUS MAXN WHEN TESTING SO YOU DONT MESS UP WITH GARBAGE VALS OR SHIT
using namespace std;
typedef pair<int, int> pi;
typedef int ll;
ll N, D, M;

// THIS PROBLEM HAD HUGE ISSUES WITH SEGFAULTS/MEMORY LIMITS. Check your array loops/limits you use WITHIN your code are correct. they may seem correct just because they are too large for sample input. Match it with the input/definitions.

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
// vector<ll> jobs;
vector<pi> jobs_save;
ll days[MAXN]; // days needs MAXN because thats max # of machines.
vector<ll> plan[100005]; // this gave me a MLE when i had MAXN instead of this number for plan days. because plan holds number of days which is 1E5, not 1E6 -> had to change.

bool make_plan(ll machs) {

  fill(days, days+MAXN, 0);

  for (int i=0; i < M; i++) {
    ll machID = i % machs;

    days[machID] = max(days[machID]+1, jobs_save[i].first); // ++ vs +1, obstructs with comparison.
    plan[days[machID]-1].push_back(jobs_save[i].second+1);
  }
  return true;
}

bool works(ll machs) {

  fill(days, days+MAXN, 0);

  for (int i=0; i < M; i++) {
    ll machID = i % machs;
    // cout << machID << " ";

    days[machID] = max(days[machID]+1, jobs_save[i].first); // ++ vs +1, obstructs with comparison.
    if ((days[machID] - jobs_save[i].first) > D){
      return false;
    }
  }
  return true;
}

int main() { 
  FIO;
  freopen("in", "r", stdin);
  cin >> N >> D >> M;

  
  for (int i = 0; i < M; i ++) {
    ll a; cin >> a; 
    // jobs.push_back(a);
    jobs_save.push_back({a,i});
  }

  // sort(jobs.begin(), jobs.end());
  sort(jobs_save.begin(), jobs_save.end());

  ll a = 1; ll b = 1E6; ll mid;
  while (a != b) {
    mid = (a+b)/2;
    // cout << a << " and " << mid << " and " << b<< endl;

    if (works(mid)) {
      b = mid;
    }
    else {
      a = mid + 1;
    }
  }

  cout << a << endl;

  make_plan(a);
  for (ll i = 0; i < N; i++) {
    for (auto i : plan[i]) {
      cout << i << " ";
    }
    cout << "0" << endl;

  }
}   