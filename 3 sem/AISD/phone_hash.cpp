#include <unordered_map>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

using ull = unsigned long long;

constexpr ull MOD1{1000000007};
constexpr ull MOD2{1000000009};
constexpr ull P1{313};
constexpr ull P2{10007};
constexpr int INF = 1e9;

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

struct Word {
    ull hash;
    int word_id;

    bool operator<(const Word& other) const {
        return hash < other.hash;
    }
};

int main() {
    std::ifstream input("input.txt"); 
    std::ofstream out("output.txt");

    std::string phone_number;
    input >> phone_number;
    
    const size_t phone_length{phone_number.size()};
    
    std::vector<int> dp(phone_length + 1, INF);
    std::vector<int> parent_pos(phone_length + 1, -1);
    std::vector<int> parent_word_id(phone_length + 1, -1);
    dp[0] = 0;

    int dictionary_size;
    input >> dictionary_size;

    std::vector<std::string> dictionary_words(dictionary_size);
    std::vector<std::vector<Word>> words(101);

    std::string raw_word;
    for (int i{0}; i < dictionary_size; ++i) {
        input >> raw_word;
        dictionary_words[i] = raw_word;

        ull hash1{0}, hash2{0};
        for (char letter : raw_word) {
            char digit{letter_to_digit.at(letter)};
            hash1 = (hash1 * P1 + digit) % MOD1;
            hash2 = (hash2 * P2 + digit) % MOD2;
        }
        ull comb_hash{(hash1 << 32) | hash2};

        words[raw_word.size()].push_back({comb_hash, i});
    }

    std::vector<int> existing_lens;
    for (size_t i{1}; i <= 100; ++i) {
        if (!words[i].empty()) {
            std::sort(words[i].begin(), words[i].end());
            words[i].erase(
                std::unique(words[i].begin(), words[i].end(),
                    [](const Word& a, const Word& b) {
                        return a.hash == b.hash;
                    }),
                words[i].end()
            );
            existing_lens.push_back(i);
        }
    }

    std::vector<ull> pow1(101, 1), pow2(101, 1);
    for (size_t i{1}; i <= 100; ++i) {
        pow1[i] = (pow1[i - 1] * P1) % MOD1;
        pow2[i] = (pow2[i - 1] * P2) % MOD2;
    }

    std::vector<ull> prefMOD1(phone_length + 1, 0), prefMOD2(phone_length + 1, 0);
    for (size_t i{0}; i < phone_length; ++i) {
        char digit{phone_number[i]};
        prefMOD1[i + 1] = (prefMOD1[i] * P1 + digit) % MOD1;
        prefMOD2[i + 1] = (prefMOD2[i] * P2 + digit) % MOD2;
    }

    for (size_t curr_pos{1}; curr_pos <= phone_length; ++curr_pos) {
        for (size_t len : existing_lens) {
            if (len > curr_pos) break;

            size_t start_pos{curr_pos - len};
            if (dp[start_pos] != INF) {
                ull hash1{(prefMOD1[curr_pos] + MOD1 - (prefMOD1[start_pos] * pow1[len]) % MOD1) % MOD1};
                ull hash2{(prefMOD2[curr_pos] + MOD2 - (prefMOD2[start_pos] * pow2[len]) % MOD2) % MOD2};
                ull hash{(hash1 << 32) | hash2};

                const auto& vec = words[len];
                auto it = std::lower_bound(vec.begin(), vec.end(), hash,
                    [](const Word& w, ull val) {
                        return w.hash < val;
                    });

                if (it != vec.end() && it->hash == hash) {
                    if (dp[start_pos] + 1 < dp[curr_pos]) {
                        dp[curr_pos] = dp[start_pos] + 1;
                        parent_pos[curr_pos] = start_pos;
                        parent_word_id[curr_pos] = it->word_id;
                    }
                }
            }
        }
    }

    if (dp[phone_length] == INF) {
        out << "No solution\n";
    } else {
        std::vector<std::string> result;
        result.reserve(dp[phone_length]);

        size_t start{phone_length};
        out << dp[phone_length] << "\n";
        while (start > 0) {
            result.push_back(dictionary_words[parent_word_id[start]]);
            start = parent_pos[start];
        }
        std::reverse(result.begin(), result.end());

        for (size_t i{0}; i < result.size(); ++i) {
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