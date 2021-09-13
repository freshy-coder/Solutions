 0; i < N; i++) {
    dp[i][i][0] = abs(cows[i])*N;
    dp[i][i][1] = abs(cows[i])*N;
  }