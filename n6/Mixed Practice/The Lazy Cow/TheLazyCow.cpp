#include<bits/stdc++.h>
#define MAXN 401
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll N, K;


#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll field[MAXN][MAXN];
ll pre[MAXN][MAXN];

int main() { 
  FIO;
  freopen("lazy.in", "r", stdin);
  ofstream fout("lazy.out");

  cin >> N >>K;

  for (ll i = 0; i < N; i++) {
    for (ll j = 0; j < N; j++) {
      cin >> field[i][j];
      if (j>0) pre[i][j] = pre[i][j-1]+field[i][j];
      else pre[i][j] = field[i][j];
      // cout << pre[i][j] << " ";
    }
    // cout << endl;
  }
  ll ans = 0;
  for (ll i = 0; i < N; i++) {
    for (ll j = 0; j < N; j++) {
      // rows above starting pt to starting pt's row
      ll side = 0;
      // cout << "fu" << endl; 
      ll sum = 0; ll f, b;
      for (ll r = i-K; r <= i; r++) {
        if (r < 0 ) { side++; continue; }
        if (j-side-1 < 0) b = 0;
        else b = pre[r][j-side-1];
        f = pre[r][min(j+side, N-1)];
        sum += f-b;
        side++;
        // cout << f << " and " << b << endl;
      }
      side--;
      for (ll r = i+1; r <= i+K; r++) {
        side--;
        if (r >= N) { continue;}
        if (j-side-1 < 0) b = 0;
        else b = pre[r][j-side-1];
        f = pre[r][min(j+side, N-1)];
        sum += f-b;
        // cout << f << " and " << b << endl;
        // side--;
      }
      // if(sum == 119) cout << i << ", " << j << " on " << sum << endl;
      ans = max(sum, ans);
    }
  }

  fout << ans;

}