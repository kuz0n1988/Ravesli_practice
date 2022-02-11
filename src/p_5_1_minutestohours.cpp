#include "p_5_1_minutestohours.h"

#include <QLabel>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>



P_5_1_MinutesToHours::P_5_1_MinutesToHours(QWidget *parent) : QWidget(parent)
{
    QLabel      *lbl_top    = new QLabel("Введите временной интервал в (минутах):", this);
    QSpinBox    *spb_min    = new QSpinBox(this);
                 spb_min->setRange(0, 1440);
                 spb_min->setSuffix(" мин.");
    QLabel      *lbl_reslt1 = new QLabel("150 мин.", this);
    QLabel      *lbl_reslt2 = new QLabel(" = ");
    QLabel      *lbl_reslt3 = new QLabel("2 ч. 30 мин.");
    MyTime      *time = new MyTime();

    connect(spb_min,    SIGNAL(valueChanged(QString)),          lbl_reslt1, SLOT(setText(QString)));
    connect(spb_min,    SIGNAL(valueChanged(int)),              time,       SLOT(slotChangeMinutes(int)));
    connect(time,       SIGNAL(signalChangeMinutes(QString)),   lbl_reslt3, SLOT(setText(QString)));

    spb_min->setValue(150); // вместо инициализации

    QHBoxLayout *layout_results = new QHBoxLayout();
                 layout_results->addWidget(lbl_reslt1);
                 layout_results->addWidget(lbl_reslt2);
                 layout_results->addWidget(lbl_reslt3, 1, Qt::AlignLeft);
                 layout_results->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    QVBoxLayout *layout_main    = new QVBoxLayout(this);
                 layout_main->addWidget(lbl_top);
                 layout_main->addWidget(spb_min);
                 layout_main->addLayout(layout_results, 1);
}
