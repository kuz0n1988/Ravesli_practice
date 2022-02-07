#include "p_4_1_versta.h"

#include <QLabel>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QGridLayout>

P_4_1_versta::P_4_1_versta(QWidget *parent) : QWidget(parent)
{
    setObjectName("41");

    QLabel          *lbl_distance_km    = new QLabel("Введите расстояние в километрах:", this);
    QDoubleSpinBox  *spd_distance_km    = new QDoubleSpinBox(this);
                     spd_distance_km->setRange(0, std::numeric_limits<double>::max());
                     spd_distance_km->setSuffix(" км.");
                     spd_distance_km->setValue(100.0);

    QLabel          *lbl_distance_v     = new QLabel("Расстояние в верстах:", this);
                     m_result           = new QLineEdit(this);
                     m_result->setReadOnly(true);
    connect(spd_distance_km,    SIGNAL(valueChanged(double)),
            this,               SLOT(slotShowVerst(double)));

    QGridLayout     *layout_main        = new QGridLayout(this);
    layout_main->addWidget(lbl_distance_km, 0, 0);
    layout_main->addWidget(spd_distance_km, 0, 1);
    layout_main->addWidget(lbl_distance_v,  1, 0);
    layout_main->addWidget(m_result,        1, 1);

    slotShowVerst(spd_distance_km->value());
}

double  P_4_1_versta::getDistanceInVerst(const double &dist)
{
    return dist * 1.0668;
}

void    P_4_1_versta::slotShowVerst(const double &dist)
{
    m_result->setText(QString::number(getDistanceInVerst(dist), 'f', 2) + " вёрст");
}
