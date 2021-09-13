#include<bits/stdc++.h>
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll N;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
// Algorithm: Count the mods for each variable, easily multiply and count up all
// Thinking strat: simplification - just look at b+e+s+s+i+e - how can we quickly tell if given variable values can make this divisible by 7? How can we quickly tell how many variable combos are possible? Expand to entire expression.
// when dealing with divisibility/multiplicity/parity, it helps to look at mods and parity

// Note: f-ed up on math/counting part. Just be careful and reason your way though it, AMC logic.


int main() { 
  FIO;
  freopen("bgm.in", "r", stdin);
  ofstream fout("bgm.out");
  cin >> N;
  char a; ll b;

  map<char, map<ll, ll>> choices;

  for (ll i = 0; i < N; i++) {
    cin >> a >> b;
    choices[a][b % 7]++;
  }

  // (B,E,S,I,G,O,M)
  // You will never see the following ever again.
  ll ans = 0;
  ll mult = 1;

  for (auto x : choices['B']) { ll b = x.first; ll mult1 = x.second;
    for (auto y : choices['E']) { ll e = y.first; ll mult2 = mult1 * y.second;
      for (auto z : choices['S']) { ll s = z.first; ll mult3 = mult2 * z.second;
        for (auto w : choices['I']) { ll i = w.first; ll mult4 = mult3 * w.second;
          for (auto t : choices['G']) { ll g = t.first; ll mult5 = mult4 * t.second;
            for (auto u : choices['O']) { ll o = u.first; ll mult6 = mult5 * u.second;
              for (auto v : choices['M']) { ll m = v.first; ll mult7 = mult6 * v.second;
                // cout << "a test:" << mult << endl;
                if ((b+e+s+s+i+e)*(g+o+e+s)*(m+o+o) % 7 == 0) {
                  ans+=mult7;
                }
              }
            }
          }
        }
      }
    }
  }
  fout << ans;

}