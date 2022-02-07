#ifndef P_4_1_VERSTA_H
#define P_4_1_VERSTA_H

#include <QWidget>

class QLineEdit;

class P_4_1_versta : public QWidget
{
    Q_OBJECT

private:
    QLineEdit   *m_result;
public:
    explicit P_4_1_versta(QWidget *parent = nullptr);

    // Взял за привычку такие методы делать статическими
    // чтобы их могли вызывать другие объекты без
    // создания нового экземпляра текущего класса
    static double  getDistanceInVerst(const double&);
private slots:
    void    slotShowVerst(const double&);
};

#endif // P_4_1_VERSTA_H
