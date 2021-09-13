
// void add(vector<ll> a, vector<ll> og) { // only adds if not stepping on some haybale
//   if (a[0] >= N || a[0] < 0 || a[1] >= N || a[1] < 0 || grid[a[0]][a[1]] == 1){
//     a[0] = og[0]; a[1] = og[1];
//   }
//   if (a[2] >= N || a[2] < 0 || a[3] >= N || a[3] < 0 || grid[a[2]][a[3]] == 1){
//     a[2] = og[2]; a[3] = og[3];
//   }
//   q.push(a);
// }

// ll distAcc(vector<ll> x) {
//   return dist[x[0]][x[1]][x[2]][x[3]][x[4]];
// }

// void bfs() {
  
//   dist[N-1][0][N-1][0][0] = 0;
//   q.push({N-1, 0, N-1, 0, 0, 0}); // same as dp. i, j, x, y, rotation, length
//   ll count = 0;
//   while (!q.empty()) {
//     count++;

//     vector<ll> x = q.front();
//     // cout << count << endl;
//     // cout << "investigating: " << x[0]<<" " <<x[1]<<" " <<x[2]<<" " <<x[3]<<" " <<x[4] <<" " << x[5] << endl;
//     q.pop();

//     if (distAcc(x) != -1 && count != 1) {
//       continue;
//     }
//     dist[x[0]][x[1]][x[2]][x[3]][x[4]] = x[5];

//     ll inc = 0;
//     for (ll k = 1; k < 4; k++) { // all other possible rotations - 1,2,3
//       if (k == 2) inc = 2;
//       else inc = 1;
//       q.push({x[0],x[1],x[2],x[3],   (x[4]+k) % 4   , x[5]+(inc)});
//     }

//     // going forward
//     if (x[4] == 0) {
//       add({x[0],  x[1]+1  ,  x[2]-1  ,x[3],x[4],  x[5]+1  }, x); // A goes RIGHT, B goes UP
//     }
//     else if (x[4] == 1) {
//       add({  x[0]+1  ,x[1],x[2],  x[3]+1  ,x[4],  x[5]+1  }, x); // A goes DOWN, B goes RIGHT
//     }
//     else if (x[4] == 2) {
//       add({x[0],  x[1]-1  ,  x[2]+1  ,x[3],x[4],  x[5]+1  }, x); // A goes LEFT, B goes DOWN
//     }
//     else if (x[4] == 3) {
//       add({  x[0]-1  ,x[1],x[2],  x[3]-1  ,x[4],  x[5]+1  }, x); // A goes UP, B goes LEFT
//     }
    
//   }
// } 
