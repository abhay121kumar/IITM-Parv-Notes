
int longestCommonSubsequence(char* text1, char* text2) {
    int m = strlen(text1);
    int n = strlen(text2);
    if (m < n) {
        char* temp = text1; text1 = text2; text2 = temp;
        int t = m; m = n; n = t;
    }

    int dp[n + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= m; ++i) {
        int prev = 0;
        for (int j = 1; j <= n; ++j) {
            int temp = dp[j];
            if (text1[i - 1] == text2[j - 1]) {
                dp[j] = prev + 1;
            } else {
                dp[j] = dp[j] > dp[j - 1] ? dp[j] : dp[j - 1];
            }
            prev = temp;
        }
    }

    return dp[n];
}