// be extra conservative setting up variables or clearing arrays - just clear/reset at every step if necessary
// this one had a different algorithm from what i had originally, scanned more! flesh it out.

#include<bits/stdc++.h>
#define MAXN 1005 //change
#define FIO ios::sync_with_stdio(0); cin.tie(0); 

using namespace std;
typedef pair<long long,long long> pi;
typedef long long ll;
typedef long double ld;
ll N;



int main() { 
  FIO; 
  ofstream fout("art2.out");
  freopen("art2.in", "r", stdin);
  
  cin >> N;

  ll art[MAXN];
  bool on[MAXN+1];

  // read in data to art[]
  for (int i = 0; i < N; i++) {
    cin >> art[i];
  }

  fill(on, on+N+1, false);

  ll xmin[MAXN+1];
  ll xmax[MAXN+1];

  
  // getting start of intervals and storing it to trav
  for (ll i = 0; i < N; i++) {
    ll val = art[i];
    if(val != 0 && !on[val]){
      // if (val == 12) cout << "gotchu" << endl;
      xmin[val] = i;
      on[val] = true;
    }
  }

  fill(on, on+N+1, false);

  // for (auto item : trav) {
  //   cout << item.first << ", "<<item.second << endl;
  // }


// getting end of intervals and storing it to trav
ll count = 0;
  for (ll i = N-1; i >=0; i--) {
    ll val = art[i];
    if(val != 0 && !on[val]){
      xmax[val] = i;
      on[val] = true;
      count++;
    }
  }
  // cout << count;

  ll ans = 0;


  vector<ll> go;
  for (int i = 0; i < N; i ++) {
    ll c = art[i];
    
    if (i == xmin[c]) {
      go.push_back(c);
      ans = max((int) ans, (int) go.size()); // must cast
    }

    if (go.size() > 0 && go[go.size()-1] != c)  {
      fout << "-1" << endl; return 0;
    }

    
    if (i == xmax[c]) go.pop_back();

  }

  fout << ans;


}