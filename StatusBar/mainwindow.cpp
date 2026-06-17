#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Устанавливаем размер окна
    setFixedSize(300, 200);

    // Создаем кнопку, которая будет инициировать сообщение
    btn = new QPushButton("Нажми меня", this);
    btn->setGeometry(100, 80, 100, 40);

    // Связываем сигнал клика по кнопке со слотом showStatusMessage
    connect(btn, &QPushButton::clicked, this, &MainWindow::showStatusMessage);

    // Инициализируем строку состояния, которая есть у QMainWindow по умолчанию
    statusBar()->showMessage("Готов к работе");
}

MainWindow::~MainWindow() {}

void MainWindow::showStatusMessage() {
    // Выводим сообщение в статус-бар на 3000 миллисекунд (3 секунды)
    statusBar()->showMessage("Кнопка была нажата!", 3000);
}