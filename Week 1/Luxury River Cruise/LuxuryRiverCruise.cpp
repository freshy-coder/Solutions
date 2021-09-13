#include<bits/stdc++.h>
#define MAXN 1005 //change
#define FIO ios::sync_with_stdio(0); cin.tie(0); 

using namespace std;
typedef pair<long long,long long> pi;
typedef long long ll;
typedef long double ld;
ll n, m, k;

pi adj[MAXN];


int main() { 
  FIO; 
  ofstream fout("cruise.out");
  freopen("cruise.in", "r", stdin);
  
  cin >> n >> m >> k; 


  // SAVING INPUT TO ADJACENCY LIST (consists of pairs that have nodes {left, right})
  for (int i = 0; i < n; i++) {
    ll a,b; cin >> a >> b;
    adj[i] = make_pair(--a, --b);
  }

    vector<char> dir;
  for (int i = 0; i < m; i ++) {char x; cin >> x; dir.push_back(x);}
     // incrorect reading resulted in the loop not running properly. print it out!

  ll dest[MAXN]; // stores where each node will be after M steps

  // For each node, goes through the M instructions and finds where it will end up. Saves to dest.
  for (int i = 0; i < n; i++) {
    ll node = i;
    for (char x : dir) {
    //   cout << node+1 << " ";
      if (x == 'L')
        node = adj[node].first;
      else
        node = adj[node].second;
    }
    dest[i] = node;
  }


  ll offset = 0, cycle_len = 0;
  bool visited[MAXN]; fill(visited, visited+n, false);
  vector<ll> past;

  ll step = 0; 
  ll node = 0; ll prev = 0;

  // CYCLE-FINDER - Traverses graph using dest array, taking M steps every iteration, stops when a cycle is found or K steps have been taken.
  while (step < k) {
    // cout << "visiting: " << node << endl;

    // IF CYCLE IS FOUND, node will already be visited
    if (visited[node]) {

      // Find length of the cycle and # of nodes in path before cycle actually starts
      prev = find(past.begin(), past.end(), node) - past.begin();
      cycle_len = step-prev;
      offset = prev; // # of nodes in path before cycle starts
      // cout <<"cycle ends on: " << node <<", cycle length: " << cycle_len << ", offset: " << prev << endl;
      

      // Find how many extra steps are LEFT to take
      float left = (k - offset) % cycle_len;
      // cout << "left: " << left << endl;

      // take those extra steps and get the answer
      for (int i = 0; i < left; i++) {
        node = dest[node];        
      }

      fout << node+1; // ANSWER OUTPUT
      return 0;
      
    }

    // IF NO CYCLE IS FOUND, keep traversing
    visited[node] = true;
    past.push_back(node);
    step++;
    node = dest[node];
  }

  fout << node+1; // This will be reached if no cycle is found and the while loop reaches K executions.  

}

