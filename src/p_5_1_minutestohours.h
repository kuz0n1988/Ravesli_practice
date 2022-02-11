#ifndef P_5_1_MINUTESTOHOURS_H
#define P_5_1_MINUTESTOHOURS_H

#include <QObject>
#include <QWidget>

#include <string>

/* Буду для этого задания делать собственный класс
 * для хранения значений времени
 * Изначально хотел использовать ctime и тип time_t
 * но там идёт привязка к 1-му января 70-го года
 * (зачем это мне) и документация очень скудная.
 * Плюс, хочу основной виджет объявить без членов
 * класса, а работу завязать на слот-сигналы.
 * Для этого делаю класс MyTime дочерним QObject
 *
 * И да, я знаю, что реализовывать два разных класса в
 * одном файле - это  моветон.
 */
class MyTime : public QObject
{
    Q_OBJECT
private:
    unsigned int m_minutes;

    void checkInputParameter(const int& m)
    {
        if(m < 0)
            throw "The value of the \"minutes\" parameter cannot be negative";
    }
public:
    /* В конструкторе и сеттере я использую обычный
     * int вместо unsigned, потому что именно он
     * используется в качестве value в QSpinBox
     * */
    MyTime(const int& min = 150) : m_minutes(min)
    { checkInputParameter(min); }

    void setMinutes(const int& min)
    {
        checkInputParameter(min);
        m_minutes = min;
    }

    std::wstring getHoursAndMinutes()
    {
        return std::to_wstring(m_minutes/60) + L" ч. " +
               std::to_wstring(m_minutes%60) + L" мин.";
    }

public slots:
    void slotChangeMinutes(const int &min)
    {
        setMinutes(min);
        emit signalChangeMinutes(QString::fromStdWString(getHoursAndMinutes()));
    }
signals:
    void signalChangeMinutes(const QString &hours_and_minutes);
};

class P_5_1_MinutesToHours : public QWidget
{
    Q_OBJECT
public:
    explicit P_5_1_MinutesToHours(QWidget *parent = nullptr);
};

#endif // P_5_1_MINUTESTOHOURS_H
