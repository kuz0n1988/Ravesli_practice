#ifndef P_2_2_DISCOUNT_H
#define P_2_2_DISCOUNT_H

#include <QWidget>

class QLabel;
class QLineEdit;
class QStringList;

class P_2_2_Discount : public QWidget
{
    Q_OBJECT
private:
    static const QStringList  m_labels;

    // Была у меня мысль спрятать эти объёкты в конструктор
    // а потом заморочиться с реализацией через сигналы-слоты
    // Когда-нибудь потом я так и сделаю! Может быть.
    QLabel      *m_discount;
    QLineEdit   *m_discount_result;

public:
    explicit P_2_2_Discount(QWidget *parent = nullptr);

private slots:
    void    slotCalculateDiscount(const double& sum);
};

#endif // P_2_2_DISCOUNT_H
