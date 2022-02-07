#ifndef P_4_3_ARRAYCONCATENATOR_H
#define P_4_3_ARRAYCONCATENATOR_H

#include <QWidget>

#include <vector>

class QVBoxLayout;
class QPlainTextEdit;

class P_4_3_ArrayConcatenator : public QWidget
{
    Q_OBJECT
private:
    std::vector<int> m_arr1;
    std::vector<int> m_arr2;

    QVBoxLayout     *m_layout_left;
    QVBoxLayout     *m_layout_right;

    QPlainTextEdit  *m_result;
public:
    explicit P_4_3_ArrayConcatenator(QWidget *parent = nullptr);

private slots:
    void    slotChangeArrayLength(int);
};

#endif // P_4_3_ARRAYCONCATENATOR_H
