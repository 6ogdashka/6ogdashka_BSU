
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

void MainWindow::on_pushButton_9_clicked()
{
    showInMessageBox(mainBag.M);
}

void MainWindow::on_pushButton_8_clicked()
{
    showInMessageBox(buffBag.M);
}

void MainWindow::on_pushButton_7_clicked()
{
    showInMessageBox(mainComp.M);
}

void MainWindow::on_pushButton_6_clicked()
{
    showInMessageBox(buffComp.M);
}

void MainWindow::on_pushButton_3_clicked()
{
    if (filetype == 1) {
        mainBag = mainBag + buffBag;
    } else {
        mainComp = mainComp + buffComp;
    }
}

void MainWindow::on_pushButton_10_clicked()
{
    if (filetype == 1) {
        mainBag.sortRevAlphabetical();
    } else {
        mainComp.sortRevAlphabetical();
    }
}

void MainWindow::on_pushButton_12_clicked()
{
    if (filetype == 2) {
        mainComp.sortReverseAlphabetical();
    } else {
        mainBag.sortReverseAlphabetical();
    }
}
void MainWindow::on_pushButton_11_clicked()
{
    QString searchName = ui->lineEdit_3->text();

    if (searchName.isEmpty()) {
        QMessageBox::warning(this, "ВНИМАНИЕ", "Введите имя для поиска");
        return;
    }

    if (filetype == 1) {
        QVector<Bag> found = mainBag.search(searchName);
        if (found.isEmpty()) {
            QMessageBox::information(this, "Результаты поиска", "Товар \"" + searchName + "\" не найден.");
        } else {
            showInMessageBox(found, "Результаты поиска");
        }
    } else {
        QVector<Comp> found = mainComp.search(searchName);
        if (found.isEmpty()) {
            QMessageBox::information(this, "Результаты поиска", "Товар \"" + searchName + "\" не найден.");
        } else {
            showInMessageBox(found, "Результаты поиска");
        }
    }
}

void MainWindow::on_pushButton_13_clicked()
{
    QString size;
    if ( filetype == 1) size = QString::number(mainBag.GetCount()); else size = QString::number(mainComp.GetCount());
    QMessageBox::information(this, "Размер выбранного массива",size);
}

