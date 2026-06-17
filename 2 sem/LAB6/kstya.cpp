#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void printArray(vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    srand(time(NULL));
    int n;
    cout << "enter number of elements: ";
    cin >> n;

    vector<int> a;
    for (int i = 0; i < n; i++) {
        a.push_back(rand() % 201 - 100); 
    }

    cout << "your array:\n";
    printArray(a);
    int k, countN;
    //N элементов,начиная сномера K
    cout << "enter K and N: ";
    cin >> k >> countN;
    a.erase(a.begin() + k, a.begin() + k + countN);

    cout << "your array after erasion:\n";
    printArray(a);
//К элементов в начало массива
    int addK;
    cout << "enter new K: ";
    cin >> addK;

    for (int i = 0; i < addK; i++) {
        int randomNum = rand() % 201 - 100;
        a.insert(a.begin(), randomNum); 
    }

    cout << "your new array:\n";
    printArray(a);
    //Поменять местами минимальный и максимальный элементы
    int min_idx = 0;
    int max_idx = 0;
    for (int i = 1; i < a.size(); i++) {
        if (a[i] < a[min_idx]) {
            min_idx = i;
        }
        if (a[i] > a[max_idx]) {
            max_idx = i;
        }
    }
    int temp = a[min_idx];
    a[min_idx] = a[max_idx];
    a[max_idx] = temp;

    cout << "your new array:\n";
    printArray(a);
    //Простой обмен,Первый четный
    int comps = 0;
    int found_index = -1;
    
    for (int i = 0; i < a.size(); i++) {
        comps++;
        if (a[i] % 2 == 0) {
            found_index = i;
            break; 
        }
    }
    cout << "results of search:\n";
    if (found_index != -1) {
        cout << "first even number: " << a[found_index] << " at index " << found_index << "\n";
    } else {
        cout << "there is no even numbers\n";
    }
    cout << "number of comparasons: " << comps << "\n";
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < a.size() - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }

    cout << "your sorted array:\n";
    printArray(a);
    comps = 0;
    found_index = -1;
    
    for (int i = 0; i < a.size(); i++) {
        comps++;
        if (a[i] % 2 == 0) {
            found_index = i;
            break;
        }
    }

    cout << "result of search:\n";
    if (found_index != -1) {
        cout << "first even number:" << a[found_index] << " at index " << found_index << "\n";
    } else {
        cout << "there is no even numbers\n";
    }
    cout << "numer of comparasons: " << comps << "\n";

    return 0;
}