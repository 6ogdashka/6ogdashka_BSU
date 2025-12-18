#include <iostream>
#include <fstream>
#include <random>
#include <exception>
#include <stdexcept>

template<typename T>
void selection_sort(T*, size_t);
void check_file(std::ifstream&);
void check_file(std::ofstream&);
void input_int_number(int32_t&);
template<typename T>
void input_manualy(T*, int32_t);
template<typename T>
void input_rng(T*, int32_t);
template<typename T>
void input_file(T*, int32_t&);
template<typename T>
void input(T*, int32_t);
template<typename T>
void output(T*, int32_t);


int main()
{
 try
 {
  std::cout << "integer solution:" << std::endl;
  std::cout << "input lenght of array" << std::endl;
  int32_t lenght;
  input_int_number(lenght);
  if (lenght < 0 && lenght > 100)
  {
   throw std::invalid_argument("invalid lenght");
  }
  int32_t* arr = new int32_t[lenght];
  //int32_t arr[100];
  input<int32_t>(arr, lenght);
  selection_sort(arr, lenght);
  output(arr, lenght);
  //delete[] arr;
  //arr = nullptr;
 }
 catch (std::exception& exception)
 {
  std::cerr << "Error occured:" << exception.what() << std::endl;
  std::cin.ignore();
 }
return 0;
}

void check_file(std::ifstream& fin) {
 if (!fin.good()) {
  throw ("file doesn't exists");
 }
 if (fin.peek() == EOF) {
  throw ("file is empty");
 }
}
void check_file(std::ofstream& fout) {
 if (!fout.good()) {
  throw ("file doesn't exists");
 }
}
void input_int_number(int32_t& number)
{
 if (!(std::cin >> number))
 {
  throw std::invalid_argument("not a number");
 }
}
template<typename T>
void selection_sort(T* arr, size_t lenght)
{
 size_t buff = lenght - 1;
 for (size_t i = 0; i < buff; i++)
 {
  std::pair<T, int32_t> local_min{};
  local_min.first = arr[i];
  local_min.second = i;
  for (size_t j = i; j < lenght; j++)
  {
   if (arr[j] < local_min.first)
   {
    local_min.first = arr[j];
    local_min.second = j;
   }
  }
  std::swap(arr[i], arr[local_min.second]);
 }
}
template<typename T>
void input_manualy(T* arr, int32_t lenght)
{
 for (size_t i = 0; i < lenght; ++i)
 {
  if (!(std::cin >> arr[i]))
  {
   throw ("invalid data");
  }
 }
}
template<typename T>
void input_rng(T* arr, int32_t lenght)
{
 std::random_device rd;
 std::mt19937 gen(rd());
 int32_t max;
 int32_t min;
 std::cout << "input borders of random values" << std::endl;
 input_int_number(min);
 input_int_number(max);
 if (min > max)
 {
  std::swap(min, max);
 }
 std::uniform_real_distribution<double> num(min, max);
 for (size_t i = 0; i < lenght; ++i)
 {
  arr[i] = (T)num(gen);
 }
}
template<typename T>
void input_file(T* arr, int32_t& lenght)
{
 std::ifstream fin("input.txt");
 //check_file(fin);
 int32_t i{};
 while (fin >> arr[i])
 {
  ++i;
 }
 lenght = i;
 fin.close();
}
template<typename T>
void input(T* arr, int32_t lenght)
{
 std::cout << "how do you want to input your array and get output? " << std::endl << "1) ipnut manualy" << std::endl << "2) RNG input" << std::endl << "3) input from input.txt" << std::endl;
 int32_t variant;
 input_int_number(variant);
 switch (variant)
 {
 case 1:
  input_manualy(arr, lenght);
  break;
 case 2:
 {
  input_rng(arr, lenght);
  break;
 }
 case 3:
 {
  input_file<int32_t>(arr, lenght);
  break;
 }
 default:
 {
  throw std::invalid_argument("invalid variant");
 }
 }
}
template<typename T>
void output(T* arr, int32_t lenght)
{
 std::ofstream fout("output.txt");
 for (size_t i = 0; i < lenght; ++i)
 {
  std::cout << arr[i] << ' ';
  fout << arr[i] << ' ';
 }
 std::cout << std::endl << "output only in output.txt" << std::endl;
}