#include <iostream>
#include <random>
#include <algorithm>
#include <utility>
#include <vector>

void CinVec(std::vector<int>& vec);
void Delete(std::vector<int>& vec); 
void Generate(std::vector<int>& vec);
void Insert(std::vector<int>& vec1);
void Replace(std::vector<int>& vec);
std::pair<int,int> Find(std::vector<int>& vec);
void InsertionSort(std::vector<int>& vec);

int main() {

    size_t n;
    std::cout << "Введите размер массива:";
    std::cin >> n;
    std::vector<int> vec(n);
    Generate(vec);
    std::cout << "Сгенерированный массив: ";
    CinVec(vec);
    Delete(vec);
    std::cout << "Массив после удаления: ";
    CinVec(vec);
    Insert(vec);
    std::cout << "Массив после склеивания: ";
    CinVec(vec);
    Replace(vec);
    std::cout << "Массив посел обмена: ";
    CinVec(vec);
    std::cout << "Первый отрицательный элемент это:" << Find(vec).first << ".Потребовалось " << Find(vec).second << " сравнений.\n";
    InsertionSort(vec);
    std::cout << "Отсортированый массив: ";
    CinVec(vec);
    std::cout << "Теперь первый отрицательный элемент это:" << Find(vec).first << ".Потребовалось " << Find(vec).second << " сравнений.\n";
}

void Generate(std::vector<int>& vec) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distrib(-10000000,1000000);
    std::generate(vec.begin(), vec.end(), [&] { return distrib(gen); });
}

void CinVec(std::vector<int>& vec) {
    for ( int i : vec) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

void Delete(std::vector<int>& vec) {
    for ( int i{0}; i < vec.size(); i++) {
        vec.erase(vec.begin() + i);
    }
}

void Insert(std::vector<int>& vec1) {
    std::cout << "Введите число k:";
    int k{};
    std::cin >> k;
    std::cout << "Введите k новых элементов: ";
    std::vector<int> vec2(k);
    for ( int i{}; i < k; ++i) {
        std::cin >> vec2[i];
    }
    vec1.insert(vec1.end(), vec2.begin(), vec2.end());
}

void Replace(std::vector<int>& vec) {
    if (vec.empty()) return;
    std::swap(*std::max_element(vec.begin(), vec.end()),*std::min_element(vec.begin(), vec.end()));
}

std::pair<int,int> Find(std::vector<int>& vec) {
    int a{};
    for ( int i : vec) {
        if ( i < 0) {
            ++a;
            return std::make_pair(i, a);
        }
        ++a;

    }
    return std::make_pair(-1, -1);
}

void InsertionSort(std::vector<int>& vec) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        auto insertion_point = std::upper_bound(vec.begin(), it, *it);
        std::rotate(insertion_point, it, std::next(it));
    }
}