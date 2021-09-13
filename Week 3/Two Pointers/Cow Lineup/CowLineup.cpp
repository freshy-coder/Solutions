#include<bits/stdc++.h>
#define MAXN 100005 //change. SET A SPACIOUS MAXN WHEN TESTING SO YOU DONT MESS UP WITH GARBAGE VALS OR SHIT
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pi;
ll N,K;

#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

ll inp[MAXN];
map<ll, ll> cnt;
ll on = 0;

void add(int rp) {
  cnt[inp[rp]]++;
  if(cnt[inp[rp]] == 1) { // if it is only 1, it was 0 and nonexistent before.
    on++;
  }
}

void remove(int lp) {
  cnt[inp[lp]]--;
  if (cnt[inp[lp]] == 0) {
    on--;
  }
}

int main() { 
  FIO;
  freopen("lineup.in", "r", stdin);
  ofstream fout("lineup.out");

  cin >> N >> K;

  for (ll i = 0; i < N; i++) {
    cin >> inp[i];
  }

  ll lp = 0;
  ll ans = 0;
  for (int rp = 0; rp < N; rp++) {
    add(rp);
    while (on > K+1) {
      remove(lp);
      lp++;
    }
    ans = max(ans, cnt[inp[rp]]); // This part is interesting. Two pointers is very low runtime, and at this point we only care about the cnt[] of the value at the right pointer. That's because any other larger range would have already been traversed by rp.
  }
  fout << ans;


}   