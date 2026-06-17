#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

class Calculator : public QDialog {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitClicked();        // Слот для обработки нажатий на кнопки цифр/букв
    void operationClicked();    // Слот для выбора арифметического действия
    void equalClicked();        // Слот для запуска вычислений
    void clearAll();            // Слот сброса всех данных калькулятора
    void baseChanged(int baseId); // Слот для переключения системы счисления

private:
    void updateButtonStates();  // Метод, блокирующий недопустимые для текущей СС кнопки
    void calculate(long long rightOperand, const QString &pendingOperator); // Вычислитель

    QLineEdit *display;         // Экран отображения чисел
    QPushButton *digitButtons[16]; // Массив кнопок ввода (0-9, A-F)
    QPushButton *addButton;     // Кнопка сложения
    QPushButton *subButton;     // Кнопка вычитания
    QPushButton *mulButton;     // Кнопка умножения
    QPushButton *divButton;     // Кнопка деления
    QPushButton *equalButton;   // Кнопка вычисления результата
    QPushButton *clearButton;   // Кнопка очистки дисплея

    QButtonGroup *baseGroup;    // Группа переключателей систем счисления
    QRadioButton *binRadio;     // Радио-кнопка двоичной СС
    QRadioButton *octRadio;     // Радио-кнопка восьмеричной СС
    QRadioButton *decRadio;     // Радио-кнопка десятичной СС
    QRadioButton *hexRadio;     // Радио-кнопка шестнадцатеричной СС

    long long sumInMemory;      // Переменная для хранения накопленного результата
    QString pendingOperation;   // Переменная для хранения текущей операции
    bool isWaitingForOperand;   // Флаг: ждем ли ввод нового числа
    int currentNumBase;         // Текущее основание системы счисления (2, 8, 10, 16)
};

#endif