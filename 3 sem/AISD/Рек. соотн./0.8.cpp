#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false),std::cin.tie(nullptr);
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");

    int x, y, z;
    in >> x >> y >> z;

    const int CHANGE_COST = std::min(x + y, z);

    std::string s1, s2;
    in >> s1;
    in >> s2;

    int n = s1.length();
    int m = s2.length();

    char* first_str  = new char[n + 1]();
    char* second_str = new char[m + 1]();

    for (int i = 1; i <= n; ++i) {
        first_str[i] = s1[i - 1];
    }
    for (int i = 1; i <= m; ++i) {
        second_str[i] = s2[i - 1];
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    for (int i = 1; i <= n; ++i) dp[i][0] = i * x;
    for (int j = 1; j <= m; ++j) dp[0][j] = j * y;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int cost = (first_str[i] == second_str[j]) ? 0 : CHANGE_COST;
            dp[i][j] = std::min({dp[i - 1][j] + x,dp[i][j - 1] + y,dp[i - 1][j - 1] + cost});
        }
    }

    out << dp[n][m];

    return 0;
}