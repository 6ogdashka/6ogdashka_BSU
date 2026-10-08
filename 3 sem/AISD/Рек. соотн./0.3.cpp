#include <iostream>

const long long MOD = 1e9 + 7;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false),std::cin.tie(nullptr);

    long long n, k, result{1};
    
    std::cin >> n >> k;

    for (long long i = 1; i <= k; ++i) {
        result = (result * (n - i + 1)) % MOD;
        result = (result * power(i, MOD - 2)) % MOD;
    }

    std::cout << result << '\n';
    return 0;
}