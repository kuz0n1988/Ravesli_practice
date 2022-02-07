#include "p_2_1_dacha.h"

#include <QLabel>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QGridLayout>

#include <QDebug>

#include "makinghtmllink.h"

P_2_1_dacha::P_2_1_dacha(QWidget *parent) : QWidget(parent)
{
    setObjectName("21");

    QLabel  *lbl_distance       = new QLabel("Расстояние до дачи в один конец (км):", this);
             m_distance         = new QDoubleSpinBox(this);
             m_distance->setValue(67);
             m_distance->setSuffix(" км.");
             m_distance->setRange(0, 500.0);    // Сомневаюсь, что есть настолько упоротые,
                                                // которые будут ездить на дачу за 500 км

    QLabel  *lbl_fuel_consum    = new QLabel("Расход топлива (литров на 100 км пробега):", this);
             m_fuel_consum      = new QDoubleSpinBox(this);
             m_fuel_consum->setValue(8.5);
             m_fuel_consum->setSuffix(" л/100км");
             m_fuel_consum->setRange(0, 40.0);  // Сомневаюсь, что кто-то будет ездить на дачу
                                                // используя танк. А вот электромобиль - могут!

    QLabel  *lbl_fuelPrice      = new QLabel("Цена литра топлива (руб.):");
             m_fuel_price       = new QDoubleSpinBox(this);
             m_fuel_price->setValue(50.0);
             m_fuel_price->setSuffix(" руб.");
             m_fuel_price->setRange(0, std::numeric_limits<double>::max());
                                                // Сомневаюсь, что коммунизм когда-нибудь наступит
                                                // и топливо станет бесплатным. Скорее ёмкости
                                                // переменной типа double однажды может не хватить

            m_result            = new QLineEdit(this);
            m_result->setReadOnly(true);

    connect(m_distance,     SIGNAL(valueChanged(double)), SLOT(slotShowTravelCost()));
    connect(m_fuel_consum,  SIGNAL(valueChanged(double)), SLOT(slotShowTravelCost()));
    connect(m_fuel_price,   SIGNAL(valueChanged(double)), SLOT(slotShowTravelCost()));

    QGridLayout *layout_main    = new QGridLayout(this)             ;
                 layout_main->addWidget(lbl_distance,       0, 0);
                 layout_main->addWidget(m_distance,         0, 1);
                 layout_main->addWidget(lbl_fuel_consum,    1, 0);
                 layout_main->addWidget(m_fuel_consum,      1, 1);
                 layout_main->addWidget(lbl_fuelPrice,      2, 0);
                 layout_main->addWidget(m_fuel_price,       2, 1);
                 layout_main->addWidget(m_result,           3, 0, 1, 2, Qt::AlignTop);
                 layout_main->addWidget(MakingHtmlLink::getMyHtmlLabel(this), 4, 0, 1, 2, Qt::AlignBottom);

    slotShowTravelCost();
}

void P_2_1_dacha::slotShowTravelCost()
{
    QString pattern = "Поездка на дачу обойдётся в %1 руб.";

    // Для простоты понимания, сначала считаем, сколько топлива мы потратим
    double temp = m_fuel_consum->value()
                * m_distance->value()
                / 100;

    // Потом умножаем на рубли и присваиваем m_result
    temp = temp * m_fuel_price->value();
    m_result->setText(pattern.arg(QString::number(temp, 'f', 2)));

    /* ====================ПРИМЕЧАНИЕ====================
     * Изначально я умножал итоговую цифру на два, т.к.
     * было задано вычислить стоимость поездки на авто на
     * дачу ТУДА И ОБРАТНО, а вводные данные включали в
     * себя только расстояние до дачи (но не обратно)
     * Однако, в приведённом на той же странице примере
     * этот ньюанс не учитывался, и я переделал как в примере
     * */
}
