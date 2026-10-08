#include <fstream>
#include <vector>
#include <utility>

using ll = long long;

ll GetSum(std::vector<std::pair<ll,ll>>& vec, int i, int j) {
    const ll C = vec[i].first;
    ll result{};
    for ( int k{i+1}; k <= j; k++) {
        result += C*(vec[k].first*vec[k].second);
    }
    return result;
}


int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    size_t s{};
    in >> s;
    std::vector<std::pair<ll,ll>> vec{s};

    for ( ll i{}; i < s; i++) {
        in >> vec[i].first;
        in >> vec[i].second;
    }

    std::vector<std::vector<int>> dp(s,std::vector<int>(s));
    for ( int i{}; i < s; i++) {
        dp[i][i] = GetSum(vec,i,i);
    }
    
    for ( int l{2}; l <= s; l++ ) {
        for ( int k{};  k < s - l + 1; k++) {
            ll min = GetSum(vec,k,l+k-1);
            for ( int i{k+1};i < (l+k); i++){
                if ((dp[k][i-1] + dp[i][l+k-1] + vec[k].first*vec[i-1].second*vec[l+k-1].second) < min) {
                    min = (dp[k][i-1] + dp[i][l+k-1] + vec[k].first*vec[i-1].second*vec[l+k-1].second);
                }
            }
            dp[k][k+l-1] = min;
        }
    }

    out << dp[0][s-1];

    return 0;
}