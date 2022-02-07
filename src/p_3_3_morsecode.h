#ifndef P_3_3_MORSECODE_H
#define P_3_3_MORSECODE_H

#include <QWidget>
#include <array>
#include <string>

class QPlainTextEdit;

class P_3_3_MorseCode : public QWidget
{
    Q_OBJECT
private:
    static const std::array<std::string, 36> M_ABC_MORSE;

    QPlainTextEdit  *m_morse;
public:
    explicit P_3_3_MorseCode(QWidget *parent = nullptr);

    // в качестве параметра использовал wstring,
    // т.к. он понимает кириллицу
    // этот метод в принципе работает ТОЛЬКО С КИРИЛЛИЦЕЙ
    static std::string getMorseCode(const std::wstring &source);

private slots:
    // Преобразует данные, вводимые пользователем, в код Морзе
    void slotConvertToMorse(const QString&);

    // Воспроизводит морзянку через динамик.
    // !!!!!==========ВАЖНО==========!!!!!
    // Я ещё не освоил потоки, по этому активация
    // данного слота наглухо блокирует программу,
    // и она будет висеть, пока морзянка
    // не воспроизведётся полностью.
    void slotBeepTheMorse();
};

#endif // P_3_3_MORSECODE_H
