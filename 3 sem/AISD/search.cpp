#include <iostream>
#include <tuple>
#include <vector>

std::tuple<int, int, int> binarySearch(int target, const std::vector<int>& vec) {
    int n = static_cast<int>(vec.size());

    int left = 0;
    int right = n;
    while (left < right) {
        int mid = (right + left) / 2;
        if (vec[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    int l = left;

    left = 0;
    right = n;
    while (left < right) {
        int mid = (right + left) / 2;
        if (vec[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    int r = left;

    int found = 0;
    if (l < n) {
        if (vec[l] == target) {
            found = 1;
        }
    }

    std::tuple<int, int, int> result{found, l, r};
    return result;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }

    int k;
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        int target;
        std::cin >> target;
        std::tuple<int, int, int> res = binarySearch(target, vec);
        std::cout << std::get<0>(res) << ' ' << std::get<1>(res) << ' ' << std::get<2>(res) << '\n';
    }

    return 0;
}