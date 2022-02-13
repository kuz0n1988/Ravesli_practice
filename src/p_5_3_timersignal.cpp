#include "p_5_3_timersignal.h"

#include <QLCDNumber>
#include <QDial>
#include <QTimer>
#include <QVBoxLayout>

#include <windows.h>

P_5_3_TimerSignal::P_5_3_TimerSignal(QWidget *parent) : QWidget(parent)
{
    QLCDNumber  *lcd_display    =   new QLCDNumber(2, this);

    QDial       *dia_input      = new QDial(this);
                 dia_input->setRange(0, 60);
                 dia_input->setNotchesVisible(true);
                 dia_input->setNotchTarget(5);

    QVBoxLayout *layout_main    = new QVBoxLayout(this);
                 layout_main->addWidget(lcd_display);
                 layout_main->addWidget(dia_input);

                 m_tmr          = new QTimer();

    connect(dia_input,      SIGNAL(sliderMoved(int)),
            lcd_display,    SLOT(display(int)));
    // &QTimer::setInterval - не слот :( а так хотелось бы!
    connect(dia_input,      SIGNAL(sliderMoved(int)),
            this,           SLOT(slotChangeInterval(int)));
    connect(dia_input,      SIGNAL(sliderReleased()),
            m_tmr,         SLOT(start()));
    connect(m_tmr, SIGNAL(timeout()), this, SLOT(slotImperialMarch()));
}

void P_5_3_TimerSignal::slotChangeInterval(int seconds)
{
    m_tmr->setInterval(seconds * 1000);
}

void P_5_3_TimerSignal::slotImperialMarch()
{
    int a = 500;

    Beep(392, a);
    Beep(392, a);
    Beep(392, a);
    Beep(311, a*0.75);
    Beep(466, a*0.25);

    Beep(392, a);
    Beep(311, a*0.75);
    Beep(466, a*0.25);
    Beep(392, a*2);

    Beep(587, a);
    Beep(587, a);
    Beep(587, a);
    Beep(622, a*0.75);
    Beep(466, a*0.25);

    Beep(369, a);
    Beep(311, a*0.75);
    Beep(466, a*0.25);
    Beep(392, a*2);

    m_tmr->stop();
}
