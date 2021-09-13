#include<bits/stdc++.h>
#define MAXN 10005
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll N, M;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

vector<ll> adj[MAXN];
vector<pi> adjgpsP[MAXN];
vector<pi> adjgpsQ[MAXN];
ll nexts[MAXN];
bool visited[MAXN];
ll distances[MAXN];
priority_queue<pi> pq;

// how to pass by address?
// verify themes: track one variable max/min, flipping edges
// strat: flip dijk, use befores
// befores algorithm doesn't work on directed, i made it work
// check dijk starting

// keep track of node properties separately
// path changes -> in that one small part of dijk

void dijkstra(string gps) {
  memset(visited, false, sizeof(visited) ); // reset visited array
  pq.push(make_pair(0, N)); // add start state (-moves, (x, y) ) 
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
      if (gps == "P") {
        for (auto nbr : adjgpsP[x]) {
          pq.push({moves-nbr.second, nbr.first});
        }
      }
      else {
        for (auto nbr : adjgpsQ[x]) {
          pq.push({moves-nbr.second, nbr.first});
        }
      }
  }

  
  memset(nexts, -1, sizeof(nexts));
  for (int i = 1; i <= N; i++) {
    if (gps == "P") {
      for (auto nbr : adjgpsP[i]) {
        if (distances[i]+nbr.second == distances[nbr.first]) {
          nexts[nbr.first] = i;
        }
      }
    }
    else {
      for (auto nbr : adjgpsQ[i]) {
        if (distances[i]+nbr.second == distances[nbr.first]) {
          nexts[nbr.first] = i;
        }
      }
    }
  }

}


main() { 
  FIO;
  freopen("gpsduel.in", "r", stdin);
  ofstream fout("gpsduel.out");
  
  cin >> N >> M;
  for (ll i = 0; i < M; i++) {
    ll a, b, p, q; cin >> a >> b >> p >> q;
    adjgpsP[b].push_back({a, p});
    adjgpsQ[b].push_back({a, q});
    adj[a].push_back(b);
  }

  dijkstra("P");
  vector<ll> nextsP;
  for (auto item : nexts) nextsP.push_back(item);

  dijkstra("Q");
  vector<ll> nextsQ;
  for (auto item : nexts) nextsQ.push_back(item);

  // for (auto item : nextsP) {
  //   cout << item << " ";
  // }
  // cout << endl;
  // for (auto item : nextsQ) {
  //   cout << item << " ";
  // }

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
        ll cry = 0;
        if (nextsP[x] != nbr) cry++;
        if (nextsQ[x] != nbr) cry++;
        pq.push({moves-cry, nbr});
      }
  }
  fout << distances[N];

}