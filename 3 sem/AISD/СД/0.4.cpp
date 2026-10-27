#include <iostream>
#include <queue>
#include <fstream>

using ll = long long;

ll get_min(std::queue<ll>& q1, std::queue<ll>& q2) {
    if (q1.empty()) {
        ll result = q2.front();
        q2.pop();
        return result;
    }
    if (q2.empty()) {
        ll result = q1.front();
        q1.pop();
        return result;
    }
    if (q1.front() <= q2.front()) {
        ll result = q1.front();
        q1.pop();
        return result;
    } else {
        ll result = q2.front();
        q2.pop();
        return result;
    }
}

int main() {
    std::ifstream in("huffman.in");
    std::ofstream out("huffman.out");

    ll n;
    in >> n;

    std::queue<ll> q1;
    std::queue<ll> q2;
    for (ll i = 0; i < n; ++i) {
        ll freq;
        in >> freq;
        q1.push(freq);
    }

    ll length = 0;
    while (q1.size() + q2.size() > 1) {
        ll first = get_min(q1, q2);
        ll second = get_min(q1, q2);
        ll sum = first + second;
        length += sum;
        q2.push(sum);
    }

    out << length;

    return 0;
}