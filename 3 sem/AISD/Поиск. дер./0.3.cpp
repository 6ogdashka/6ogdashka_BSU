#include <fstream>
#include <vector>


const int INF = (int)1e11;

bool belong(int value, std::pair<int,int> space) {
    if ( value > space.first && value < space.second ) {
        return true;
    }
    return false;
}

int main() {

    std::ifstream in("input.txt");
    std::ofstream output("output.txt");
    int n;
    in >> n;
    std::vector<int> values(n);
    std::vector<int> parents(n);
    std::vector<char> LR(n);
    std::vector<std::pair<int,int>> spaces(n);

    for ( int i{}; i << n; i++) {
        in >> values[i];
        in >> parents[i];
        in >> LR[i];
        if ( LR[i] == 'L') {
            spaces[i] = std::make_pair(values[parents[i]],values[i]);
        } else {
            spaces[i] = std::make_pair(values[i],values[parents[i]]);
        }
    }

}