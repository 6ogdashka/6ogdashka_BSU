#include <fstream>
#include <vector>

int main() {
    std::ifstream input("input.txt");
    std::ofstream out("output.txt");
    int n{};
    input >> n;

    std::vector<int> vec(n);
    for ( int i{}; i< n; i++) {
        input >> vec[i];
    }

    std::vector<int> last{};

    for ( int i : vec) {
        auto it = std::lower_bound(last.begin(),last.end(),i);
        if ( it == last.end()) {
            last.push_back(i);
        } else {
            *it = i;
        }
    }

    out << last.size();
     
}