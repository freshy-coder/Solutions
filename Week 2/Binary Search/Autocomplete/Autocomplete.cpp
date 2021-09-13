#include<bits/stdc++.h>
#define MAXN 100005 //change
#define FIO ios::sync_with_stdio(0); cin.tie(0); 

using namespace std;
typedef pair<long long,long long> pi;
typedef long long ll;
typedef long double ld;
ll W, N;

vector<pair<string, ll>> dict;



int main() { 
  FIO; 
  ofstream fout("auto.out");
  freopen("auto.in", "r", stdin);
  
  cin >> W >> N;
  for (ll i = 0; i < W; i++) {
    string s; cin >> s; dict.push_back(make_pair(s,i+1));
  }

  sort(dict.begin(), dict.end()); // using a data structure for dict to store the previous indexes before sort, that's what the problem wants.
  
  // for (auto item : dict) cout << item << endl;

  vector<pair<ll, string>> find;

  for (ll i = 0; i < N; i ++) {
    ll a; string s; cin >> a >> s;
    // cout << "read: " << a << " with " << s;
    find.push_back(make_pair(a,s));
  }

  for (int i = 0; i < N; i ++) {
  int a = 0; int b = W; ll mid = 0;

  string toFind = find[i].second;

  // cout << "toFind: " << toFind << endl;
  // had a lot of trouble knackering out this binary search
  int count = 0;
  while (a != b) {
    count++; if (count == 100) break;
    mid = (a+b)/2;
    // cout << a <<" mid: " << mid << ", b: " << b << endl;

    // if (dict[mid].size() >= toFind.size() && dict[mid].substr(0, toFind.size()).compare(toFind) != 0) {

      // just trust lexographic comparison no need to do length check
      if (dict[mid].first.substr(0, toFind.size()).compare(toFind) >= 0) {
        b = mid;
        // cout << "dict too big or just right." << endl;
      }
      else { // if not works and is too small
        // cout << "dict too small." << endl;
        a = mid+1;
      }
    // }
  }

  // cout << a << endl;
  ll idx = a+find[i].first-1;
  // cout << "so will plus: " << find[i].first << " => " idx;
  if(idx <= dict.size() && dict[idx].first.size() >= toFind.size() && dict[idx].first.substr(0, toFind.size()).compare(toFind)== 0) {
    fout << dict[idx].second << endl;
  }
  else {
    // cout << "from a: " << a <<", idx: " << idx << endl;
    // cout << "spot #: " <<idx << ", has: " << dict[idx].first << endl; 
    fout << -1 << endl;
  }
  }
  


}

