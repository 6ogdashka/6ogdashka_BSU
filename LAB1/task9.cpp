#include <iostream>

int get_hour_value ();
int get_minut_value();

int main() {
    try {
    std::cout << "Введите время прибытия (часы минуты): ";
    int arrival_hours = get_hour_value(), 
        arrival_minutes = get_minut_value();
    std::cout << "Введите время отправления (часы минуты): ";
    int departure_hours = get_hour_value(), 
        departure_minutes = get_minut_value();

    int arrival_total_minutes = arrival_hours * 60 + arrival_minutes;
    int departure_total_minutes = departure_hours * 60 + departure_minutes;

    int parking_time_minutes = departure_total_minutes - arrival_total_minutes;

    int parking_hours = parking_time_minutes / 60;
    int parking_minutes = parking_time_minutes % 60;

    std::cout << "Время стоянки: " << parking_hours << " часов " << parking_minutes << " минут\n";
    } catch ( const char* msg) { std::cout << msg;}
    return 0;
}

int get_hour_value () {
    int value;
    if (( std::cin >> value ) && ( value >= 0) && ( value <= 23)) {
        return value;
    } else {
        throw " Неверное колличество чассов!";
    }
}

int get_minut_value () {
    int value;
    if ( (std::cin >> value) && ( value >= 0) && ( value <= 59)) {
        return value;
    } else {
        throw " Неверное колличетсво минут!";
    }
}