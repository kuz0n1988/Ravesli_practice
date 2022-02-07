#ifndef P_3_1_SPEEDRUNNER_H
#define P_3_1_SPEEDRUNNER_H

#include <QWidget>

class QSpinBox;
class QTimeEdit;
class QLineEdit;

class P_3_1_SpeedRunner : public QWidget
{
    Q_OBJECT
private:
    QSpinBox    *m_distance;
    QTimeEdit   *m_time;
    QLineEdit   *m_result;

public:
    explicit P_3_1_SpeedRunner(QWidget *parent = nullptr);

private slots:
    void slotCalculateSpeedRunner();
};

#endif // P_3_1_SPEEDRUNNER_H
