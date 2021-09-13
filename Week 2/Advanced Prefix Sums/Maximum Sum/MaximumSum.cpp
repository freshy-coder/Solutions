#include<bits/stdc++.h>
#define MAXN 105 //change
#define FIO ios::sync_with_stdio(0); cin.tie(0); 

using namespace std;
typedef pair<long long,long long> pi;
typedef long long ll;
typedef long double ld;
ll N;

ll arr[MAXN][MAXN];
ll pre[MAXN][MAXN];

// you can see how for these you should look for some sort of linear/sweep solution

int main() { 
  FIO; 
  // freopen("in", "r", stdin);
  
  cin >> N;

  // reading input
  for (ll r = 1; r <= N; r++) {
    for (ll c = 1; c <= N; c++) cin >> arr[r][c];
  }

  for (ll r = 0; r < N; r++) { // reset entire grid, especially if you're doing 1-index. you dont want garbage vals?
  // don't switch r & c!
    for (ll c = 0; c < N; c++) pre[r][c] = 0;
  }


  // CALCULATING PREFIX SUMS
  for (ll r = 1; r <= N; r++) {
    for (ll c = 1; c <= N; c++) {
      pre[r][c] = arr[r][c] + pre[r-1][c] + pre[r][c-1] - pre[r-1][c-1];
      // cout << pre[r][c] << " ";
    }
    // cout << endl;
    
  }
  // cout << endl;
   
  ll ans = 0;

  for (ll a = 1; a <= N; a ++) {
    for (ll b = 1; b <= N; b++) {
    // ll a = 2; ll b = 4;
      if (a >= b) continue;
      // height end points established
      
      vector<ll> sums;
      for (ll c = 1; c <= N; c++) {
        sums.push_back(pre[b][c] - pre[b][c-1] - pre[a-1][c] + pre[a-1][c-1]);
        // cout << "c: " << c <<" -> "<< pre[b][c] <<" " << pre[b][c-1] <<" " << pre[a-1][c] <<" " << pre[a-1][c-1] << endl;
      }


      ll best = 0; ll curr = 0;
      for (auto item : sums) {
        // cout << item << " ";
        curr = max((ll) 0, curr + item);
        best = max(best, curr);
      }
      
      // if (best > ans) cout << endl << a << "," << b << endl;

      ans = max(best, ans);

    }
  }


  cout << ans;
  


}

