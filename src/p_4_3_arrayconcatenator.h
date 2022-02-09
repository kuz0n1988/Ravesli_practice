#ifndef P_4_3_ARRAYCONCATENATOR_H
#define P_4_3_ARRAYCONCATENATOR_H

#include <QWidget>

#include <vector>

class QVBoxLayout;
class QPlainTextEdit;
class QString;

class P_4_3_ArrayConcatenator : public QWidget
{
    Q_OBJECT
private:
    std::vector<int> m_arr1;
    std::vector<int> m_arr2;

    QVBoxLayout     *m_layout_left;
    QVBoxLayout     *m_layout_right;

    QPlainTextEdit  *m_result;

private:
    // вытягивает значения из SpinBox-ов, лежащих в QVBoxLayout
    // после чего пихает их в вектор
    std::vector<int>    putNumbersToArray   (const QVBoxLayout*);

    // достаёт значения из вектора и пихает обратно в SpinBox-ы
    void getNumbersFromArray (QVBoxLayout*, const std::vector<int>&);

    // Превращает значения вектора в оформленную строку
    QString vectorToQString (const std::vector<int> &arr);

public:
    explicit P_4_3_ArrayConcatenator(QWidget *parent = nullptr);

    // Соединяет ОТСОРТИРОВАННЫЕ массивы (собственно, это цель задачи)
    static std::vector<int> concatenateSortedArrays
            (const std::vector<int> &arr1,
             const std::vector<int> &arr2);

private slots:
    void    slotChangeArrayLength(int);
    void    sortAndConcatenate();
};

#endif // P_4_3_ARRAYCONCATENATOR_H
