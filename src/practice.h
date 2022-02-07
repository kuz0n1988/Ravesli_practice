#ifndef PRACTICE_H
#define PRACTICE_H

#include <QWidget>
#include <QMap>

class QStackedWidget;
class QLabel;

class Practice : public QWidget
{
    Q_OBJECT

private:
// ========== КОНСТАНТЫ ===========
    const int MAX_PARTS = 24;   // - количество частей на ravesli.com
    const int MAX_TASKS = 3;    // - количество задач в каждой части

// ========== ПЕРЕМЕННЫЕ ==========
    QMap<int, int>       m_index_of_widgets;
    QStackedWidget      *m_main_widget;
    int                  m_part = 1;
    int                  m_task = 1;

public:
// ========== КОНСТРУКТОРЫ ========
    Practice(QWidget *parent = nullptr);
    ~Practice();

private:
// ========== МЕТОДЫ ==============
    void initializeMap();
    int makeKey();
    int makeKey(int part, int task);

private slots:
// ========== СЛОТЫ ===============
    void slot_changeWidget();
    void slot_changePart(int);
    void slot_changeTask(int);
};
#endif // PRACTICE_H
