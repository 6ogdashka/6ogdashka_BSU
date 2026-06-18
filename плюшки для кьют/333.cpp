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