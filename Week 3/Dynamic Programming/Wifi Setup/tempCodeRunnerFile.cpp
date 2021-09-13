push_back(2*x);
  }
  sort(pos.begin(), pos.end());

  for (ll i = 1; i <= N; i++) {
    dp[i] = 1E9;
    for (ll s = 1; s <= i; s++) {
      dp[i] = min(dp[i], dp[s-1] + a + (b*(pos[i]-pos[s])/2));
    }
  }
  cout << dp[N];