#include "p_1_1_sandwich.h"

//#include <QtWidgets>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>

#include <QDebug>

P_1_1_Sandwich::P_1_1_Sandwich(QWidget *parent) : QWidget(parent)
{

    qDebug() << "Object " << objectName() << " constructing...";

    QLabel  *lbl_input      = new QLabel    ("Введите сэндвич:", this);
             led_input      = new QLineEdit ("Введите сэндвич сюда", this);
             lbl_result     = new QLabel    ("Здесь будет отображаться результат", this);
             lbl_result->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    QLabel  *lbl_html_page  = new QLabel
            ("<a href=\"https://ravesli.com/praktika-chast-1/\">"
             "<div>Страница на Ravesli.com</div>"
             "<div>Часть №1: Практические задания по С++</div></a>");
             lbl_html_page->setOpenExternalLinks(true);

    connect(led_input, &QLineEdit::textEdited, this, &P_1_1_Sandwich::checkTheSandwich);

    QVBoxLayout *layout_main   = new QVBoxLayout(this);
    layout_main->addWidget(lbl_input);
    layout_main->addWidget(led_input,  1, Qt::AlignTop);
    layout_main->addWidget(lbl_result, 5);
    //layout_main->addStretch(5);
    layout_main->addWidget(lbl_html_page);

    qDebug() << "Object " << objectName() << " constructed!";
}

bool P_1_1_Sandwich::isMirror(const std::wstring &str)
{
    // Находим предельное количество циклов, равное половине массива
    // чтобы не высчитывать это значение каждый цикл.
    // Если количество элементов нечётное - пофиг. Центральный элемент
    // всё равно встречается лишь один раз
    unsigned long long counter = str.length() / 2;

    // Сравниваем первый и последний элемент, потом второй и предпоследний и т.д.
    // Если элементы неодинаковые - значит это не палиндром, а значит
    // точно не сэндвич с говном
    for (unsigned long long i = 0; i < counter; i++)
        if (str[i] != str[str.length() - i - 1])
            return false;

    return true;
}

bool P_1_1_Sandwich::isNotTwoSymbols(const std::wstring& str)
{
    // В задании было, что как минимум 2 символа должны быть различны,
    // но при этом говно между булками не может быть разного сорта
    // По этому проверяем на наличие ровно двух разных символов в массиве

    // Поскольку на зеркальность мы уже проверялись, то для простоты
    // расчётов половину строки можно выкинуть. Для этого создаём
    // временную переменную, которая соответствует:
    // а) для чётного количества символов - ровно половине строки
    // б) для нечётного количества - половине плюс один (чтобы не потерять центральный символ)

    std::wstring temp;

    if (str.length() % 2 == 0)
        temp = str.substr(0, str.length() / 2);
    else
        temp = str.substr(0, str.length() / 2 + 1);

    // Берём в качестве матрицы поиска первый символ
    wchar_t a = temp[0];

    // Ищем символ, отличающийся от первого
    // Если получаем std::string::npos то возвращаем false
    // (во всей строке только один символ, а их должно быть ровно два одинаковых)
    // Если получаем любой другой результат - меняем значение матрицы поиска на новое значение

    size_t b = temp.find_first_not_of(a, 0);
    // и да, я понятия не имею, что такое size_t, но функция find_first_not_of категорически
    // отказывалась возвращать мне что-то более простое и понятное для меня, типа 'char' или 'int'

    if (b == std::string::npos)
        return false;

    a = str[b]; // Если алгоритм дошел сюда, значит в строке больше одного значения. Меняем матрицу.

    // А теперь используя адрес массива size_t b в качестве отправной точки
    // едём до конца половинки нашей строки в поисках третьего символа
    // Если находим - возвращаем false, т.к. в в строке больше 2х разных символов
    // Если не находим, значит в строке только два разных символа - возвращаем true

    b = temp.find_first_not_of(a, b);

    if (b == std::string::npos)
        return true;

    return false;
}

bool P_1_1_Sandwich::isIcecreamSandwich(const std::wstring &str)
{
    // Проверяет, не пустая ли строка (не должна быть пустой)
    if (str.empty())
        return false;

    // Проверка на длину (должна быть не менее 3 символов)
    if (str.length() < 3)
        return false;

    // Проверка на зеркальность (левая и правая часть должны быть зеркальны)
    if (!isMirror(str))
        return false;

    // Проверка на количество символов (должно быть ровно 2 разных типа)
    if (!isNotTwoSymbols(str))
        return false;

    // Если все проверки прошли успешно - значит это сэндвич
    return true;
}

void P_1_1_Sandwich::checkTheSandwich()
{
    qDebug() << objectName() << " checkTheSandwich()";

    std::wstring temp = led_input->text().toStdWString();
    qDebug() << QString::fromStdWString(temp);

    if(isIcecreamSandwich(temp))
        lbl_result->setText("ДА, это сэндвич с мороженным!");
    else
        lbl_result->setText("Нет, это не сэндвич с мороженным!");
}
