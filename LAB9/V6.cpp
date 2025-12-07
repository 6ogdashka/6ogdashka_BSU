#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int expandAroundCenter(const std::string& s, int left, int right);
int maxPalindromeLength(const std::string& str);
void checkInputFile(std::ifstream& fin);
void checkOutputFile(std::ofstream& fout);

int main() {
  try {

    std::ifstream file("input.txt");
    checkInputFile(file);
    std::ofstream ofile("output.txt");
    checkOutputFile(ofile);

    std::string current_str;
    int maxPalindromeLen = 0;
    std::vector<std::string> words;
    std::unordered_map<std::string, int> palindromeLengths;

    while (std::getline(file, current_str)) {
      int currentLen = maxPalindromeLength(current_str);
      
      if (currentLen > maxPalindromeLen) {
        maxPalindromeLen = currentLen;
      }
      
      words.push_back(current_str);
      palindromeLengths[current_str] = currentLen;
    }

    if (words.empty()) {
      throw " words dont exist in file";
    }

    file.close();

    int counter = 0;
    for (size_t i = 0; i < words.size(); ++i) {
      if ((palindromeLengths[words[i]] == maxPalindromeLen) && (counter < 10)){
        ofile << words[i] << '\n';
        ++counter;
      }
    }

    ofile.close();

  } catch (const char* msg) {
    std::cerr << "Error: " << msg << std::endl;
    return 1;
  }
  return 0;
}

void checkInputFile(std::ifstream& fin) {
    if (!fin.good()) {
        throw "doesn't exists";
    }
    if (fin.peek() == EOF) {
        throw "file is empty";
    }
}

void checkOutputFile(std::ofstream& fout) {
    if (!fout.good()) {
        throw "doesn't exist";
    }
}

int expandAroundCenter(const std::string& s, int left, int right) {
  while (left >= 0 && right < static_cast<int>(s.length()) && 
         s[left] == s[right]) {
    left--;
    right++;
  }
  return right - left - 1;
}

int maxPalindromeLength(const std::string& str) {
  if (str.empty()) {
    return 0;
  }

  int maxLen = 0;

  for (int i = 0; i < static_cast<int>(str.length()); i++) {
    int len1 = expandAroundCenter(str, i, i);
    int len2 = expandAroundCenter(str, i, i + 1);

    if (len1 > maxLen) maxLen = len1;
    if (len2 > maxLen) maxLen = len2;
  }

  return maxLen;
}