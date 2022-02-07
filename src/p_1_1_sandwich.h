#ifndef P_1_1_Sandwich_H
#define P_1_1_Sandwich_H

#include <QWidget>
#include <string>

class QLineEdit;
class QLabel;

class P_1_1_Sandwich : public QWidget
{
    Q_OBJECT
private:
    QLineEdit   *led_input;
    QLabel      *lbl_result;

    static bool isMirror        (const std::wstring &str); // Проверяет на зеркальность
    static bool isNotTwoSymbols (const std::wstring &str); // Проверяет наличие только двух типов символов в строке
public:
    explicit P_1_1_Sandwich(QWidget *parent = nullptr);

    // Aлгоритм написан на С++ без Qt, по этому std::wstring
    // Пробовал std::string, но начались проблемы с кириллицей
    static bool isIcecreamSandwich(const std::wstring &str);
private slots:
    void checkTheSandwich();
};

#endif // P_1_1_Sandwich_H
