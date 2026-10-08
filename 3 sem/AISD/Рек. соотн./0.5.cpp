#include <iostream>
#include <algorithm>
#include <vector>
#include <set>


void print_(const std::vector<std::vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return;

    size_t n = matrix.size() - 1;
    std::vector<int> a;
    std::vector<int> b;

    int i = static_cast<int>(n);
    int j = static_cast<int>(n);

    while (i > 0 && j > 0) {
        if (matrix[i][j] == matrix[i - 1][j]) {
            i--;
        } else if (matrix[i][j] == matrix[i][j - 1]) {
            j--;
        } else {
            a.push_back(i - 1);
            b.push_back(j - 1);
            i--;
            j--;
        }
    }

    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());

    for (size_t index = 0; index < a.size(); ++index) {
        std::cout << a[index] << (index + 1 == a.size() ? "" : " ");
    }
    std::cout << "\n";

    for (size_t index = 0; index < b.size(); ++index) {
        std::cout << b[index] << (index + 1 == b.size() ? "" : " ");
    }
    std::cout << "\n";

}

int main() {
    std::ios_base::sync_with_stdio(false),std::cin.tie(nullptr);
    freopen("input.txt","r",stdin);
    size_t n{};
    std::cin >> n;

    int* first_str = new int[n+1];
    int* second_str = new int[n+1];

    for ( size_t i{1}; i <= n; i++) {
        std::cin >> first_str[i];
    }

    for ( size_t i{1}; i <= n; i++) {
        std::cin >> second_str[i];
    }

    std::vector<std::vector<int>> dp(n+1, std::vector<int>(n+1, 0));
    std::set<int> parent_pos{};

    
    for ( size_t i{1}; i <= n; i++) {
        for ( size_t j{n}; j > 0; j--) {
            if ( first_str[i] == second_str[j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = std::max(dp[i-1][j], dp[i][j-1]);
            }   
        }
    }

    std::cout << dp[n][n] << "\n";
    print_(dp);
}