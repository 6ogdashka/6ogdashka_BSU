#include <iostream>

int main() {
    int arrival_hours, arrival_minutes;
    int departure_hours, departure_minutes;

    std::cout << "Введите время прибытия (часы минуты): ";
    std::cin >> arrival_hours >> arrival_minutes;
    std::cout << "Введите время отправления (часы минуты): ";
    std::cin >> departure_hours >> departure_minutes;

    int arrival_total_minutes = arrival_hours * 60 + arrival_minutes;
    int departure_total_minutes = departure_hours * 60 + departure_minutes;

    int parking_time_minutes = departure_total_minutes - arrival_total_minutes;

    int parking_hours = parking_time_minutes / 60;
    int parking_minutes = parking_time_minutes % 60;

    std::cout << "Время стоянки: " << parking_hours << " часов " << parking_minutes << " минут\n";

    return 0;
}