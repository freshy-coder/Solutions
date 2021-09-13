#include<bits/stdc++.h>
#define MAXN 12 //change. SET A SPACIOUS MAXN WHEN TESTING SO YOU DONT MESS UP WITH GARBAGE VALS OR SHIT
using namespace std;
typedef pair<int, int> pi;
typedef long long ll;
ll T, N, a, b;
string s;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

// don't forget <= when doing 1-based
// don't forget to update both action array and dp (common theme)

ll dp[MAXN];
ll pill[MAXN];

int main() { 
  FIO;
  freopen("in", "r", stdin);
  cin >> T;

  for (ll t = 0; t < T; t++) {// ONLY DOING 1 T FOR NOW
    cin >> N >> a >> b >> s;

    fill(dp, dp+MAXN, 0);
    fill(pill, pill+MAXN, 0);

    dp[0] = b;
    pill[0] = 1;
/*  
Each unit of gas pipeline costs us a bourles, and each unit of pillar — b bourles. So, it's not always optimal to make the whole pipeline on the height 2. Find the shape of the pipeline with minimum possible cost and calculate that cost. 
*/  
cout << N << " " <<  a << " " << b << endl << s << endl;
    for (ll i = 1; i <= N; i++) {
      cout <<i << " : " << s.substr(i, 1) << endl;
      if (pill[i-1] == 2 && s.substr(i,1) == "1") { // currently at 2 and must stay at 2
        cout << "at 2, must stay 2" << endl;
        dp[i] = dp[i-1] + a + 2*b;
        pill[i] = 2;
      }
      else if (pill[i-1] == 1 && s.substr(i,1) == "1") { // currently at 1 and must move to 2
        cout << "at 1, must move 2" << endl;
        dp[i] = dp[i-1] + 2*a + 2*b;
        pill[i] = 2;
      }
      else if (pill[i-1] == 1 && (s.substr(i,1) == "0" || i == N)) { // currently at 1 and don't have to go to 2
        // greedily stay there
        cout << "at 1, staying at 1" << endl;
        dp[i] = dp[i-1] + a + b;
        pill[i] = 1;
        
      }
      else { // actual dp - if at 2 and can go to 1 or 2
        // case: end of the line go down OR
        cout << "choosing between staying up: " << a + 2*b << ", and going down: " << 2*a + b << " down >= up: " << (2*a + b >= a + 2*b) << endl;
        if (s.substr(i-1,1) == "1" || (i != N && 2*a + b >= a + 2*b)) { // if (we have to stay up || (or its not the end and staying up is cheap))
          cout << "at 2, volunt. staying at 2" << endl;
          dp[i] = dp[i-1] + a + 2*b;
          pill[i] = 2;
        }
        else if (s.substr(i-1,1) == "0" && (i == N || 2*a + b < a + 2*b)) { // if (we can go down and (we have to EOL or its cheaper))
          cout << "at 2, volunt. moving to 1" << endl;
          dp[i] = dp[i-1] + 2*a +b;
          pill[i] = 1;
        }
      }
      cout << "so: " << dp[i] << endl;
    }

    cout << dp[N] << endl;
    for (auto item : pill) cout << item << " ";
  }


}   