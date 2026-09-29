#include <unordered_map>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

const std::unordered_map<char, char> letter_to_digit = {
    {'I', '1'}, {'J', '1'},
    {'A', '2'}, {'B', '2'}, {'C', '2'},
    {'D', '3'}, {'E', '3'}, {'F', '3'},
    {'G', '4'}, {'H', '4'},
    {'K', '5'}, {'L', '5'},
    {'M', '6'}, {'N', '6'},
    {'P', '7'}, {'R', '7'}, {'S', '7'},
    {'T', '8'}, {'U', '8'}, {'V', '8'},
    {'W', '9'}, {'X', '9'}, {'Y', '9'},
    {'O', '0'}, {'Q', '0'}, {'Z', '0'},
    {'0', '0'}, {'1', '1'}, {'2', '2'}, {'3', '3'}, {'4', '4'},
    {'5', '5'}, {'6', '6'}, {'7', '7'}, {'8', '8'}, {'9', '9'}
};

int main() {
    std::ifstream input("input.txt"); 
    std::ofstream out("output.txt");

    std::string phone_number;
    if (!(input >> phone_number)) return 0;
    
    const size_t size{phone_number.size()};
    const int INF = 1e9;
    
    std::vector<int> dp(size + 1, INF);
    std::vector<int> parent_pos(size + 1, -1);
    std::vector<std::string> parent_word(size + 1);
    dp[0] = 0;

    int n;
    if (!(input >> n)) return 0;

    std::vector<std::vector<std::pair<std::string, std::string>>> words(101);
    std::string word;
    size_t max_len{};

    for (int i{0}; i < n; i++) {
        input >> word;
        std::string original = word;
        for (char& j : word) { 
            j = letter_to_digit.at(j);
        }
        
        std::reverse(word.begin(), word.end());
        words[word.size()].push_back({word, original});
        if (word.length() > max_len) {
            max_len = word.length();
        }
    }

    for (auto& vec : words) {
        std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
    }

    size_t max_size{max_len};
    for (size_t i{1}; i <= size; i++) {
        max_size = (i < max_len) ? i : max_len;
        std::string str{};
        for (size_t j{1}; j <= max_size; j++) {
            str += phone_number[i - j];
            if (dp[i - j] != INF) {
                auto it = std::lower_bound(words[j].begin(), words[j].end(), str,
                    [](const std::pair<std::string, std::string>& a, const std::string& val) {
                        return a.first < val;
                    });

                if (it != words[j].end() && it->first == str) {
                    if (dp[i - j] + 1 < dp[i]) {
                        dp[i] = dp[i - j] + 1;
                        parent_pos[i] = i - j;
                        parent_word[i] = it->second;
                    }
                }
            }
        }
    }

    if (dp[size] == INF) {
        out << "No solution\n";
    } else {
        std::vector<std::string> result;
        size_t start = size;
        out << dp[size] << "\n";
        while (start > 0) {
            result.push_back(parent_word[start]);
            start = parent_pos[start];
        }
        std::reverse(result.begin(), result.end());

        for (size_t i = 0; i < result.size(); ++i) {
            if (i != result.size() - 1) {
                out << result[i] << " ";
            } else {
                out << result[i];
            }
        }
        out << "\n";
    }

    return 0;
}
