#include <iostream>

int main() {
    int birth_day, birth_month, birth_year;
    int current_day, current_month, current_year;

    std::cout << "Введите дату рождения (день месяц год): ";
    std::cin >> birth_day >> birth_month >> birth_year;
    std::cout << "Введите текущую дату (день месяц год): ";
    std::cin >> current_day >> current_month >> current_year;

    int total_months_in_year = 12;
    int total_days_in_month = 30;

    int birth_total_days = (birth_year * total_months_in_year + birth_month) * total_days_in_month + birth_day;
    int current_total_days = (current_year * total_months_in_year + current_month) * total_days_in_month + current_day;

    int age_total_days = current_total_days - birth_total_days;

    int age_years = age_total_days / (total_months_in_year * total_days_in_month);
    int age_months = (age_total_days % (total_months_in_year * total_days_in_month)) / total_days_in_month;
    int age_days = age_total_days % total_days_in_month;

    std::cout << "Возраст: " << age_years << " лет, " << age_months << " месяцев, " << age_days << " дней\n";

    return 0;
}