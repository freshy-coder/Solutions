#include<bits/stdc++.h>
#define MAXN 255
#define MAXM 25005
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll N, M;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

vector<vector<ll>> adj[MAXN];
pi edges[MAXM];
bool visited[MAXM];
priority_queue<pi> pq;
ll distances[MAXN];
bool importantEdges[MAXM];

// at first glance, seemed like a brute force dijkstra test-all might have worked
// something like that still worked. Payed attention to what were the POINTS OF INTEREST. We only care about the path that FJ takes originally to put a new roadblock down somewhere and do dijkstra. And there are 25K paths, but only 250 nodes max, so Dijkstra 250 times max would work fine. Don't be deceived by high numbers that a seemingly slow solution might work!

ll dijkstra(ll i) {
  memset(visited, false, sizeof(visited) ); // reset visited array
    memset(distances, false, sizeof(distances) );
    pq.push({0,1}); // add start state (-moves, (x, y) ) 
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
        // cout << "process - " << " for node: " << x << " : " << distances[x] << endl;
        
        // transitions
        for (auto nbr : adj[x]) {
          // cout << "from " << x << " to " << nbr[0] << endl;
          if (nbr[2] == i) {
            
            pq.push({moves-(nbr[1]*2), nbr[0]});
            // cout << "M--ADD: " << moves-(nbr[1]*2) << "," << nbr[0]<< endl;
          }
          else {
            // cout << "ADD: " << moves-(nbr[1]) << "," << nbr[0] << endl;
            pq.push({moves-nbr[1], nbr[0]});
          }
          
        }
    }
    return distances[N];
}

main() { 
  FIO;
  freopen("rblock.in", "r", stdin);
  ofstream fout("rblock.out");

  cin >> N >> M;

  for (int i = 0; i < M; i++) {
    ll a, b, l; cin >> a >> b >> l;
    edges[i] = {a,b};
    adj[a].push_back({b,l,i});
    adj[b].push_back({a,l,i});
  }
  ll og = dijkstra(-1);
  ll ans = 0;
  
  for (ll i = 1; i <= N; i++) {
    for (auto nbr : adj[i]) {
      if (distances[nbr[0]] + nbr[1] == distances[i])
      importantEdges[nbr[2]] = true;
    }
  }

  for (int i = -1; i <= M; i++) {
      if (importantEdges[i]) {
        ans = max(ans, dijkstra(i)-og);
      }
  }
  fout << ans << endl;

  

}