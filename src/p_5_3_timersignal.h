#ifndef P_5_3_TIMERSIGNAL_H
#define P_5_3_TIMERSIGNAL_H

#include <QWidget>
#include <QTimer>

class P_5_3_TimerSignal : public QWidget
{
    Q_OBJECT
private:
    QTimer *m_tmr;
public:
    explicit P_5_3_TimerSignal(QWidget *parent = nullptr);
    ~P_5_3_TimerSignal()
    {
        if(m_tmr)
            delete  m_tmr;
    }

public slots:
    void slotChangeInterval(int);
    void slotImperialMarch();
};

#endif // P_5_3_TIMERSIGNAL_H
