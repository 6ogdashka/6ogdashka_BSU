#include "calculator.h"
#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QDialog(parent), sumInMemory(0), pendingOperation(""), isWaitingForOperand(true), currentNumBase(10) {

    // Собираем интерфейс: дисплей сверху, радио-кнопки для выбора СС под ним
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    display = new QLineEdit("0", this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    QFont font = display->font();
    font.setPointSize(18);
    display->setFont(font);
    mainLayout->addWidget(display);

    QHBoxLayout *radioLayout = new QHBoxLayout();
    baseGroup = new QButtonGroup(this);

    binRadio = new QRadioButton("BIN (2)", this);
    octRadio = new QRadioButton("OCT (8)", this);
    decRadio = new QRadioButton("DEC (10)", this);
    hexRadio = new QRadioButton("HEX (16)", this);
    decRadio->setChecked(true);

    baseGroup->addButton(binRadio, 2);
    baseGroup->addButton(octRadio, 8);
    baseGroup->addButton(decRadio, 10);
    baseGroup->addButton(hexRadio, 16);

    radioLayout->addWidget(binRadio);
    radioLayout->addWidget(octRadio);
    radioLayout->addWidget(decRadio);
    radioLayout->addWidget(hexRadio);
    mainLayout->addLayout(radioLayout);

    // Рисуем сетку кнопок для ввода цифр и букв
    QGridLayout *gridLayout = new QGridLayout();
    QString charMap = "0123456789ABCDEF";

    for (int i = 0; i < 16; ++i) {
        digitButtons[i] = new QPushButton(QString(charMap[i]), this);
        digitButtons[i]->setMinimumSize(40, 40);
        connect(digitButtons[i], &QPushButton::clicked, this, &Calculator::digitClicked);
    }

    // Расставляем кнопки по своим местам в сетке
    gridLayout->addWidget(digitButtons[7], 0, 0);
    gridLayout->addWidget(digitButtons[8], 0, 1);
    gridLayout->addWidget(digitButtons[9], 0, 2);
    gridLayout->addWidget(digitButtons[10], 0, 3);

    gridLayout->addWidget(digitButtons[4], 1, 0);
    gridLayout->addWidget(digitButtons[5], 1, 1);
    gridLayout->addWidget(digitButtons[6], 1, 2);
    gridLayout->addWidget(digitButtons[11], 1, 3);

    gridLayout->addWidget(digitButtons[1], 2, 0);
    gridLayout->addWidget(digitButtons[2], 2, 1);
    gridLayout->addWidget(digitButtons[3], 2, 2);
    gridLayout->addWidget(digitButtons[12], 2, 3);

    gridLayout->addWidget(digitButtons[0], 3, 0);
    gridLayout->addWidget(digitButtons[13], 3, 1);
    gridLayout->addWidget(digitButtons[14], 3, 2);
    gridLayout->addWidget(digitButtons[15], 3, 3);

    // Добавляем кнопки действий
    clearButton = new QPushButton("C", this);
    addButton   = new QPushButton("+", this);
    subButton   = new QPushButton("-", this);
    mulButton   = new QPushButton("*", this);
    divButton   = new QPushButton("/", this);
    equalButton = new QPushButton("=", this);

    gridLayout->addWidget(clearButton, 0, 4);
    gridLayout->addWidget(addButton, 1, 4);
    gridLayout->addWidget(subButton, 2, 4);
    gridLayout->addWidget(mulButton, 3, 4);
    gridLayout->addWidget(divButton, 4, 0);
    gridLayout->addWidget(equalButton, 4, 1, 1, 4);

    mainLayout->addLayout(gridLayout);

    // Связываем кнопки со слотами логики
    connect(addButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(subButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(mulButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(divButton, &QPushButton::clicked, this, &Calculator::operationClicked);
    connect(equalButton, &QPushButton::clicked, this, &Calculator::equalClicked);
    connect(clearButton, &QPushButton::clicked, this, &Calculator::clearAll);
    connect(baseGroup, &QButtonGroup::idClicked, this, &Calculator::baseChanged);

    updateButtonStates();
}

Calculator::~Calculator() {}

// Логика нажатия на цифровую кнопку: просто добавляем символ к тексту
void Calculator::digitClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton) return;

    QString digitValue = clickedButton->text();
    if (display->text() == "0" || isWaitingForOperand) {
        display->clear();
        isWaitingForOperand = false;
    }
    display->setText(display->text() + digitValue);
}

// Запоминаем выбранную операцию и число
void Calculator::operationClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton) return;

    QString clickedOperator = clickedButton->text();
    bool ok;
    long long operand = display->text().toLongLong(&ok, currentNumBase);

    if (!ok) return;

    if (!pendingOperation.isEmpty()) {
        calculate(operand, pendingOperation);
        display->setText(QString::number(sumInMemory, currentNumBase).toUpper());
    } else {
        sumInMemory = operand;
    }

    pendingOperation = clickedOperator;
    isWaitingForOperand = true;
}

// Финальный расчет по нажатию на "="
void Calculator::equalClicked() {
    bool ok;
    long long operand = display->text().toLongLong(&ok, currentNumBase);
    if (!ok) return;

    if (!pendingOperation.isEmpty()) {
        calculate(operand, pendingOperation);
        pendingOperation = "";
    } else {
        sumInMemory = operand;
    }

    display->setText(QString::number(sumInMemory, currentNumBase).toUpper());
    isWaitingForOperand = true;
}

void Calculator::clearAll() {
    sumInMemory = 0;
    pendingOperation = "";
    display->setText("0");
    isWaitingForOperand = true;
}

// Пересчитываем число при смене системы счисления
void Calculator::baseChanged(int baseId) {
    bool ok;
    long long value = display->text().toLongLong(&ok, currentNumBase);
    currentNumBase = baseId;

    if (ok) {
        display->setText(QString::number(value, currentNumBase).toUpper());
    } else {
        display->setText("0");
    }
    updateButtonStates();
}

// Блокируем кнопки, которые не относятся к выбранной СС (например, '9' в BIN)
void Calculator::updateButtonStates() {
    for (int i = 0; i < 16; ++i) {
        digitButtons[i]->setEnabled(i < currentNumBase);
    }
}

// Непосредственно математика
void Calculator::calculate(long long rightOperand, const QString &pendingOperator) {
    if (pendingOperator == "+") sumInMemory += rightOperand;
    else if (pendingOperator == "-") sumInMemory -= rightOperand;
    else if (pendingOperator == "*") sumInMemory *= rightOperand;
    else if (pendingOperator == "/") {
        if (rightOperand != 0) sumInMemory /= rightOperand;
        else { clearAll(); display->setText("ERROR"); }
    }
}