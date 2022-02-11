#ifndef P_5_2_PRICETABLE_H
#define P_5_2_PRICETABLE_H

#include <QWidget>

class QGridLayout;

class P_5_2_PriceTable : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *m_layout_result;
public:
    explicit P_5_2_PriceTable(QWidget *parent = nullptr);

private slots:
    void slotChangeTable(const double&);
};

#endif // P_5_2_PRICETABLE_H
