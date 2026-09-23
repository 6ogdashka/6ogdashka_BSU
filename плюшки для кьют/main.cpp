#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->label_2->setText("Текущий тип массива - Bag ");
    filetype = 1;
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->label_2->setText("Текущий тип массива - Comp ");
    filetype = 2;
}

// Чтение основного файла
void MainWindow::on_pushButton_clicked()
{
    if(filetype == 0) {
        QMessageBox::warning(this,"ВНИМАНИЕ","Не выбран тип массива");
    } else {
        QString filename = ui->lineEdit->text();
        switch(filetype) {
        case 1: { mainBag = Bag::readText(filename); ui->lineEdit->clear(); break; }
        case 2: { mainComp = Comp::readText(filename); ui->lineEdit->clear(); break; }
        }
    }
}

// Чтение буферного файла
void MainWindow::on_pushButton_2_clicked()
{
    if(filetype == 0) {
        QMessageBox::warning(this,"ВНИМАНИЕ","Не выбран тип массива");
    } else {
        QString filename = ui->lineEdit_2->text();
        switch(filetype) {
        case 1: { buffBag = Bag::readText(filename); ui->lineEdit_2->clear(); break; }
        case 2: { buffComp = Comp::readText(filename); ui->lineEdit_2->clear(); break; }
        }
    }
}

// Отображение списков (передаем внутренний вектор .M, так как функция ждет контейнер с .size() и [])
void MainWindow::on_pushButton_9_clicked()  { showInMessageBox(mainBag.M); }
void MainWindow::on_pushButton_8_clicked()  { showInMessageBox(buffBag.M); }
void MainWindow::on_pushButton_7_clicked()  { showInMessageBox(mainComp.M); }
void MainWindow::on_pushButton_6_clicked()  { showInMessageBox(buffComp.M); }

// Объединение массивов с помощью оператора + класса COMP
void MainWindow::on_pushButton_3_clicked()
{
    if (filetype == 1) {
        mainBag = mainBag + buffBag;
    } else {
        mainComp = mainComp + buffComp;
    }
}

// Сортировка по убыванию (Z-A)
void MainWindow::on_pushButton_10_clicked()
{
    if (filetype == 1) {
        mainBag.sortRevAlphabetical();
    } else {
        mainComp.sortRevAlphabetical();
    }
}

// Сортировка по возрастанию (A-Z)
void MainWindow::on_pushButton_12_clicked()
{
    if (filetype == 2) {
        mainComp.sortReverseAlphabetical();
    } else {
        mainBag.sortReverseAlphabetical();
    }
}