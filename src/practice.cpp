#include "practice.h"

#include <QStackedWidget>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

#include "makinghtmllink.h"

#include "p_1_1_sandwich.h"             // Cэндвич с мороженным
#include "p_1_2_minnumber.h"            // Поиск минимального числа
#include "p_1_3_timeoftheyear.h"        // Вывод названия времени года

#include "p_2_1_dacha.h"                // Стоимость поездки на дачу
#include "p_2_2_discount.h"             // Расчёт размера скидки
#include "p_2_3_guessthenumber.h"       // Игра "угадай число"

#include "p_3_1_speedrunner.h"          // Определяет скорость бегуна
#include "p_3_2_positiveevenintsum.h"   // Сумматор положительных четных чисел
#include "p_3_3_morsecode.h"            // МОРЗЯНКА

#include "p_4_1_versta.h"               // Преобразовывает километры в вёрсты
#include "p_4_2_averageofdoublearray.h" // Среднее значение элементов ряда чисел
#include "p_4_3_arrayconcatenator.h"    // Соединитель сортированных массивов

#include "p_5_1_minutestohours.h"       // Перевод минут в часы и минуты
#include "p_5_2_pricetable.h"           // Таблица с ценами на яблоки
#include "p_5_3_timersignal.h"          // Таймер включающий сигнал

#include "p_6_1_2numbers1compare.h"     // Сравнивает два числа


Practice::Practice(QWidget *parent)
    : QWidget(parent)
{
    qDebug () << "================================================================";
    qDebug () << "====================Application just started====================";
    qDebug () << "================================================================";

    // Левая половина
    m_main_widget                   = new QStackedWidget(this);
    m_main_widget->setFrameStyle(QFrame::Box | QFrame::Raised);
    m_main_widget->setLineWidth(2);

    MakingHtmlLink *lbl_html_link    = new MakingHtmlLink(0, this); // создаём ссылку

    initialize();               // Инициализируем m_main_widget

    // Правая половина
    // ===Блок выбора части
    QLabel      *lbl_select_part    = new QLabel("Выберите &часть:", this);
                 m_cmb_select_part  = new QComboBox(this);
    lbl_select_part->setBuddy(m_cmb_select_part); // не работает с английской раскладкой

    for(int i = 0; i < (1+((m_main_widget->count())-1)/3); i++)   // чтобы не делать ручками
        m_cmb_select_part->addItem("Часть №" + QString::number(i+1));

    connect(m_cmb_select_part, SIGNAL(currentIndexChanged(int)), SLOT(slot_changeWidget()));
    connect(m_cmb_select_part, SIGNAL(currentIndexChanged(int)),
            lbl_html_link,   SLOT(slotChangeHtmlLink(int)));

    /* Оставил в качестве примера подключения слотов к сигналам путём получения
     * указателей на перегруженные функции через явное преобразование типов
     * Господи, как же уродливо выглядит эта конструкция
    connect(cmb_select_part,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            static_cast<void (Practice::*)(int)>(&Practice::slot_changePart));    */

    // ===Блок выбора задачи
    QLabel      *lbl_select_task    = new QLabel("Выберите &задание:", this);
                 m_cmb_select_task    = new QComboBox(this);
    lbl_select_task->setBuddy(m_cmb_select_task); // не работает с английской раскладкой
    m_cmb_select_task->addItem("Задание #1 - EASY");
    m_cmb_select_task->addItem("Задание #2 - MEDIUM");
    m_cmb_select_task->addItem("Задание #3 - HARD");
    connect(m_cmb_select_task, SIGNAL(currentIndexChanged(int)), SLOT(slot_changeWidget()));

    // Компоновка
    // ===Компонуем левую половину
    QVBoxLayout *left_layout        = new QVBoxLayout();
    left_layout->addWidget(m_main_widget, 2);
    left_layout->addWidget(lbl_html_link, 0, Qt::AlignBottom);

    // ===Компонуем правую половину
    QVBoxLayout *right_layout       = new QVBoxLayout();
    right_layout->addWidget(lbl_select_part,   0, Qt::AlignTop);
    right_layout->addWidget(m_cmb_select_part,   0, Qt::AlignTop);
    right_layout->addWidget(lbl_select_task,   0, Qt::AlignTop);
    right_layout->addWidget(m_cmb_select_task,   1, Qt::AlignTop);

    // ===Компонуем лево и право
    QHBoxLayout *box_main           = new QHBoxLayout(this);
    box_main->addLayout(left_layout, 1);
    box_main->addLayout(right_layout, 0);

    // Поскольку переменных посредников у нас больше нет
    // выставляем значения ручками
    m_cmb_select_part->setCurrentIndex(m_cmb_select_part->count()-1);
    m_cmb_select_task->setCurrentIndex(((m_main_widget->count()-1)%3));

    /* Эта строчка больше не нужна, т.к. ComboBox-ы напрямую связаны
     * с этим слотом, а их значения мы меняем двумя строчками сверху
    slot_changeWidget();
    */
}

Practice::~Practice(){}

// ============================== МЕТОДЫ =============================

void Practice::initialize()
{
    // ==============================ЧАСТЬ 1==============================

    // 1.1. Задачка про сэндвич с мороженным
    m_main_widget->addWidget(new P_1_1_Sandwich(this));
    // 1.2. Задачка на поиск минимального числа
    m_main_widget->addWidget(new P_1_2_MinNumber(this));
    // 1.3. Задачка на вывод названия времени года по месяцу
    m_main_widget->addWidget(new P_1_3_TimeOfTheYear(this));

    // ==============================ЧАСТЬ 2==============================

    // 2.1. Расчёт стоимости поездки на дачу
    m_main_widget->addWidget(new P_2_1_dacha(this));
    // 2.2. Расчёт размера скидки
    m_main_widget->addWidget(new P_2_2_Discount (this));
    // 2.3. Игра "угадай трёхзначное положительное число"
    m_main_widget->addWidget(new P_2_3_GuessTheNumber (this));

    // ==============================ЧАСТЬ 3==============================

    // 3.1. Расчёт скорости бега
    m_main_widget->addWidget(new P_3_1_SpeedRunner(this));
    // 3.2. Сумма положительных чётных чисел
    m_main_widget->addWidget(new P_3_2_PositiveEvenIntSum (this));
    // 3.3. Преобразователь русского языка в азбуку Морзе
    m_main_widget->addWidget(new P_3_3_MorseCode (this));

    // ==============================ЧАСТЬ 4==============================

    // 4.1. Конвертирует километры в вёрсты
    m_main_widget->addWidget(new P_4_1_versta(this));
    // 4.2. Рассчитывает среднее арифметическое значение элементов массива
    m_main_widget->addWidget(new P_4_2_AverageOfDoubleArray (this));
    // 4.3  Соединяет два упорядоченных массива в один
    m_main_widget->addWidget(new P_4_3_ArrayConcatenator (this));

    // ==============================ЧАСТЬ 5==============================

    // 5.1. Получаем ввод в минутах и переводим его в часы и минуты
    m_main_widget->addWidget(new P_5_1_MinutesToHours (this));
    // 5.2. Получаем ввод в минутах и переводим его в часы и минуты
    m_main_widget->addWidget(new P_5_2_PriceTable (this));
    // 5.3. Таймер, который выставляет пользователь.
    m_main_widget->addWidget(new P_5_3_TimerSignal (this));

    // ==============================ЧАСТЬ 6==============================

    // 6.1. Сравниваем два числа, которые вводит пользователь
    m_main_widget->addWidget(new P_6_1_2Numbers1Compare (this));
}

// ============================== МЕТОДЫ ==============================

int Practice::makeKey()
{
    /* Чтобы придумать этот алгоритм, я полтора часа решал системы квадратных
     * уравнений и уже подумывал, а не вспомнить ли как решаются матрицы
     * Но потом до меня дошло, что нужно просто текущей индекс части умножать
     * на три и прибавлять текущий индекс задания
     * MAP больше не нужна!!!
     * */
    return ((m_cmb_select_part->currentIndex()*3)+(m_cmb_select_task->currentIndex()));
}

// ============================== СЛОТЫ ==============================

void Practice::slot_changeWidget()
{ m_main_widget->setCurrentIndex(makeKey()); }
