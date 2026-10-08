#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n{};
    std::cin >> n;
    std::vector<int> vec(n+1);
    for (int i = 1; i <= n; i++) {
        std::cin >> vec[i];
    }

    if (n == 1) {
        std::cout << vec[1] << "\n";
        std::cout << n;
        return 0;
    }
    if ( n == 2 ) {
        std::cout << -1;
        return 0;
    }

    std::vector<int> dp(n + 1, -1);
    std::vector<int> parent_pos(n + 1, -1);

    dp[1] = vec[1];
    parent_pos[1] = 0;

    for (int i = 3; i <= n; i++) {

        if ( dp[i-2] > dp[i-3] ) {
            dp[i] = vec[i] + dp[i-2];
            parent_pos[i] = i - 2;
        } else {
            dp[i] = vec[i] + dp[i-3];
            parent_pos[i] = i - 3;
        }
    }

    std::vector<int> path;
    for (int i = n; i !=0; i = parent_pos[i]) {
        path.push_back(i);
    }
    std::reverse(path.begin(), path.end());

    std::cout << dp[n] << "\n";
    for (int i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i != path.size() - 1) {
            std::cout << " ";
        }
    }

    return 0;
}
