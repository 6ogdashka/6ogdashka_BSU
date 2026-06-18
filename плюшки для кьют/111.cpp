#ifndef COMP_H
#define COMP_H

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QString>
#include <QDebug>
#include <QMessageBox>

template <typename Container>
void showInMessageBox(const Container& container, const QString& title = "Содержимое") {

    QString buffer;
    QTextStream stream(&buffer);

    for (int i = 0; i < container.size(); ++i) {
        stream << container[i] << "\n";
    }
    stream.flush();

    if (buffer.isEmpty()) {
        buffer = "Список пуст";
    }

    QMessageBox::information(nullptr, title, buffer);
}

struct Comp {
    QString Name, Section;
    int Price;

    bool operator==(const Comp& o) const { return Name == o.Name; }

    friend QTextStream& operator>>(QTextStream& in, Comp& c) {
        QStringList s = in.readLine().split(';');
        if(s.size() >= 3) { c.Name = s[0]; c.Section = s[1]; c.Price = s[2].toInt(); }
        return in;
    }
    friend QTextStream& operator<<(QTextStream& out, const Comp& c) {
        return out << c.Name << " " << c.Section << " " << c.Price;
    }

    static QVector<Comp> readText(const QString& filename) {
        QVector<Comp> result;
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                Comp comp;
                in >> comp;
                if (!comp.Name.isEmpty()) {
                    result.append(comp);
                }
            }
            file.close();
        }
        return result;
    }


};

struct Bag {
    QString Name, Section;
    int Num;

    bool operator==(const Bag& o) const { return Name == o.Name; }

    friend QTextStream& operator>>(QTextStream& in, Bag& b) {
        QStringList s = in.readLine().split(';');
        if(s.size() >= 3) { b.Name = s[0]; b.Num = s[1].toInt(); b.Section = s[2]; }
        return in;
    }
    friend QTextStream& operator<<(QTextStream& out, const Bag& b) {
        return out << b.Name << " " << b.Num << " " << b.Section;
    }

    static QVector<Bag> readText(const QString& filename) {
        QVector<Bag> result;
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                Bag bag;
                in >> bag;
                if (!bag.Name.isEmpty()) {
                    result.append(bag);
                }
            }
            file.close();
        }
        return result;
    }
};

template <class T>
class COMP {
public:
    QString title = "Каталог";
    QVector<T> M;

    ~COMP() = default;

    COMP() {}

    COMP(const QString& title_, const QVector<T> other) : title(title_), M(other) {}

    COMP(const COMP& other) = default;

    COMP& operator=(const COMP& other) = default;

    COMP(COMP&& other) noexcept {
        this->M= std::move(other.M);
    }

    COMP& operator=(QVector<T> other) {
        M = other;
        return this;
    }

    COMP& operator=(COMP&& other) noexcept {
        if (this != &other) {
            this->M = std::move(other.M);
        }
        return *this;
    }

    friend QTextStream& operator>>(QTextStream& in, COMP<T>& obj) {
        int count = in.readLine().toInt();
        for(int i = 0; i < count && !in.atEnd(); ++i) {
            T item;
            in >> item;
            obj.M.append(item);
        }
        return in;
    }
    friend QTextStream& operator<<(QTextStream& out, const COMP<T>& obj) {
        out << obj.M.size() << "\n";
        qDebug() << "\n---" << obj.title << "---";
        for(const auto& item : obj.M) {
            out << item << "\n";
            qDebug() << item.Name << "| Секция:" << item.Section;
        }
        return out;
    }

    COMP<T> operator+(const COMP<T>& other) const {
        COMP<T> res("Объединенный массив");
        for(const auto& item : M)       if(!res.M.contains(item)) res.M.append(item);
        for(const auto& item : other.M) if(!res.M.contains(item)) res.M.append(item);
        return res;
    }

    void sortRevAlphabetical() {
        std::sort(M.begin(), M.end(), [](const T& a, const T& b) { return a.Name > b.Name; });
    }

    void sortReverseAlphabetical() {
        std::sort(M.begin(), M.end(), [](const T& a, const T& b) { return a.Name < b.Name; });
    }

    void search(const QString& name) const {
        bool found = false;
        for(const auto& item : M) {
            if(item.Name == name) {
                qDebug() << "Найдено:" << item.Name << item.Section;
                found = true;
            }
        }
        if(!found) qDebug() << "Товар" << name << "не найден.";
    }

    size_t GetCount() {
        return M.size();
    }
};

#endif // COMP_H
