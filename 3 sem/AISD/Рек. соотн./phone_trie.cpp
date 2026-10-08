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

struct TrieNode {
    int next[10];
    int word_id{-1};

    TrieNode() {
        std::fill(std::begin(next), std::end(next), -1);
    }
};

void insert_word(std::vector<TrieNode>& trie, const std::string& digit_word, int word_id) {
    int current_node_idx = 0;
    for (char digit_char : digit_word) {
        int digit = digit_char - '0';
        if (trie[current_node_idx].next[digit] == -1) {
            trie[current_node_idx].next[digit] = trie.size();
            trie.emplace_back();
        }
        current_node_idx = trie[current_node_idx].next[digit];
    }
    trie[current_node_idx].word_id = word_id;
}

int main() {
    std::ifstream input("input.txt"); 
    std::ofstream out("output.txt");

    std::string phone_number;
    input >> phone_number;
    
    const size_t phone_length = phone_number.size();
    const int INF = 1e9;
    
    std::vector<int> dp(phone_length + 1, INF);
    std::vector<int> parent_pos(phone_length + 1, -1);
    std::vector<int> parent_word_id(phone_length + 1, -1);
    dp[0] = 0;

    int dictionary_size;
    input >> dictionary_size;

    std::vector<TrieNode> trie;
    trie.reserve(500000);
    trie.emplace_back();

    std::vector<std::string> dictionary_words(dictionary_size);
    std::string raw_word;

    for (int word_idx = 0; word_idx < dictionary_size; ++word_idx) {
        input >> raw_word;
        dictionary_words[word_idx] = raw_word;
        for (char& letter : raw_word) { 
            letter = letter_to_digit.at(letter);
        }
        insert_word(trie, raw_word, word_idx);
    }

    for (size_t start_pos = 0; start_pos < phone_length; ++start_pos) {
        if (dp[start_pos] == INF) continue;

        int current_node_idx = 0;
        for (size_t curr_pos = start_pos; curr_pos < phone_length; ++curr_pos) {
            int digit = phone_number[curr_pos] - '0';

            if (trie[current_node_idx].next[digit] == -1) {
                break;
            }

            current_node_idx = trie[current_node_idx].next[digit];

            if (trie[current_node_idx].word_id != -1) {
                if (dp[start_pos] + 1 < dp[curr_pos + 1]) {
                    dp[curr_pos + 1] = dp[start_pos] + 1;
                    parent_pos[curr_pos + 1] = start_pos;
                    parent_word_id[curr_pos + 1] = trie[current_node_idx].word_id;
                }
            }
        }
    }

    if (dp[phone_length] == INF) {
        out << "No solution\n";
    } else {
        std::vector<std::string> result;
        result.reserve(dp[phone_length]);

        size_t start = phone_length;
        out << dp[phone_length] << "\n";
        while (start > 0) {
            result.push_back(dictionary_words[parent_word_id[start]]);
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