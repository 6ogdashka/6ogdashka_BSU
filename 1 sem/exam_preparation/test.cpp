#include <iostream>
#include <vector>

void PickSort ( std::vector<s>& vec) {
    for ( size_t i{}; i < vec.size(); ++i) {
        size_t min = vec[i];
        size_t pos{i};
        for ( size_t j {i}; j < vec.size();++j) {
            if ( vec[j] < min ) {
                min = vec[j];
                pos = j;
            }
        }
        std::swap(vec[i],vec[pos]);
    }
}

int main () {
    std::vector<size_t> vec = {9,8,7,6,5,4,3,2,1};
    PickSort(vec);
    std::cout << vec[0];
    std::cout << vec[3];

}