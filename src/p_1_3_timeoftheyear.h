#ifndef P_1_3_TIMEOFTHEYEAR_H
#define P_1_3_TIMEOFTHEYEAR_H

#include <QWidget>

class QLabel;

class P_1_3_TimeOfTheYear : public QWidget
{
    Q_OBJECT
private:
    static const QStringList m_names;
    static const QStringList m_TOTY;

    QLabel  *lbl_current_month;
    QLabel  *lbl_current_TOTY;
public:
    explicit P_1_3_TimeOfTheYear(QWidget *parent = nullptr);
private slots:
    void slot_whatMonth(int);
    void slot_whatTimeOfTheYear(int);
};

#endif // P_1_3_TIMEOFTHEYEAR_H
