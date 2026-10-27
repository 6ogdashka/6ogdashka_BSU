#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

void print_(const std::vector<std::vector<int>>& matrix, const char* first_str, const char* second_str, std::ofstream& out) {
    size_t n = matrix.size() - 1;
    size_t i = n;
    size_t j = n;
    std::string palindrome{};

    while (i > 0 && j > 0) {
        if (first_str[i] == second_str[j]) {
            palindrome.push_back(first_str[i]);
            i--;
            j--;
        } else if (matrix[i - 1][j] >= matrix[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    out << matrix[n][n] << "\n";
    out << palindrome;
}

int main() {
    std::ios_base::sync_with_stdio(false),std::cin.tie(nullptr);
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    std::string s{};
    in >> s;

    size_t n = s.length();

    char* first_str = new char[n + 1];
    char* second_str = new char[n + 1];

    for (size_t i{1}; i <= n; i++) {
        first_str[i] = s[i - 1];
    }

    for (size_t i{1}; i <= n; i++) {
        second_str[i] = s[n - i];
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1, 0));

    for (size_t i{1}; i <= n; i++) {
        for (size_t j{1}; j <= n; j++) {
            if (first_str[i] == second_str[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }   
        }
    }

    print_(dp, first_str, second_str, out);

}
