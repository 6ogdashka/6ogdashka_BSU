class Solution {
public:
    bool isSubsequence(std::string s, std::string t) {
        size_t i = 0;
        for (char c : t) {
            if (i < s.size() && s[i] == c) {
                ++i;
            }
        }
        return i == s.size();
    }
};