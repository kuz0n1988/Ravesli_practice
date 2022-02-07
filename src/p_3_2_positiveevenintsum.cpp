#include "p_3_2_positiveevenintsum.h"

#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QVBoxLayout>

P_3_2_PositiveEvenIntSum::P_3_2_PositiveEvenIntSum(QWidget *parent) : QWidget(parent)
{
    setObjectName("32");

    QLabel          *lbl_enter_number   = new QLabel
                     ("Введите количество положительных\n"
                      "целых чётных чисел, которое\n"
                      "необходимо просуммировать:", this);
    QSpinBox        *spb_enter_number   = new QSpinBox(this);
                     spb_enter_number->setValue(12);
                     spb_enter_number->setRange(1, 1000);

    QLabel          *lbl_result         = new QLabel("Результат:", this);
    /*QLineEdit*/    m_result           = new QLineEdit(this);
                     m_result->setReadOnly(true);

    connect(spb_enter_number,   SIGNAL(valueChanged(int)),
            this,               SLOT(slotGetSum(int)));

    QVBoxLayout     *layout_main        = new QVBoxLayout(this);
                     layout_main->addWidget(lbl_enter_number);
                     layout_main->addWidget(spb_enter_number);
                     layout_main->addWidget(lbl_result);
                     layout_main->addWidget(m_result, 1, Qt::AlignTop);

    slotGetSum(spb_enter_number->value());
}

void P_3_2_PositiveEvenIntSum::slotGetSum(int number)
{
    int sum = 0;

    for(int i = 1; i <= number; i++)
        sum += i * 2;

    m_result->setText(QString::number(sum));
}
