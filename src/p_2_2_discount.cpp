#include "p_2_2_discount.h"

#include <QLabel>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QStringList>
#include <QGridLayout>

//#include "makinghtmllink.h"

const QStringList P_2_2_Discount::m_labels =
        { "Суммы покупки недостаточно для предоставления скидки",   // 0
          "Вам предоставляется скидка в %1\%",                      // 1
          "Сумма с учётом скидки: %1 руб."};                        // 2

P_2_2_Discount::P_2_2_Discount(QWidget *parent) : QWidget(parent)
{
    QLabel          *lbl_enter_sum      = new QLabel("Введите сумму покупки:", this);
    QDoubleSpinBox  *spb_enter_sum      = new QDoubleSpinBox(this);
                     spb_enter_sum->setRange(0.0, std::numeric_limits<double>::max());
                     spb_enter_sum->setValue(640);
                     spb_enter_sum->setSuffix(" p.");
    connect(spb_enter_sum, SIGNAL(valueChanged(double)), SLOT(slotCalculateDiscount(double)));

                     m_discount         = new QLabel(this);
                     m_discount_result  = new QLineEdit(this);
                     m_discount_result->setReadOnly(true);

    QGridLayout     *layout_main        = new QGridLayout(this);
                     layout_main->addWidget(lbl_enter_sum,      0, 0);
                     layout_main->addWidget(spb_enter_sum,      0, 1);
                     layout_main->addWidget(m_discount,         1, 0, 1, 2, Qt::AlignTop);
                     layout_main->addWidget(m_discount_result,  2, 0, 1, 2, Qt::AlignTop);

    slotCalculateDiscount(spb_enter_sum->value());
}

void P_2_2_Discount::slotCalculateDiscount(const double& sum)
{
    double discount = 0.0;

    if(sum > 1000.0)
        discount = 0.05;
    else if(sum > 500.0)
        discount = 0.03;
    else
        m_discount->setText(m_labels[0]);

    if(discount > 0.0)
        m_discount->setText(m_labels[1].arg(QString::number(discount*100, 'f', 0)));
    // раньше две такие строчки были в первом блоке if-else
    // но меня так раздражает дублирующийся код, что я вынес её в отдельное условие
    // Да, я знаю, что лишнее условие это вредно для производительности кода

    m_discount_result->setText(m_labels[2].
            arg(QString::number(sum * (1.0-discount), 'f', 2)));
}
