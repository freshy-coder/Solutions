#include<bits/stdc++.h>
#define MAXN 100005
using namespace std;
typedef pair<long long, long long> pi;
typedef int ll;
typedef long double ld;
ll N, K;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll Ldistances[MAXN];
ll distances[MAXN];
bool visited[MAXN];
bool leaves[MAXN];
queue<pi> q;
vector<ll> adj[MAXN];

void bfs(ll c) {
  
  // dist[N-1][0][N-1][0][0] = 0;
  // q.push({N-1, 0, N-1, 0, 0, 0}); // same as dp. i, j, x, y, rotation, length
  while (!q.empty()) {

    ll dist = q.front().first;
    ll node = q.front().second;
    // cout << "read in node: " << node;
    q.pop();

    if (visited[node]) {
      // cout << "quitting: " << node << endl;
      continue;
    }
    // cout << count << endl;
    if (c == 1) {
      Ldistances[node] = dist;
    }
    else {
      distances[node] = dist;
    }
    
    visited[node] = true;
    // cout << "setting dist: " << dist << " for node: " << node << endl;

    // cout << "for node: " << node << endl;
    for (auto nbr : adj[node]) {
      q.push({dist+1, nbr});
      // cout << dist+1 << " for " << nbr << endl;
    }

  }
} 

ll parents[MAXN];

void dfs (ll s, ll e) {
  for (auto u : adj[s]) {
    if(u != e) {
      // e is the parent of s
      parents[s] = e;
      dfs(u,s);
    }
  }
}


int main() { 
  FIO;
  freopen("atlarge.in", "r", stdin);
  ofstream fout("atlarge.out");
  memset(parents, -1, sizeof(parents));
  memset(distances, -1, sizeof(distances));
  memset(Ldistances, -1, sizeof(Ldistances));
  cin >> N >> K;
  for (ll i = 0; i < N-1; i++) {
    ll a, b;cin >> a >> b;
    adj[a].push_back(b); adj[b].push_back(a);
  }

  dfs(K, -1);

  for (ll i = 1; i <= N; i++) {
    if (adj[i].size() == 1) {
      leaves[i] = true;
      q.push({0, i});
    }
  }
  

  bfs(1);
  // for (auto item : Ldistances) {
  //   cout << item << " ";
  // }

  // cout << endl;
  q.push({0, K});
  memset(visited, false, sizeof(visited));
  bfs(0);

  // for (auto item : distances) {
  //   cout << item << " ";
  // }

  ll farmers = 0;
  for (ll i = 1; i <= N; i++) {
    if (i != K && Ldistances[parents[i]] > distances[parents[i]] && Ldistances[i] <= distances[i]
        || (leaves[i] && distances[i] == 1)) {
      // cout << i << endl;
      farmers ++;
    }
  }
    
  fout << farmers;
}