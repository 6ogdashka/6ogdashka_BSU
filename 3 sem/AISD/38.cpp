#include <fstream>
#include <vector> 
#include <algorithm>
#include <string>


struct INT {
    std::string numb{};
    INT(std::string s) { numb = s; }

};

INT add(INT first_numb, INT second_numb) {
    if (first_numb.numb == "0") return second_numb;
    if (second_numb.numb == "0") return first_numb;

    std::string result;

    std::string max_str = (first_numb.numb.length() > second_numb.numb.length()) ? first_numb.numb : second_numb.numb;
    std::string min_str = (first_numb.numb.length() > second_numb.numb.length()) ? second_numb.numb : first_numb.numb;
    int max_size = max_str.length();
    int min_size = min_str.length();
    std::reverse(max_str.begin(),max_str.end());
    std::reverse(min_str.begin(),min_str.end());
    int one = 0;
    for ( int i{}; i < max_size; i++) {
        if ( i < min_size ) {
        int first_digit = max_str[i] - '0';
        int second_digit = min_str[i] - '0';

        if ( one == 1 ) {
            first_digit++;
            one = 0;
        }
        if ( ((first_digit + second_digit) / 10) > 0 ) {
            one = 1;
        }
        result += std::to_string((first_digit + second_digit)%10);
        } else {
            int digit = max_str[i] - '0';
            if ( ((digit + one) / 10) > 0 ) {
                result += "0";
            } else {
                result += std::to_string(digit + one);
                one = 0;
            }
        }
    }

    if ( one == 1) {
        result += "1";
    }

    std::reverse(result.begin(), result.end());
    return INT{result};
}

static const INT zero{"0"};
static const INT one{"1"};

int main() {
    std::ifstream in("in.txt");
    std::ofstream out("out.txt");

    int n;
    in >> n;

    int k;
    in >> k;

    int S{};
    int buff{};
    while ( in >> buff ) {
        S+=buff;
    }

    int a = n - S + 1;
    int b = k;

    if (a < b) {
        out << 0;
        return 0;
    }

    std::vector<std::vector<INT>> vec(205);
    for ( std::vector<INT>& i : vec) {
        i.push_back(zero);
    }
    vec[1].push_back(one);
    vec[1].push_back(zero);

    for ( int i{2};i <= 204; i++) {
        for ( int j{1}; j <= i; j++) {
            vec[i].push_back(add(vec[i-1][j-1],vec[i-1][j]));
        }
        vec[i].push_back(zero);
    }
    out << vec[a+1][b+1].numb;
}