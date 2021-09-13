#include<bits/stdc++.h>
#define MAXN 10005
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll N, M, T;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll places[MAXN];

bool visited[MAXN];
priority_queue<pi> pq;

vector<pi> adj[MAXN];
ll distances[MAXN];

// Algorithm: perform dijkstra to get the path from each cow to barn. Use reverse-dijkstra to get the befores of each node, then track each path. Save the number of cows that pass through each node to a map. Calculate how much time you would save for each node using # of cows passing through, its distance to barn, and the length of shortcut.

// Thought process: did basic things, such as running dijkstra N times or just choosing the node that was farthest.
// Tried bogus test cases, like 1000 fields 1 distance away from the barn and one field 500 distance away => we find the point of interest is actually the number of cows passing through points. 
// and we knew to do dijkstra in the first place, clearly, because all cows are going shortest path to barn.

main() { 
  FIO;
  freopen("shortcut.in", "r", stdin);
  ofstream fout("shortcut.out");
  cin >> N >> M >> T;

  for (int i = 1; i <N+1; i++) {
    cin >> places[i];
  }

  for (int i = 0; i < M; i++) {
    ll a, b, t; cin >> a >> b >> t;
    adj[a].push_back({b,t}); adj[b].push_back({a,t});
  }
  

  memset(visited, false, sizeof(visited) ); // reset visited array
  pq.push(make_pair(0, 1)); // add start state (-moves, (x, y) ) 
  distances[1]=0;
  while (!pq.empty()) {

      // extract item from pq
      int moves = pq.top().first;
      int x = pq.top().second;
      pq.pop();
      
      if (visited[x]) { // don't visit if already done so (equivalent of checking before visit if the new dstance is better)
          continue;
      }
      visited[x] = true; // current spot is visited
      distances[x] = -moves;
      
      // transitions
      for (auto nbr : adj[x]) {
        pq.push({moves-nbr.second, nbr.first});
      }
  }

  ll befores[MAXN];
  memset(befores, -1, sizeof(befores));
  for (int i = 1; i <= N; i++) {
    ll can = 1E9;
    for (auto nbr : adj[i]) {
      if (distances[nbr.first]+nbr.second == distances[i] && nbr.first < can) {
        can = nbr.first;
      }
    }
    befores[i] = can;
  }

  ll visits[MAXN];
  memset(visits, 0, sizeof(visits));
  for (int i = 1; i <= N; i++) {
    ll curr = i;
    while(curr != 1) {
      visits[curr] += places[i];
      curr = befores[curr];
    }
  }

  ll ans = 0;
  for (int i = 1; i <= N; i++) {
    ans = max(ans, (distances[i]-T)*visits[i]);
  }
  fout << ans << endl;

  // for (auto item : visits) {
  //   cout << item << " "; 
  // }
  // cout << endl;

  // for (auto item : befores) {
  //   cout << item << " ";
  // }
  // cout << endl;

  // for (auto item : distances) {
  //   cout << item << " ";
  // }

}