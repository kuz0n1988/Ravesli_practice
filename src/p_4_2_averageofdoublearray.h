#ifndef P_4_2_AVERAGEOFDOUBLEARRAY_H
#define P_4_2_AVERAGEOFDOUBLEARRAY_H

#include <QWidget>

#include <vector>

class QSpinBox;
class QDoubleSpinBox;
class QLabel;
class QPushButton;
class QString;

class P_4_2_AverageOfDoubleArray : public QWidget
{
    Q_OBJECT
private:
    static const QStringList    m_labels;   // Текстовые шаблоны для надписей
    int                  m_counter = 0;     // Счётчик
    std::vector<double>  m_array;           // формируемый массив данных

    QLabel              *m_what_to_do;      // Информация о текущем этапе
    QSpinBox            *m_array_length;    // поле ввода размера массива
    QDoubleSpinBox      *m_array_element;   // поле ввода элементов массива
    QPushButton         *m_do;              // кнопка действия
    QLabel              *m_info;            // информационная панель

public:
    explicit P_4_2_AverageOfDoubleArray(QWidget *parent = nullptr);

/* Сначала я хотел запилить собственную реализацию поиска
 * минимального и максимального значений, но потом вспомнил, что
 * есть стандартные методы обработки контейнерных STL-классов
 *
    static double getArrayMin    (const std::vector<double>&);
    static double getArrayMax    (const std::vector<double>&);
*/

    // превращает значения массива в аккуратную колонку QString
    const QString       getAarrayElementsColumn();

    // Возвращает среднее арифметическое элементов массива
    static double       getArrayAverage(const std::vector<double> &array);
    void                showResult();

private slots:
    void    slotGetArrayLength();
    void    slotGetArrayElements();
    void    slotResetAllElements();
};

#endif // P_4_2_AVERAGEOFDOUBLEARRAY_H
