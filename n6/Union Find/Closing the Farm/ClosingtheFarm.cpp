#include<bits/stdc++.h>
#define MAXN 200005
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

// You should immediately get the notion of processing backwards and seeing if the farm's open at each point
// to confirm that, you know that the end result will be all farms are closed. That is, when going backwards, outside of the barn that's being opened in reverse at that moment and barns you already opened, there are no other open barns. So you can go backwards.
// then its simple U-F:
// to reopen a barn, union all of its nodes (store neighbors DFS) 
// you shouldn't have rushed into solving before working out all the kinks/testing on input
// for reversal problems it helps to map out orignial flow with reversed flow to test if each step matches, and you're doing them in the right order
// your problem: you shouldn't be reopening edges to barns not reopened yet. Those aren't relevant; THINGS WE CARE ABOUT are ALREADY OPENED NODES!

ll N, M;

vector<ll>adj[MAXN];
priority_queue<vector<ll>> pq;
map<ll, ll> opened;

int parent[MAXN];
int siz[MAXN];

int findRoot(int a) {
	if (parent[a] == a) {
		return a;
	}
	return parent[a] = findRoot(parent[a]);
	// or return findRoot(parent[a])
}

bool isConnected(int a, int b) {
	return parent[a] = findRoot(b);
}

void join(int a, int b) {
  a = findRoot(a);
  b = findRoot(b);
	
  // cout << "joining: " << a << " and " << b << endl;
  // parent[findRoot(a)] = findRoot(b); // makes a's parent point to b's. b's parent is all's parent.
  // cout << "new size: " << 
  
  

  if (a != b) {
    // cout << "adding sizes:" << endl;
    // siz[findRoot(b)] += siz[findRoot(a)];
    parent[b] = a;
    // cout << siz[a] << " for : " << a << endl;

    siz[a] += siz[b];
  }
    
}



main() { 
  FIO;
  freopen("closing.in", "r", stdin);
  ofstream fout("closing.out");
  cin >> N >> M;


  for (ll i =0; i < M; i++) {
    ll a, b; cin >> a >> b; a--; b--;
    adj[b].push_back(a);
    adj[a].push_back(b);
  }

  ll order[MAXN];
  fill(siz, siz+MAXN+1, 1);
  for (ll i = 0; i < N; i++) {
    parent[i] = i;
    cin >> order[i]; order[i]--;
  }

  vector<string> res;

  for (ll i = N-1; i >= 0; i--) {
    

    
    ll open = order[i];
    opened[open] = 1;
    // cout << "opening: " << open << endl;
    for (auto node : adj[open]) {
      if (opened[node] == 1) {
        join(open, node);
      }
      
    }
    // cout << siz[findRoot(open)] << endl;

    if (siz[findRoot(open)] >= N-i) {
      res.push_back("YES");
    }
    else {
      res.push_back("NO");

    }
  }

  for (ll i = N-1; i>=0; i-- ) {
    fout << res[i] << endl;
  }




  // fout << "";
}