#ifndef P_2_1_DACHA_H
#define P_2_1_DACHA_H

#include <QWidget>

//class QSpinBox;
class QDoubleSpinBox;
class QLineEdit;

class P_2_1_dacha : public QWidget
{
    Q_OBJECT
private:
    QDoubleSpinBox      *m_distance;    // Расстояние до дачи
    QDoubleSpinBox      *m_fuel_consum; // Расход на сотку
    QDoubleSpinBox      *m_fuel_price;  // Поле ввода цены за литр топлива
    QLineEdit           *m_result;      // Сюда засунем результаты вычислений

public:
    explicit P_2_1_dacha(QWidget *parent = nullptr);
private slots:
    void slotShowTravelCost();
};

#endif // P_2_1_DACHA_H
