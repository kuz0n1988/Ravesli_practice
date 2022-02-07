#ifndef P_1_2_MINNUMBER_H
#define P_1_2_MINNUMBER_H

#include <QWidget>
#include <vector>

class QPushButton;
class QLabel;
class QSpinBox;

class P_1_2_MinNumber : public QWidget
{
    Q_OBJECT
private:
    // константы, чтобы не юзать магические числа
    const int   LENGTH_MIN  = 1;
    const int   LENGTH_MAX  = 10;

    // Массив значений
    std::vector<unsigned int>   m_array;        // массив со значениями
    unsigned int                m_counter = 0;  // счётчик ввода элементов в массив

    static const QList<QString>           m_label_names;  // список названий, элементов управления

    // Элементы управления
    QLabel      *lbl_what_to_do;    // Надпись, которая говорит, что делать
    QSpinBox    *spb_number;        // Поле ввода значений
    QPushButton *pbt_step;          // Кнопка действия
    QLabel      *lbl_result;        // Информационное поле: выводит ошибки или результат

public:
    explicit P_1_2_MinNumber(QWidget *parent = nullptr);

    // метод, возвращающий минимальное значение в массиве
    int     minNumber();

private slots:
    void    slot_resetAllElements();     // сбрасывает все к исходным значениям
    void    slot_setNewArraySize();      // метод, делающий ресайз вектора
    void    slot_startCycleOfCounting(); // метод, отвечающий за ввод данных
//    void    slot_showResults();
};

#endif // P_1_2_MINNUMBER_H
