#include <fstream>
#include <vector>

int main(){
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");
    int n;
    in >> n;
    std::vector<int> numbers{0};
    int buff;
    while(in >> buff) {
        numbers.push_back(buff);
    }
    bool result = true;

    for ( int i{n}; i/2 > 0; i++) {
        if ( numbers[i] <= numbers[i/2] ) {
            result = false;
            break;
        }
    }

    for ( int i{n}; i/2 + 1 > 0; i++) {
        if ( numbers[i] <= numbers[i/2 + 1]) {
            result = false;
            break;
        }
    }
    
    (result == false) ? out << "No" : out << "Yes";
    return 0;

}