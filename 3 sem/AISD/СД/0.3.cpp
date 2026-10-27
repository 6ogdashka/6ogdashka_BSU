#include <fstream>

const long long TWO = 2;

int main(){
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    long long n{};
    in >> n;
    
    for ( int i{}; i < 63; i++) {
        if (( n >> i) & 1) {
            out << i << "\n";
        }
    }

    return 0;

}