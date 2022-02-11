#include "p_5_2_pricetable.h"

#include <QLabel>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

P_5_2_PriceTable::P_5_2_PriceTable(QWidget *parent) : QWidget(parent)
{
    QLabel          *lbl_price  = new QLabel("Введите цену за 1 кг яблок: ", this);
    QDoubleSpinBox  *spd_price  = new QDoubleSpinBox(this);
                     spd_price->setRange(0.0, std::numeric_limits<double>::max());
                     spd_price->setSuffix(" руб.");
                     spd_price->setDecimals(2);
    QGroupBox       *gbx_result = new QGroupBox("Результаты расчётов:", this);

    // Поскольку модель-представление в qt я только начал изучать и работать с ним
    // пока не умею, буду изобретать велосипед через QGridLayout и QLabel
                     m_layout_result  = new QGridLayout();
                     m_layout_result->addWidget(new QLabel("Вес, г.",         this), 0, 0, Qt::AlignCenter);
                     m_layout_result->addWidget(new QLabel("Стоимость, руб.", this), 0, 1, Qt::AlignCenter);

    for(int i = 1; i < 11; i++) // Делаем 10*2 надписей
    {
        m_layout_result->addWidget(new QLabel(QString::number(i*100), this), i, 0, Qt::AlignCenter);
        m_layout_result->addWidget(new QLabel(this),                         i, 1, Qt::AlignCenter);
    }
    gbx_result->setLayout(m_layout_result);

    connect(spd_price, SIGNAL(valueChanged(double)), SLOT(slotChangeTable(double)));
    spd_price->setValue(16.5);

    QHBoxLayout *layout_top     = new QHBoxLayout();
                 layout_top->addWidget(lbl_price, 0);
                 layout_top->addWidget(spd_price, 1, Qt::AlignLeft);

    QVBoxLayout *layout_main    = new QVBoxLayout(this);
                 layout_main->addLayout(layout_top);
                 layout_main->addWidget(gbx_result, 5, Qt::AlignTop);
}

void P_5_2_PriceTable::slotChangeTable(const double& price)
{
    QLabel *lbl_tmp;

    for(int i = 1; i < 11; i++)
    {
        lbl_tmp = (QLabel*)(m_layout_result->itemAtPosition(i, 1)->widget());
        lbl_tmp->setText(QString::number(((price * i ) / 10), 'f', 2));
    }
}
