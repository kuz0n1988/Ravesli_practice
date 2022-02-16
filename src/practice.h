#ifndef PRACTICE_H
#define PRACTICE_H

#include <QWidget>

class QStackedWidget;
class QComboBox;

class Practice : public QWidget
{
    Q_OBJECT

private:
// ========== КОНСТАНТЫ ===========
    const int MAX_PARTS = 24;   // - количество частей на ravesli.com
    const int MAX_TASKS = 3;    // - количество задач в каждой части

// ========== ПЕРЕМЕННЫЕ ==========
    QStackedWidget      *m_main_widget;
    QComboBox           *m_cmb_select_part;
    QComboBox           *m_cmb_select_task;

public:
// ========== КОНСТРУКТОРЫ ========
    Practice(QWidget *parent = nullptr);
    ~Practice();

private:
// ========== МЕТОДЫ ==============
    void initialize();
    int makeKey();

private slots:
// ========== СЛОТЫ ===============
    void slot_changeWidget();
};
#endif // PRACTICE_H
