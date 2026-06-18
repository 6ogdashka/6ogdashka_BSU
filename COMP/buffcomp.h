#ifndef BUFFCOMP_H
#define BUFFCOMP_H

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <QString>
#include <QDebug>
#include <algorithm>

struct Comp {
    QString Name;
    QString Section;
    int Price;

    friend QTextStream& operator>>(QTextStream& in, Comp& obj) {
        QString line = in.readLine();
        if (line.isEmpty()) return in;

        QStringList fields = line.split(';');
        if (fields.size() >= 3) {
            obj.Name = fields[0].trimmed();
            obj.Section = fields[1].trimmed();
            obj.Price = fields[2].toInt();
        }
        return in;
    }

    friend QTextStream& operator<<(QTextStream& out, const Comp& obj) {
        out << obj.Name << ";" << obj.Section << ";" << obj.Price;
        return out;
    }

    bool operator==(const Comp& other) const {
        return this->Name.toLower() == other.Name.toLower();
    }

    void printRow() const {
        qDebug().noquote() << QString("| %1 | %2 | %3 |")
        .arg(Name, -20)
            .arg(Section, -15)
            .arg(QString::number(Price), 10);
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
    QString Name;
    int Num;
    QString Section;

    friend QTextStream& operator>>(QTextStream& in, Bag& obj) {
        QString line = in.readLine();
        if (line.isEmpty()) return in;

        QStringList fields = line.split(';');
        if (fields.size() >= 3) {
            obj.Name = fields[0].trimmed();
            obj.Num = fields[1].toInt();
            obj.Section = fields[2].trimmed();
        }
        return in;
    }

    friend QTextStream& operator<<(QTextStream& out, const Bag& obj) {
        out << obj.Name << ";" << obj.Num << ";" << obj.Section;
        return out;
    }

    bool operator==(const Bag& other) const {
        return this->Name.toLower() == other.Name.toLower();
    }

    void printRow() const {
        qDebug().noquote() << QString("| %1 | %2 | %3 |")
        .arg(Name, -20)
            .arg(QString::number(Num), 10)
            .arg(Section, -15);
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
    QString Table_Title;
    QVector<T> M;

public:
    COMP() = default;
    COMP(const QString& title) : Table_Title(title) {}

    int GetCount() const {
        return M.size();
    }

    friend QTextStream& operator>>(QTextStream& in, COMP<T>& obj) {
        obj.M.clear();
        if (in.atEnd()) return in;

        QString countLine = in.readLine();
        int expectedCount = countLine.toInt();

        for (int i = 0; i < expectedCount && !in.atEnd(); ++i) {
            T item;
            in >> item;
            obj.M.append(item);
        }
        return in;
    }

    friend QTextStream& operator<<(QTextStream& out, const COMP<T>& obj) {
        out << obj.M.size() << "\n";
        for (const auto& item : obj.M) {
            out << item << "\n";
        }

        qDebug().noquote() << "\n=== Таблица:" << obj.Table_Title << " ===";
        if (obj.M.isEmpty()) {
            qDebug() << "Массив пуст.";
            return out;
        }

        for (const auto& item : obj.M) {
            item.printRow();
        }
        qDebug().noquote() << "========================================";
        return out;
    }

    COMP<T> operator+(const COMP<T>& other) const {
        COMP<T> result("Объединенный массив");

        for (const auto& item : this->M) {
            if (!result.M.contains(item)) {
                result.M.append(item);
            }
        }
        for (const auto& item : other.M) {
            if (!result.M.contains(item)) {
                result.M.append(item);
            }
        }
        return result;
    }

    void sortAlphabetical() {
        std::sort(M.begin(), M.end(), [](const T& a, const T& b) {
            return a.Name.localeAwareCompare(b.Name) < 0;
        });
    }

    void sortReverseAlphabetical() {
        std::sort(M.begin(), M.end(), [](const T& a, const T& b) {
            return a.Name.localeAwareCompare(b.Name) > 0;
        });
    }

    void sortSectionAndReverseName() {
        std::sort(M.begin(), M.end(), [](const T& a, const T& b) {
            int secCmp = a.Section.localeAwareCompare(b.Section);
            if (secCmp != 0) {
                return secCmp < 0;
            }
            return a.Name.localeAwareCompare(b.Name) > 0;
        });
    }

    void searchByName(const QString& searchName) const {
        bool found = false;
        qDebug().noquote() << "\n[Поиск] Результаты по запросу:" << searchName;
        for (const auto& item : M) {
            if (item.Name.toLower() == searchName.toLower()) {
                item.printRow();
                found = true;
            }
        }
        if (!found) {
            qDebug() << "Сообщение: Такой товар отсутствует.";
        }
    }
};
#endif // BUFFCOMP_H
