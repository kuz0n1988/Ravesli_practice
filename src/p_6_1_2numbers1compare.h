#ifndef P_6_1_2NUMBERS1COMPARE_H
#define P_6_1_2NUMBERS1COMPARE_H

#include <QWidget>

class QSlider;
class QLabel;

class P_6_1_2Numbers1Compare : public QWidget
{
    Q_OBJECT
private:
    /* Поскольку задание очень простое, то я решил (поизвращаться)
     * поэксперементировать с QSlider для ввода числовых значений
     * */
    QSlider *m_sld_first;
    QSlider *m_sld_second;
    QLabel  *m_lbl_compare;
public:
    explicit P_6_1_2Numbers1Compare(QWidget *parent = nullptr);

private slots:
    void slotCompare();
};

#endif // P_6_1_2NUMBERS1COMPARE_H
