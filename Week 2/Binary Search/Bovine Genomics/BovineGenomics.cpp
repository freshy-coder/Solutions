#include<bits/stdc++.h>
#define MAXN 10 //change
#define FIO ios::sync_with_stdio(0); cin.tie(0); 

using namespace std;
typedef pair<long long,long long> pi;
typedef long long ll;
typedef long double ld;
ll M,N;

vector<string> spotCows;
vector<string> unSpotCows;

bool subsect(ll s, ll len) {
  // cout << "from: " << s << " to " << e << endl;
  unordered_map<string, ll> stores;
  for (auto item : unSpotCows) {
    // cout << "storing: " << item.substr(s,len) << endl;
    stores[item.substr(s, len)] = 1;
  }

  for (auto item : spotCows) {
    if (stores.find(item.substr(s,len)) != stores.end()){
      return false;
    }
  }
  return true;
}

bool works(ll len) {
  for (int i = 0; i < M-len; i++) {
    if (subsect(i, len)) 
    {
      // cout << i << " to " <<  i+len << endl;
      return true;
    }
  }
  return false;
}

int main() { 
  FIO; 
  ofstream fout("cownomics.out");
  freopen("cownomics.in", "r", stdin);

  cin >> N >> M;

  for (int i = 0; i < N; i++){
    string a; cin >> a; spotCows.push_back(a);
  }

  for (int i = 0; i < N; i++){
    string a; cin >> a; unSpotCows.push_back(a);
  }

  ll a = 0; ll b = M+1; ll mid;
  while (a != b) {
    
    mid = (a+b) / 2;
    
    if (works(mid)) {
      b = mid;
    }
    else {
      a = mid+1;
    }  

  }
  fout << a;






}

