#include "p_1_3_timeoftheyear.h"
//#include "makinghtmllink.h"

//#include <QtWidgets>

#include <QLabel>
#include <QStringList>
#include <QSpinBox>
#include <QString>
#include <QVBoxLayout>

#include <QDebug>

const QStringList P_1_3_TimeOfTheYear::m_names = {
    "Такого месяца не существует",          // 0
    "Январь",                               // 1
    "Февраль",                              // 2
    "Март",                                 // 3
    "Апрель",                               // 4
    "Май",                                  // 5
    "Июнь",                                 // 6
    "Июль",                                 // 7
    "Август",                               // 8
    "Сентябрь",                             // 9
    "Октябрь",                              // 10
    "Ноябрь",                               // 11
    "Декабрь"};                             // 12

const QStringList P_1_3_TimeOfTheYear::m_TOTY = {
    "Времени года не существует",           // 0
    "Зима",                                 // 1
    "Весна",                                // 2
    "Лето",                                 // 3
    "Осень"                                 // 4
};

P_1_3_TimeOfTheYear::P_1_3_TimeOfTheYear(QWidget *parent) : QWidget(parent)
{
    QLabel   *lbl_title         = new QLabel    ("Введите номер месяца", this);
    QSpinBox *spb_number        = new QSpinBox  (this);
    // По-приколу сделаем доступный диапазон от -20 до 20, чтобы был повод выкинуть ошибку
    spb_number->setRange(-20, 20);
              lbl_current_month = new QLabel    ("Тут будет отображаться название месяца",  this);
              lbl_current_TOTY  = new QLabel    ("Тут будет отображаться время года",       this);
    spb_number->setValue(0);
    connect(spb_number, SIGNAL(valueChanged(int)), SLOT(slot_whatMonth(int)));
    connect(spb_number, SIGNAL(valueChanged(int)), SLOT(slot_whatTimeOfTheYear(int)));

    QVBoxLayout *layout_main = new QVBoxLayout(this);
    layout_main->addWidget(lbl_title);
    layout_main->addWidget(spb_number);
    layout_main->addWidget(lbl_current_month);
    layout_main->addWidget(lbl_current_TOTY, 5, Qt::AlignTop);
//    layout_main->addWidget(lbl_html_page, 0, Qt::AlignBottom);
//    layout_main->addWidget(MakingHtmlLink::getMyHtmlLabel(this), 0, Qt::AlignBottom);
}

void P_1_3_TimeOfTheYear::slot_whatMonth(int number)
{
    QString str = "Месяц: %1";
    if (number < 1 || number > 12)
        lbl_current_month->setText(m_names[0]);
    else
        lbl_current_month->setText(str.arg(m_names[number]));
}

void P_1_3_TimeOfTheYear::slot_whatTimeOfTheYear(int number)
{
    QString str = "Время года: %1";
    switch (number)
    {   // Зима
    case 12:
    case 1:
    case 2:
        lbl_current_TOTY->setText(str.arg(m_TOTY[1]));
        qDebug() << "Recieved number: " << number
                 << "Compared text:   " << m_TOTY[1];
        break;
    case 3: // Весна
    case 4:
    case 5:
        lbl_current_TOTY->setText(str.arg(m_TOTY[2]));
        qDebug() << "Recieved number: " << number
                 << "Compared text:   " << m_TOTY[2];
        break;
    case 6: // Лето
    case 7:
    case 8:
        lbl_current_TOTY->setText(str.arg(m_TOTY[3]));
        qDebug() << "Recieved number: " << number
                 << "Compared text:   " << m_TOTY[3];
        break;
    case 9: // Осень
    case 10:
    case 11:
        lbl_current_TOTY->setText(str.arg(m_TOTY[4]));
        qDebug() << "Recieved number: " << number
                 << "Compared text:   " << m_TOTY[4];
        break;
    default:    // Специальный раздел для инопланетных пришельцев,
                // которые не знают, что на Земле всего 12 месяцев
        lbl_current_TOTY -> setText(m_TOTY[0]);
        qDebug() << "Recieved number: " << number
                 << "Compared text:   " << m_TOTY[0];

    }
}
