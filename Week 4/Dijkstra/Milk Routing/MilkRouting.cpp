#include<bits/stdc++.h>
#define MAXN 505
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll N, M, X;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

vector<vector<ll>> adj[MAXN]; // {dest, l, c}
ll visited[MAXN];
vector<ll> distances[MAXN]; // {time, l, c}
priority_queue<vector<ll>> pq; // {time, l, c, dest}

// sometimse code just doesn't do anything, might be div by zero error or incorrect memory access
// Dijkstra on multiple computed variables

main() { 
  FIO;
  freopen("mroute.in", "r", stdin);
  ofstream fout("mroute.out"); 
  cin >> N >> M >> X;
  for (ll i = 0; i < M; i++) {
    ll a, b, l, c; cin >> a >> b >> l >> c;
    adj[a].push_back({b, l, c});
    adj[b].push_back({a, l, c});
  }

  

  memset(visited, false, sizeof(visited) ); // reset visited array
  pq.push({0,0,0,1}); // add start state (-moves, (x, y) ) 
  distances[1]= {0,0,0};

  while (!pq.empty()) {
    
    
    int x = pq.top()[3];
    // cout << "scanning: " << x << endl;
    
    if (visited[x]) { // don't visit if already done so (equivalent of checking before visit if the new dstance is better)
        pq.pop();
        continue;
    }

    visited[x] = true; // current spot is visited
    distances[x] = {pq.top()[0], pq.top()[1], pq.top()[2]};
    pq.pop();
    // transitions

    for (auto nbr : adj[x]) {
      ll c;
      if (distances[x][2] != 0) c = min(nbr[2], distances[x][2]);
      else c = nbr[2];
      // cout << -(distances[x][1]+nbr[1])- X / c;
      pq.push({-(distances[x][1]+nbr[1])- X / c, distances[x][1]+nbr[1], c, nbr[0]});
      // cout << "pushed: {" << -(distances[x][1]+nbr[1])- X / c << ", " << distances[x][1]+nbr[1] << ", " << c << ", " << nbr[0] << "}" << endl;
    }
  }
  fout << -distances[N][0];
}