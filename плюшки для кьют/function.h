#include <QFile>
#include <QDataStream>
#include <QVector>
#include <QString>
#include <QDate>
#include <QDebug>

struct Patient {
    QString name;
    int age;
    double weight;
    QDate admissionDate;

    // Оператор для чтения из бинарного потока
    friend QDataStream& operator>>(QDataStream& in, Patient& p) {
        in >> p.name >> p.age >> p.weight >> p.admissionDate;
        return in;
    }
    
    // Оператор для записи в бинарный поток (чтобы было как создавать файлы)
    friend QDataStream& operator<<(QDataStream& out, const Patient& p) {
        out << p.name << p.age << p.weight << p.admissionDate;
        return out;
    }
};

// Функция 1: Считывает весь файл и возвращает новый QVector
static QVector<Patient> readAllBinary(const QString& filename) {
    QVector<Patient> result;
    QFile file(filename);
    
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        // Важно: в Qt 6 можно задать версию потока, чтобы избежать проблем с совместимостью
        // in.setVersion(QDataStream::Qt_6_0); 
        
        while (!in.atEnd()) {
            Patient p;
            in >> p;
            result.append(p);
        }
        file.close();
    } else {
        qWarning() << "Не удалось открыть файл для чтения:" << filename;
    }
    return result;
}

// Функция 2: Добавляет данные из бинарного файла в уже существующий вектор (передача по ссылке)
static bool appendFromBinary(const QString& filename, QVector<Patient>& existingVector) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        return false; // Ошибка открытия
    }
    
    QDataStream in(&file);
    while (!in.atEnd()) {
        Patient p;
        in >> p;
        existingVector.append(p);
    }
    
    file.close();
    return true; // Успешно считано
}

#include <QFile>
#include <QTextStream>
#include <QVector>
#include "med.h"

QVector<Drug> readTextStream(const QString& filename) {
    QVector<Drug> result;
    QFile file(filename);
    
    // Флаг QIODevice::Text обязателен для текстовых файлов (выравнивает символы \r\n)
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        
        while (!in.atEnd()) {
            Drug d;
            // Считываем данные последовательно, как из std::cin
            in >> d.Name >> d.myDate >> d.Section >> d.Count;
            
            // Проверка, что мы не считали пустую строку в самом конце файла
            if (!d.Name.isEmpty()) {
                result.append(d);
            }
        }
        file.close();
    }
    return result;
}


class MyClass {
    int* data; // Пример динамического ресурса
public:
    // 1. Конструктор по умолчанию (бонус)
    MyClass() : data(new int(0)) {}

    // 2. Деструктор
    ~MyClass() { delete data; }

    // 3. Конструктор копирования
    MyClass(const MyClass& other) {
        data = new int(*other.data);
    }

    // 4. Оператор присваивания копированием
    MyClass& operator=(const MyClass& other) {
        if (this != &other) { // Защита от самоприсваивания
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }

    // 5. Конструктор перемещения (&& - rvalue ссылка)
    MyClass(MyClass&& other) noexcept : data(other.data) {
        other.data = nullptr; // Забираем ресурс, обнуляем у источника
    }

    // 6. Оператор присваивания перемещением
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
};


struct Point {
    int x, y;

    // Сравнение (внутри структуры)
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Point& other) const { return !(*this == other); }
    bool operator<(const Point& other) const { return x < other.x; } // Полезно для сортировки

    // Арифметика (внутри структуры)
    Point operator+(const Point& other) const { return {x + other.x, y + other.y}; }

    // Ввод/Вывод (обязательно friend и вне структуры)
    friend QTextStream& operator<<(QTextStream& out, const Point& p) {
        out << p.x << " " << p.y;
        return out;
    }
    friend QTextStream& operator>>(QTextStream& in, Point& p) {
        in >> p.x >> p.y;
        return in;
    }
};
