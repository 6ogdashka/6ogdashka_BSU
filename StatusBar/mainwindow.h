#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStatusBar>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showStatusMessage(); // Слот для вывода сообщения в строку состояния

private:
    QPushButton *btn;         // Кнопка для запуска действия
};

#endif