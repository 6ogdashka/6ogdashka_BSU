#include <climits>
#include <fstream>
#include <utility>
#include <vector>

using ll = long long;

bool Lbelong( int value, std::pair<ll,ll> space) {
    return (value >= space.first && value < space.second);
}

bool Rbelong( int value, std::pair<ll,ll> space) {
    return (value >= space.first && value < space.second);
}

int main() {

    std::ifstream in("bst.in");
    std::ofstream out("bst.out");
    int n;
    in >> n;
    int root;
    in >> root;
    std::vector<int> values(n+1);
    std::vector<int> parents(n+1);
    std::vector<char> LR(n+1);
    std::vector<std::pair<ll,ll>> Lspaces(n+1);
    std::vector<std::pair<ll,ll>> Rspaces(n+1);
    values[1] = root;
    Rspaces[1] = std::make_pair(root,LONG_LONG_MAX);
    Lspaces[1] = std::make_pair(LONG_LONG_MIN, root);

    for ( int i{2}; i <= n; i++) {
        in >> values[i];
        in >> parents[i];
        in >> LR[i];
    }

    for (int i{2}; i <= n; i++) {
        if (LR[i] == 'R') {
            Rspaces[i] = std::make_pair(values[i], Rspaces[parents[i]].second);
            Lspaces[i] = std::make_pair(values[parents[i]], values[i]);
        } else {
            Rspaces[i] = std::make_pair(values[i],values[parents[i]]);
            Lspaces[i] = std::make_pair(Lspaces[parents[i]].first, values[i]);
        }
    }

    bool result{true};

    for ( int i{2}; i <= n; i++) {
        if ( LR[i] == 'L') {
            result = Lbelong(values[i], Lspaces[parents[i]]);
        } else {
            result = Rbelong(values[i], Rspaces[parents[i]]);
        }
        if ( result == false) break;
    }

    if ( result == false) {
        out << "NO";
    }  else {
        out << "YES";
    }
    return 0;
}