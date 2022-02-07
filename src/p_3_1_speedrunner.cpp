#include "p_3_1_speedrunner.h"


#include <QLabel>
#include <QSpinBox>
#include <QDateTime>
#include <QTimeEdit>
#include <QLineEdit>
#include <QGridLayout>

#include <QDebug>

P_3_1_SpeedRunner::P_3_1_SpeedRunner(QWidget *parent) : QWidget(parent)
{
    setObjectName("31");

    QLabel          *distance_title = new QLabel("Введите дистанцию (метров): ", this);
    /*QSpinBox*/     m_distance     = new QSpinBox(this);
                     m_distance->setRange   (0, 50000);
                     m_distance->setSuffix  (" м.");
                     m_distance->setValue   (1000);

    QLabel          *time_title     = new QLabel    ("Введите время (минут:секунд): ", this);
    /*QTimeEdit*/    m_time         = new QTimeEdit (QTime(0, 3, 25), this);
                     m_time->setDisplayFormat("mm:ss");

    QLabel          *result_title   = new QLabel    ("Ваша скорость: ");
    /*QLineEdit*/    m_result       = new QLineEdit (this);
                     m_result->setReadOnly(true);

    connect(m_distance, SIGNAL(valueChanged(int)),
            this,       SLOT(slotCalculateSpeedRunner()));

    connect(m_time,     SIGNAL(timeChanged(QTime)),
            this,       SLOT(slotCalculateSpeedRunner()));

    QGridLayout     *layout_main    = new QGridLayout(this);
    layout_main->addWidget(distance_title,  0, 0);
    layout_main->addWidget(m_distance,      0, 1);
    layout_main->addWidget(time_title,      1, 0);
    layout_main->addWidget(m_time,          1, 1);
    layout_main->addWidget(result_title,    2, 0);
    layout_main->addWidget(m_result,        2, 1);

    slotCalculateSpeedRunner();
}

void P_3_1_SpeedRunner::slotCalculateSpeedRunner()
{
    int distance_m      = m_distance->value();

    // Вытаскиваем QTime из QTimeEdit
    QTime   time        = m_time->time();

    // Переводим значения из QTime в секунды
    double  second      = time.hour() * 3600 +
                          time.minute() * 60 +
                          time.second();

    // Разделив количество метров на количество секунд
    // получаем скорость в м/с
    // км/ч = 3.6 * м/с
    m_result->setText
            (QString::number
             (static_cast<double>(distance_m/second) * 3.6, 'f', 2) + " км/ч.");
}
