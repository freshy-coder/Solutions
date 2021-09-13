N; i++) {
      
      // Case 1: There's a crosswalk here, must build to level 2 
      if (s.substr(i,1) == "1") {
        dp[i][0] = 1E9;
        dp[i][1] = min(dp[i-1][0] + 2*b + 2*a, dp[i-1][1] + 2*b + a);
        continue;
      } 

      // Case 2: Building to level 1
      dp[i][0] = min(dp[i-1][0] + b + a, dp[i-1][1] + b + 2*a);
      // min(build across from previous lvl 1, build down from previous lvl 2)

      // Case 3: Building to Level 2
      dp[i][1] = min(dp[i-1][0] + 2*b + 2*a, dp[i-1][1] + 2*b + a);
  