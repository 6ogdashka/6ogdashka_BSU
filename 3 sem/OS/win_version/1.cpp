#include <iostream> 
#include <windows.h>
#include "threads.h"
using namespace std;
int main() { SetConsoleCP(1251); SetConsoleOutputCP(1251);
int size = 0;
cout << "Введите размер массива: ";
cin >> size;

if (size <= 0) {
    cout << "Неверный размер массива" << endl;
    return 1;
}

int* arr = new int[size];
cout << "Введите " << size << " элементов массива:" << endl;
for (int i = 0; i < size; ++i) {
    cin >> arr[i];
}

ThreadData data;
data.array = arr;
data.size = size;
data.min_index = 0;
data.max_index = 0;
data.average = 0.0;

HANDLE hMinMax;
HANDLE hAverage;
DWORD IDThreadMinMax;
DWORD IDThreadAverage;

hMinMax = CreateThread(NULL, 0, min_max, (void*)&data, 0, &IDThreadMinMax);
if (hMinMax == NULL) {
    delete[] arr;
    return GetLastError();
}

hAverage = CreateThread(NULL, 0, average, (void*)&data, 0, &IDThreadAverage);
if (hAverage == NULL) {
    CloseHandle(hMinMax);
    delete[] arr;
    return GetLastError();
}

WaitForSingleObject(hMinMax, INFINITE);
WaitForSingleObject(hAverage, INFINITE);

int avgInt = (int)data.average;
arr[data.min_index] = avgInt;
arr[data.max_index] = avgInt;

cout << "\nМассив после замены минимального и максимального элемента на среднее значение:" << endl;
for (int i = 0; i < size; ++i) {
    cout << arr[i] << " ";
}
cout << endl;

CloseHandle(hMinMax);
CloseHandle(hAverage);
delete[] arr;

return 0;
}