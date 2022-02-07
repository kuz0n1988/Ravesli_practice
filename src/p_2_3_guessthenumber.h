#ifndef P_2_3_GUESSTHENUMBER_H
#define P_2_3_GUESSTHENUMBER_H

#include <array>
#include <vector>
#include <random> // для std::random_device и std::mt19937

#include <QWidget>

class QStringList;
class QSpinBox;
class QPushButton;
class QLabel;
class QPlainTextEdit;

class P_2_3_GuessTheNumber : public QWidget
{
    Q_OBJECT
private:
    // =====КОНСТАНТЫ=====

    // Предельное количество цифр в массиве
    static const int ARRAY_LENGTH = 3;

    // Текст для элементов
    static const QStringList M_LABELS_BUTTN;
    static const QStringList M_LABELS_TITLE;
    static const QStringList M_LABELS_RESLT;

    // ===== ПЕРЕМЕННЫЕ =====

    unsigned int m_counter;                                      // Счётчик попыток
    std::array<int, ARRAY_LENGTH> m_random_digits;  // Три случайные цифры

    // Элементы интерфейса
    QLabel          *m_lbl_title;
    QSpinBox        *m_spb_variant; // Поле для пользовательского ввода варианта
    QPushButton     *m_pbt_button;  // Универсальная кнопка (СТАРТ/ВВОД/ЗАНОВО)
    QPlainTextEdit  *m_lbl_result;  // Информационное поле с результатами ввода
private:
    // возвращает вектор с уникальными значениями
    std::vector<int> onlyUniqueDigits(const std::array<int, ARRAY_LENGTH>& arr);
public:
    P_2_3_GuessTheNumber(QWidget *parent = nullptr);

    std::array<int, ARRAY_LENGTH>  getRandom3Digits();          // возвращает три случайные цифры
    std::array<int, ARRAY_LENGTH>  getUsers3Digits(const int&); // преобразует int в массив из 3-х цифр
                                                                // предполагается значение от 0 до 999

    /* Не нужно, потому что есть перегрузка == для std::array
    bool compareArrays (std::array<int, ARRAY_LENGTH> arr1,
                        std::array<int, ARRAY_LENGTH> arr2);    // Возвращает true, если массивы идентичны
                        */

    int digitsOnTheirPlace(const std::array<int, ARRAY_LENGTH> &arr1,  // Возвращает количество цифр,
                           const std::array<int, ARRAY_LENGTH> &arr2); // находящихся на своих местах

    int matchingNumbers   (const std::array<int, ARRAY_LENGTH> &base,   // Возвращает суммарное количество совпадений
                           const std::array<int, ARRAY_LENGTH> &input); // с base из варианта, введённого в input

private slots:
    void slotReset();                       // Сброс и инициализация переменных
    void slotStart();                       // Начало игры
    void slotEnterVariant();                // Получение и обработка ввода
};

#endif // P_2_3_GUESSTHENUMBER_H
