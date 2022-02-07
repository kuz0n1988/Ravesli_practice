#ifndef P_3_2_POSITIVEEVENINTSUM_H
#define P_3_2_POSITIVEEVENINTSUM_H

#include <QWidget>

class QLineEdit;

class P_3_2_PositiveEvenIntSum  : public QWidget
{
    Q_OBJECT
private:
    QLineEdit   *m_result;
public:
    P_3_2_PositiveEvenIntSum(QWidget *parent = nullptr);
private slots:
    void slotGetSum(int);
};

#endif // P_3_2_POSITIVEEVENINTSUM_H
