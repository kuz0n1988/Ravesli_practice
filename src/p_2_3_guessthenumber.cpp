#include "p_2_3_guessthenumber.h"

#include <chrono>   // для зерна ГСЧ

#include <QStringList>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
//#include <QScrollArea>  // когда осознал, что попыток может быть дейтсвительно много
#include <QPlainTextEdit>

#include <QDebug>

#include "makinghtmllink.h"

// ===================ПЕРЕЧИСЛЕНИЯ===================

enum Stages
{
    START       = 0,
    TRY         = 1,
    YOUWIN      = 2
};

// ==============ИНИЦИАЛИЗАЦИЯ КОНСТАНТ==============
const QStringList P_2_3_GuessTheNumber::M_LABELS_BUTTN =
    {"СТАРТ",       //0
     "ВВОД",        //1
     "ЕЩЁ РАЗ"};    //2

const QStringList P_2_3_GuessTheNumber::M_LABELS_TITLE =
    {"Добро пожаловать в игру \"Угадай число\"",                 //0
     "Попытка #%1.\nВведите Ваш вариант (трёхзначное число):",   //1
     "Поздравляем с победой!"};                                  //2

const QStringList P_2_3_GuessTheNumber::M_LABELS_RESLT =

        /*==================== 0 ====================*/

    {"Правила игры:\n"
     "Компьютер загадывает трехзначное число. "
     "Вы должны его отгадать. "
     "После очередного числа вам будет сообщено, "
     "сколько цифр угадано и сколько из них "
     "находится на своих местах. \n"
     "Количество попыток неограничено!",

        /*==================== 1 ====================*/

     "Попытка #%1\n"
     "Ваш вариант: %2\n"
     "Угадано: %3\t На своих местах:%4\n",

        /*==================== 2 ====================*/

     "\n***Вы угадали число %1***\n"
     "Использовано попыток: %2\n"};

// ====================КОНСТРУКТОР===================

P_2_3_GuessTheNumber::P_2_3_GuessTheNumber(QWidget *parent) : QWidget(parent)
{
    setObjectName("23");

    m_lbl_title     = new QLabel(this);
    m_spb_variant   = new QSpinBox(this);
    m_spb_variant->setRange(0, 999);
    m_pbt_button    = new QPushButton(this);
    m_lbl_result    = new QPlainTextEdit(this);
    m_lbl_result->setReadOnly(true);
//    m_lbl_result->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);

    /* Изначально пытался запихнуть QLabel в QScrollArea и безуспешно
     * пытался понять, почему же его так "скукоживает"
     * Но потом в документации случайно увидел, что QPlainTextEdit
     * является потомком  QAbstractScrollArea, так что просто поменял
     * тип объекта на него и чуть-чуть переписал код
     * */
/*    QScrollArea *scrl = new QScrollArea(this);
    scrl->setWidget(m_lbl_result);
    scrl->setFixedSize(450, 300);*/

    slotReset();

    QVBoxLayout *layout_main = new QVBoxLayout(this);
                 layout_main->addWidget(m_lbl_title);
                 layout_main->addWidget(m_spb_variant);
                 layout_main->addWidget(m_pbt_button);
                 layout_main->addWidget(m_lbl_result, 5);
                 layout_main->addWidget(MakingHtmlLink::getMyHtmlLabel(this), 1, Qt::AlignBottom);
}

// ======================МЕТОДЫ======================

std::vector<int> P_2_3_GuessTheNumber::onlyUniqueDigits(const std::array<int, ARRAY_LENGTH> &arr)
{
    // сначала хотел все эти операции сделать вручную, как я делал для указателей
    // но в STL-бибилиотеке для std::array и std::vector уже всё реализовано

    std::vector<int> temp (arr.begin(), arr.end());
    qDebug () << temp;
    std::sort(temp.begin(), temp.end());
    qDebug () << temp;
    temp.resize(std::unique(temp.begin(), temp.end()) - temp.begin());
    // не до конца понял принцип использования unique через resize

    return temp;
}

std::array<int, 3> P_2_3_GuessTheNumber::getRandom3Digits()
{
    //return std::array<int, 3> { 6, 5, 8};
    /*
     * Эта строка нужна была исключительно для сверки примера из задания
     * с работой алгоритма. В результате я сделал вывод, что текст из
     * примера нихрена не соответствует задаче.
     * Загадано число 658. На второй попытке пользователь вводит 456.
     * Соответственно угадано две цифры (5 и 6) одна из которых (5)
     * находится на своём месте в центре. В примере же выдаётся:
     * "Угадано: 1. На своих местах: 0."
     * При этом на третьей попытке пользователь вводит 654 и на этот
     * раз программа из примера сообщает правильный ответ:
     * Угадано: 2. На своих местах: 2
     *
     * Либо я тупой и не понял задачи, либо описание задачи корявое
     * либо, вероятнее всего, корявый пример.
     * */


    // *****Мне очень понравился вихрь Мерсенна*****
    // Получаем зерно из значения текущего времени
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // создаём вихрь и присваиваем ему зерно
    std::mt19937 mersenne(seed);

    // Генерируем три огрооооомных псевдослучайных числа (они реально огромные)
    // и берём от каждого из них последнюю цифру.
    // Правда, можно было взять %1000 и разбить итоговое значение по-разрядам...
    return std::array<int, ARRAY_LENGTH> {  static_cast<int>(mersenne() % 10),
                                            static_cast<int>(mersenne() % 10),
                                            static_cast<int>(mersenne() % 10) };
}

std::array<int, 3>  P_2_3_GuessTheNumber::getUsers3Digits(const int& number)
{
    std::array<int, ARRAY_LENGTH> temp_array;

    // Был соблазн запихнуть все эти манипуляции в строчку return.
    // Однако, я уже писал когда-то рабочий алгоритм на голых указателях.
    // Он был небезопасный, непонятный и использовал кучу параметров.
    // По этому я просто переписал его под std::array, а мозг не включал.
    temp_array.at(0) = number / 100;
    temp_array.at(1) = (number - temp_array[0]*100) / 10;
    temp_array.at(2) = number - temp_array[0]*100 - temp_array[1]*10;

    return temp_array;
}

/* Не нужно, потому что уже реализовано в стандартной библиотеке
bool P_2_3_GuessTheNumber::compareArrays(std::array<int, ARRAY_LENGTH> arr1,
                                         std::array<int, ARRAY_LENGTH> arr2)
{
    for(int i = 0; i < ARRAY_LENGTH; i++)
        if(arr1[i] != arr2[i])
            return false;

    return true;
}
*/

int P_2_3_GuessTheNumber::digitsOnTheirPlace(const std::array<int, ARRAY_LENGTH> &arr1,
                                             const std::array<int, ARRAY_LENGTH> &arr2)
{
    int counter = 0;

    for(int i = 0; i < ARRAY_LENGTH; i++)
        if(arr1[i] == arr2[i])
            counter++;

    return counter;
}

int P_2_3_GuessTheNumber::matchingNumbers  (const std::array<int, ARRAY_LENGTH> &base,
                                            const std::array<int, ARRAY_LENGTH> &input)
{
    // пользователь может ввести число с одинаковыми цифрами
    // Например, если загадано число 223, а пользователь ввёл 333
    // то, фактически, он угадал лишь одну цифру из трёх не зависимо
    // от положения в массиве
    // Если же пользователь ввёл 222, то он угадал две цифры из трёх

    // По этому создаём ещё один динамический массив, содержащий
    // только уникальные значения пользовательского ввода
    std::vector<int> uniq = onlyUniqueDigits(input);

    int matched_counter = 0; // Счётчик совпадений

    for(unsigned int i = 0; i < uniq.size(); i++)
        for(unsigned int j = 0; j < base.size(); j++)
            if(uniq[i] == base[j])
                matched_counter++;

    return matched_counter;
}

// ======================СЛОТЫ=======================

void P_2_3_GuessTheNumber::slotReset()
{
    // сбрасываем счётчик до единицы
    m_counter = 1;

    // меняем надписи на элементах управления
    m_lbl_title->      setText(M_LABELS_TITLE[START]);
    m_pbt_button->     setText(M_LABELS_BUTTN[START]);
    m_lbl_result->setPlainText(M_LABELS_RESLT[START]);

    // очищаем поле ввода и прячем
    m_spb_variant->setValue(555);
    m_spb_variant->hide();

    // сбрасываем подключение сигналов кнопки к слотам
    m_pbt_button->disconnect();
    // и подключаем сигнал clicked к слоту slotStart
    connect(m_pbt_button, SIGNAL(clicked()), this, SLOT(slotStart()));
}

void P_2_3_GuessTheNumber::slotStart()
{
    m_random_digits = getRandom3Digits();
    qDebug() << "Digits generated: " << m_random_digits[0] << m_random_digits[1] << m_random_digits[2];

    // меняем надписи на элементах управления
    m_lbl_title->        setText(M_LABELS_TITLE[TRY].arg(m_counter));
    m_pbt_button->       setText(M_LABELS_BUTTN[TRY]);
    m_lbl_result->  setPlainText("Ход игры:\n");

    // показываем поле ввода
    m_spb_variant->show();

    // переподключаем кнопку к слоту slotEnterVariant
    disconnect  (m_pbt_button, SIGNAL(clicked()), this, SLOT(slotStart()));
    connect     (m_pbt_button, SIGNAL(clicked()), this, SLOT(slotEnterVariant()));
}

void P_2_3_GuessTheNumber::slotEnterVariant()
{
    std::array<int, 3> users_variant = getUsers3Digits(m_spb_variant->value());

    qDebug() << "User entered: " << users_variant[0] << users_variant[1] << users_variant[2];

    m_lbl_title->   setText(M_LABELS_TITLE[TRY].arg(m_counter));

    // =====ЕСЛИ ЧИСЛО УГАДАНО
    if(m_random_digits == users_variant)
    {
        // Поздравляем с победой заменой надписей
        m_lbl_title->   setText(M_LABELS_TITLE[YOUWIN]);
        m_pbt_button->  setText(M_LABELS_BUTTN[YOUWIN]);
        m_lbl_result->  appendPlainText(M_LABELS_RESLT[YOUWIN]
                                        .arg(QString::number( m_random_digits[0]*100 +
                                                              m_random_digits[1]*10  +
                                                              m_random_digits[2]),
                                             QString::number( m_counter)));

        // переподключаем кнопку к слоту slotReset
        disconnect  (m_pbt_button, SIGNAL(clicked()), this, SLOT(slotEnterVariant()));
        connect     (m_pbt_button, SIGNAL(clicked()), this, SLOT(slotReset()));
    }

    // =====ЕСЛИ ЧИСЛО НЕ УГАДАНО
    else
    {

        // Находим количество угаданных цифр...
        int matched = matchingNumbers(m_random_digits, users_variant);
        // ...и сколько цифр находится на своих местах
        int on_their_place = digitsOnTheirPlace(m_random_digits, users_variant);

        // Добавляем полученные сведения в поле с результатами
        m_lbl_result->appendPlainText(
                                  M_LABELS_RESLT[TRY]
                                    .arg(QString::number(m_counter++),  // заодно увеличиваем значение счётчика
                                         QString::number(users_variant[0]*100 +
                                                         users_variant[1]*10  +
                                                         users_variant[2]),
                                         QString::number(matched),
                                         QString::number(on_their_place)));
    }
}
