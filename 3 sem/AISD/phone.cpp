#include <string>
#include <algorithm>
#include <fstream>
#include <vector>

struct letter_to_digit {
    char glossary[256];
    letter_to_digit() {
        for (int i = 0; i < 256; ++i) glossary[i] = 0;
        glossary['I'] = '1'; glossary['J'] = '1';
        glossary['A'] = '2'; glossary['B'] = '2'; glossary['C'] = '2';
        glossary['D'] = '3'; glossary['E'] = '3'; glossary['F'] = '3';
        glossary['G'] = '4'; glossary['H'] = '4';
        glossary['K'] = '5'; glossary['L'] = '5';
        glossary['M'] = '6'; glossary['N'] = '6';
        glossary['P'] = '7'; glossary['R'] = '7'; glossary['S'] = '7';
        glossary['T'] = '8'; glossary['U'] = '8'; glossary['V'] = '8';
        glossary['W'] = '9'; glossary['X'] = '9'; glossary['Y'] = '9';
        glossary['O'] = '0'; glossary['Q'] = '0'; glossary['Z'] = '0';
        for (char c = '0'; c <= '9'; ++c) glossary[c] = c;
    }
} glossary;

struct TrieNode {
    int next[10];
    int word_id;
    
    TrieNode() {
        std::fill(std::begin(next), std::end(next), -1);
        word_id = -1;
    }
};

std::vector<TrieNode> trie;

void insert_trie(const std::string& reversed_digits, int id) {
    int v = 0;
    for (char ch : reversed_digits) {
        int c = ch - '0';
        if (trie[v].next[c] == -1) {
            trie[v].next[c] = trie.size();
            trie.emplace_back();
        }
        v = trie[v].next[c];
    }
    trie[v].word_id = id;
}

int main() {
    std::ifstream input("input.txt"); 
    std::ofstream out("output.txt");

    std::string phone_number;
    input >> phone_number;
    
    const size_t size{phone_number.size()};
    const int INF = 1e9;
    
    std::vector<int> dp(size + 1, INF);
    std::vector<int> parent_pos(size + 1, -1);
    std::vector<int> parent_word(size + 1, -1);
    dp[0] = 0;

    int n;
    input >> n;

    trie.reserve(n * 5);
    trie.emplace_back();
    std::vector<std::string> original_words;
    original_words.reserve(n);

    std::string word;
    for (int i{0}; i < n; i++) {
        input >> word;
        std::string original = word;
        
        for (char& j : word) { 
            j = glossary.glossary[static_cast<unsigned char>(j)];
        }
        
        std::reverse(word.begin(), word.end());
        
        original_words.push_back(original);
        insert_trie(word, original_words.size() - 1);
    }

    for (size_t i{1}; i <= size; i++) {
        int v = 0;
        
        for (size_t j{1}; j <= i; j++) {
            int digit = phone_number[i - j] - '0';
            v = trie[v].next[digit];
            
            if (v == -1) break; 

            if (dp[i - j] != INF && trie[v].word_id != -1) {
                if (dp[i - j] + 1 < dp[i]) {
                    dp[i] = dp[i - j] + 1;
                    parent_pos[i] = i - j;
                    parent_word[i] = trie[v].word_id; 
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
            result.push_back(original_words[parent_word[start]]);
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