#include<bits/stdc++.h>
#define MAXN 100005 //change
#define FIO ios::sync_with_stdio(0); cin.tie(0); 

using namespace std;
typedef pair<long long,long long> pi;
typedef long long ll;
typedef long double ld;
ll N;

// timeQueue stores the times where the cow must slow down
priority_queue<ll, vector<ll>, greater<ll>> timeQueue;

// distQueue stoes the distances where the cow will slow down
priority_queue<ll, vector<ll>, greater<ll>> distQueue;

int main() { 
  FIO; 
  ofstream fout("slowdown.out");
  freopen("slowdown.in", "r", stdin);
  
  cin >> N;

  // read in the input, save to the timeQueue or distQueue accordingly
  for (ll i = 0; i< N; i++) {
    char c; ll x; cin >> c >> x;
    if (c == 'T') timeQueue.push(x);
    if (c == 'D') distQueue.push(x);
  }


  ld curTime = 0;
  ld curDist = 0;
  ll speedDen = 1;

/*
Change timeQueue and distQueue to be ints (also you can declare a priority queue of floats or ints as priority_queue<float> or priority_queue<int>, you don't need all the extra stuff you added). The denominator of speed is also not stored as an int, you have it as a long double so change that to an int (and use 1.0/speedDen when calculating speed instead of 1/speedDen to make it a float). Finally, at the end when you print, you want to round curTime + the expression you have, not do curTime plus rounding the expression. Let's say 1000*curTime = 1000.4 and the expression = 1000.4. If you do it the way you are doing, curTime + round(expression), you will get 2000, when you actually want 2001.
*/

// while either queue isn't empty
  while(timeQueue.size() > 0 || distQueue.size() > 0) {

    // time left to next slowing point in timeQueue 
    ld timeLeft = timeQueue.top()-curTime;

    // time left to next slowing point from distQueue
    ld distLeft = (distQueue.top()-curDist) / (1.0/speedDen);
    // cout << "for reference, next time: " << timeQueue.top() << ", next distance: " << distQueue.top() << endl;
    // cout << "dissecting distLeft: " << (distQueue.top()) << " - " << curDist << " divided by " << ()
    
    // cout <<"timeLeft: " << timeLeft << ", distLeft: " << distLeft << endl;

    // if the cow will reach the timeQueue's slowing point BEFORE the distQueue's, 
    if ((timeLeft < distLeft || distQueue.size() == 0) && timeQueue.size() > 0) {
      // update curTime, curDist, remove the item from the queue 
      curTime = timeQueue.top();
      curDist += timeLeft * (1.0/speedDen);
      timeQueue.pop();
    }
    // if cow will reach the distQueue's slowing point first
    else {
      // update curDist, curTime, delete item from distQueue
      curDist = distQueue.top();
      curTime += distLeft;
      distQueue.pop();
    }

    // slow down the speed
    speedDen++;


    // cout << "curTime " << curTime << ", curDist: " << curDist << ", speedDen " << speedDen << endl;
    // cout << timeQueue.size() <<" and " << distQueue.size() << endl;
  }
  // cout << speedDen << endl;

  // result is the curTime + time left to get to 1KM based on current speed
  // cout << curDist << " and " << speedDen << " and " << curTime << endl;
  fout << (ll) round(curTime + (1000-curDist) / (1.0/speedDen)) << endl;
  // not casting to ll may result in scientific notation
  
  // cout << timeLeft << " " << distLeft;
}

