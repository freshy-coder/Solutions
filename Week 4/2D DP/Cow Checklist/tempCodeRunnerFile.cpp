l i = 0; i <= Hx; i++) {
    for (ll j = 0; j <= Gx; j++) {
      dp[i][j][0] = 1E10;
      dp[i][j][1] = 1E10;
    }
  }

  dp[1][0][0] = 0;
  cout << dist(H[1], G[1]) + dist(G[1], G[2]) + dist(G[2], G[3]) + dist(G[3], G[4]) + dist(G[4], G[5]) + dist(G[5], H[2]) + dist(H[2], H[3]) + dist(H[3], H[4]);


  for (ll i = 1; i <= Hx; i++) {
    for (ll j = 0; j <= Gx; j++) {
        ll a = 1E10; ll b = 1E10; ll c = 1E10; ll d = 1E10;

        if (i > 1) { // arriving at H
          a = dp[i-1][j][0] + dist(H[i-1], H[i]); // arriving from a previous H
          b = dp[i-1][j][1] + dist(G[j], H[i]); // arriving from a previous G

          // cout << "test: " << dist(G[j], H[i]) << endl;
          // cout <<"a: " << a << " and b: "<< b << endl;

          dp[i][j][0] = min(a,b);
        }

        if (j > 0) { // arriving at G
          if (j > 1) c = dp[i][j-1][1] + dist(G[j-1], G[j]); // arriving from a previous G
          d = dp[i][j-1][0] + dist(H[i], G[j]); // arriving from a previous H

          // cout << "test: " << dist(G[j-1], G[j]) << ", "<< dist(H[i], G[j]) << endl;
          // cout << "c: " << c << " and d: "<< d << endl;

          dp[i][j][1] = min(c,d);
        }
    }
  }
  
  fout << dp[