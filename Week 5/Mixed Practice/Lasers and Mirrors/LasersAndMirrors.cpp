#include<bits/stdc++.h>
#define MAXN 100000
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;

// ALGORITHM/THINKING PROCESS
// Originally thought it was some sort of DP, like DP[ind] = least # of mirrors needed to get to mirror[ind]. Struggling to find an order to go through these states, thought it had to be dependent on original laser location
// => all hint to using DIJKSTRA! Dijkstra is basically DP, right? and it depended on original starting point. If you're on a graph and considering DP on path traversals just try dijkstra first. 

// Many things arose during implementation

// 1) as long as you mark things as visited in dijkstra and don't come back to them later on, it should take the expected runtime
// 2) Problem needed a way to store all X's and Y's along the same axis  => GRAPH COMPRESSION (see below). Can store these all in an array of vectors for each x value, then another array for y value. Can include special points in this mix too to compress them, but give them a special ID (0 & 1 in this case)
// 3) structs!! below is implementation example, with both normal constructor and a default no-argument one (must include if you're going to be putting them in lists). included an "i" value as an ID for another list
// 3.1) you can (and should) make defined comparators for the structs. it's simple.
// 4) be careful in output conditions - if there's multiple cases, make sure you choose between if or if/ifelse/else
// 5) it's much easier to do sizeof in memset than putting actual #
// 6) Again, if you're changing anything in dijkstra, it's mostly in 1) where setup/array rest is done 2) changing the pq & updates 3) unpacking pq

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll N, K;

struct pt {
  ll x, y, i;
  pt(ll xst, ll yst, ll ist):
  x(xst), y(yst), i(ist)
  {
  }

  pt():
  x(-1), y(-1), i(-1)
  {}
  
};

bool cmpy(pt a, pt b) { return a.y < b.y; } 
bool cmpx(pt a, pt b) { return a.x < b.x; } 

vector<pt> x[MAXN];
vector<pt> y[MAXN];
bool visited[MAXN];
ll distances[MAXN];
pt pts[MAXN];

priority_queue<vector<ll>> pq; 

void dijkstra() {
  // add start state (-moves, (x, y) ) 
  
  while (!pq.empty()) {
      // extract item from pq
      int moves = pq.top()[0];
      int dir = pq.top()[1];
      int i = pq.top()[2];
      // if (i == 1) moves = min(0,moves+1);
      pq.pop();

      // cout << "now testing: " << i  << ", with distance: " << -moves << endl;
      
      if (visited[i]) { // don't visit if already done so (equivalent of checking before visit if the new dstance is better)
          continue;
      }
      visited[i] = true; // current spot is visited
      distances[i] = -moves;
      
      // transitions
      // dir = 0 means arrived from below or up => assign 1 (Right or left) to neighbors
      if (dir == 0) {
        for (auto item : y[pts[i].y]) {
          if (!visited[item.i]) {
            pq.push({moves-1, 1, item.i});
            // cout << "adding to pq: dir=" << 1 <<  ", idx: " << item.i << endl;
          }
        }
      }
      // dir = 1 means arrived from right to left => assign 0 (up or down) to neighbors
      if (dir == 1) {
        for (auto item : x[pts[i].x]) {
          if (!visited[item.i]) {
            pq.push({moves-1, 0, item.i});
            // cout << "adding to pq: dir=" << 0 <<  ", idx: " << item.i << endl;
          }
        }
      }
  }
}

main() { 
  FIO;
  freopen("lasers.in", "r", stdin);
  ofstream fout("lasers.out");
  cin >> N;
  vector<pt> all;
  

  ll a, b; cin >> a >> b; all.push_back(pt(a,b,0));
  // pt lasPos = pt(a,b,0);
  pts[0] = pt(a,b,0);
  cin >> a >> b; all.push_back(pt(a,b,1));
  pts[1] = pt(a,b,1);

  
  for (ll i = 0; i < N; i++) {
    ll a, b; cin >> a >> b; all.push_back(pt(a,b,i+2));
  }

  sort(all.begin(), all.end(), cmpx);
  ll ct = 0; 
  ll prev = all[0].x;
  for (ll i = 0; i < N+2; i++) {
    if (all[i].x == prev) { 
      all[i].x = ct;
    }
    else {
      prev = all[i].x;
      ct++;
      all[i].x = ct;
    }
  }
  sort(all.begin(), all.end(), cmpy);
  ct = 0; 
  prev = all[0].y;
  
  for (ll i = 0; i < N+2; i++) {
    if (all[i].y == prev) {
      all[i].y = ct;
    }
    else {
      prev = all[i].y;
      ct++;
      all[i].y = ct;
    }
    pts[all[i].i] = all[i]; // saving all points
  }

  for (ll i = 0; i < N+2; i++) {
    x[all[i].x].push_back({all[i].x,all[i].y,all[i].i});
    y[all[i].y].push_back({all[i].x,all[i].y,all[i].i});
  }

  for (ll i = 0; i < MAXN; i++) {
    sort(x[i].begin(), x[i].end(), cmpx); // MUST WRITE SORTER
    sort(y[i].begin(), y[i].end(), cmpy);
  }

  // TESTING RIGHT FIRST
  ll pre= 1E9;
  
  pq.push({1,0,0});
  memset(distances, (ll) -1, sizeof(distances)); // easier just to do sizeof
  memset(visited, false, sizeof(visited));
  distances[0]=0;
  dijkstra();
 
  pre= distances[1];

  pq.push({1,1,0});
  memset(distances, (ll) -1, sizeof(distances)); // easier just to do sizeof
  memset(visited, false, sizeof(visited));
  distances[0]=0;
  dijkstra();

  // careful in output conditions
  if (distances[1] != -1 && pre== -1) fout  << distances[1];
  else if (distances[1] == -1 && pre== -1) fout  << -1;
  else if (distances[1] == -1 && pre!= -1) fout  << pre;
  else fout << min(distances[1], pre);

  // for (auto item : distances) {
  //   cout << item << " ";
  // }

}
