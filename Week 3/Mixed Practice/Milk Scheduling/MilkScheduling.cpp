#include<bits/stdc++.h>
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll N;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

bool places[10005];

// Sort and Sweep algorithm!
// For each cow, tried assigning it greedily. Greedy sort and sweep based on LARGER VALUES OF MILK, cuz that's what we want.
// TRY CHANGING YOUR SCALES - originally tried sorting by time then milk value, couldn't find a proper greedy sweep to validate which cows were possible to milk
// So instead, tried sorting by milk value, and assigning cows greedily to first available time spot.

// Thinking: Clearly some sort of sweeping and assignment

// USACO SOLUTION: Can try traversing in different ways! Backwards
/*
Instead, let us try doing the greedy approach starting at t=10000 and working towards the beginning. Again, the rule will be, at each time step, to choose the best available cow available at that time. The key difference here is that once a cow becomes available (i.e., t decreases below the cow's deadline d_i) it will always be available thereafter. Hence, we can never miss a cow by delaying to take it (unless we haven't taken it before reaching t=0).

Let us prove correctness more rigorously. Consider an execution of the algorithm, and suppose that at some point we chose a cow C, even though another cow D was available and had a better output. We will show that, no matter what schedule S results, we could have done at least as well by choosing D instead. If both C and D end up getting milked in S, we could simply swap the times of the C and D; this remains a valid schedule, and now D is taken at the given time. If D is never milked in the schedule, we could simply replace C with D and get a schedule with a higher output.

Now that we have a greedy algorithm planned out, we need to figure out how to implement it. A naive implementation would take O(dN) time (where d is the maximum deadline); there are d time steps and at each time step you have to determine the best of N cows. We can improve upon this by using a priority queue. As t decreases, any cow that becomes available gets added to the priority queue. When we need to find the best cow, we can just pop a cow off the top of the queue. Using the priority queue gives a solution of O((d + N) log N) time.
*/

bool cmp(pi a, pi b) {
  if (a.first == b.first) {
    return a.second < b.second;
  }
  return a.first > b.first;
}

int main() { 
  FIO;
  freopen("msched.in", "r", stdin);
  ofstream fout("msched.out");
  cin >> N;
  ll a,b;

  vector<pi> cows; // <milkage, deadline>
  for (ll i = 0; i < N; i++) {
    cin >> a >> b;
    cows.push_back({a, b});
  }
  sort(cows.begin(), cows.end(), cmp);

  ll milk = 0;
  for (ll i = 0; i < N; i++) {
    ll g = cows[i].first; ll d = cows[i].second;
    // cout <<"gall: " << g << " deadline: " <<d << endl;
    for (ll p = d; p >= 1; p--) {
      if (!places[p]) {
        places[p] = true;
        milk+= g;
        break;
      }
    }
  }
  fout << milk;


}   