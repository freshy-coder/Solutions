#include<bits/stdc++.h>
#define MAXN 5005
#define MAXM 5005
#define MOD 1000000007
using namespace std;
typedef pair<long long, long long> pi;
typedef long long ll;
typedef long double ld;
ll N, M, K;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

// map<ll,vector<ll>> words;
vector<pi> words;



int main() { 
  FIO;
  freopen("poetry.in", "r", stdin);
  ofstream fout("poetry.out");
  cin >> N >> M >> K;
  for (ll i = 0; i < M; i++) {
    ll a,b;
    cin >> a >> b;
    words.push_back({a,b});
  }


  // sort(words.begin(), words.end());
  ll num_lines[11];
  ll byClass[MAXN];
  
  fill(byClass, byClass+MAXN, 0);
  // for (ll i = 0; i < words.size(); i++) {
    for (ll j = 0; j <= K; j++) {
      num_lines[j] = 0;
      num_lines[0] = 0; // set first as zero; base case
      for(auto word : words) { 
        if (j-word.first >= 0 && num_lines[j-word.first] != -1) { // careful don't select min if you don't have to  
          num_lines[j] += num_lines[j-word.first]; // addidive or replacement?
          if (j-word.first == 0) num_lines[j] += 1;

          if (j == K) { 
            byClass[word.second]+=num_lines[j-word.first];
          }   
        }
        
        
      } 
      if (num_lines[j] == 0) num_lines[j] = -1;
    }
  // }
  // for (auto item : num_lines) {
  //   cout <<  item << " ";
  // }
  // for (ll i = 0; i <= K; i++) {
  //   cout << i << ": " << byClass[i] << endl;
  // } 
  map<char, ll> lines;
  for (ll i = 0; i < M; i++) {
    char a; cin >> a;
    lines[a]++;
  }
  ll ans = 0;
  for (auto item : lines) {
    ll power = item.second;
    ll total = 0;
    for (ll i = 0; i < MAXN; i++) {
      total += pow(byClass[i], power) ;
      total %= MOD;
    }
    if (total > 0 && ans == 0) ans = 1;
    ans *= total;
    
  }
  fout << ans;
  // for (ll r = 0; r < N; r ++) {
  //   for (ll c = 0; c < M; c ++) {
  //     all[r][c] = -1;
  //     ll cur = words[r].first;
  //     if (all[r-1][c-cur] != -1) {

  //     }
  //   }
  // }

}