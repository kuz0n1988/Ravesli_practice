#include "practice.h"

//#include <QtWidgets>
#include <QStackedWidget>
#include <QLabel>
#include <QSpinBox>
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


    initializeMap();        // Инициализируем m_main_widget и m_index_of_widget
    slot_changeWidget();    // Сразу ставим последний виджет...
    MakingHtmlLink *lbl_html_link    = new MakingHtmlLink(m_part, this); //...и создаём ссылку

    // Правая половина
    // ===Блок выбора части
    QLabel      *lbl_select_part    = new QLabel("Выберите &часть:", this);
    QSpinBox    *spb_select_part    = new QSpinBox(this);
    lbl_select_part->setBuddy(spb_select_part); // не работает с английской раскладкой
    spb_select_part->setRange(1, MAX_PARTS);
    spb_select_part->setValue(m_part);  // Сразу ставим на последний элемент
    connect(spb_select_part, SIGNAL(valueChanged(int)), SLOT(slot_changePart(int)));
    connect(spb_select_part, SIGNAL(valueChanged(int)), SLOT(slot_changeWidget()));
    connect(spb_select_part, SIGNAL(valueChanged(int)),
            lbl_html_link,   SLOT(slotChangeHtmlLink(int)));

    // ===Блок выбора задачи
    QLabel      *lbl_select_task    = new QLabel("Выберите &задание:", this);
    QSpinBox    *spb_select_task    = new QSpinBox(this);
    lbl_select_task->setBuddy(spb_select_task); // не работает с английской раскладкой
    spb_select_task->setRange(1, MAX_TASKS);
    spb_select_task->setValue(m_task);  // Сразу ставим на последний элемент
    connect(spb_select_task, SIGNAL(valueChanged(int)), SLOT(slot_changeTask(int)));
    connect(spb_select_task, SIGNAL(valueChanged(int)), SLOT(slot_changeWidget()));

    // Компоновка
    // ===Компонуем левую половину
    QVBoxLayout *left_layout        = new QVBoxLayout();
    left_layout->addWidget(m_main_widget, 2);
    left_layout->addWidget(lbl_html_link, 0, Qt::AlignBottom);

    // ===Компонуем правую половину
    QVBoxLayout *right_layout       = new QVBoxLayout();
    right_layout->addWidget(lbl_select_part,   0, Qt::AlignTop);
    right_layout->addWidget(spb_select_part,   0, Qt::AlignTop);
    right_layout->addWidget(lbl_select_task,   0, Qt::AlignTop);
    right_layout->addWidget(spb_select_task,   1, Qt::AlignTop);

    // ===Компонуем лево и право
    QHBoxLayout *box_main           = new QHBoxLayout(this);
    box_main->addLayout(left_layout, 1);
    box_main->addLayout(right_layout, 0);
}

Practice::~Practice(){}

// ============================== МЕТОДЫ =============================

void Practice::initializeMap()
{
    // Добавляем по-порядку задачки в виджет и в карту ключей

    // Набор переменных (уже не совсем избыточный) для добавления виджетов
    int      index;
    int      widget_key;

    // ==============================ЧАСТЬ 1==============================

    // 1.1. Задачка про сэндвич с мороженным
    index   = m_main_widget->addWidget(new P_1_1_Sandwich(this));
    widget_key      = makeKey(1, 1);
    m_index_of_widgets.insert(widget_key, index);

    // 1.2. Задачка на поиск минимального числа
    index   = m_main_widget->addWidget(new P_1_2_MinNumber(this));
    widget_key      = makeKey(1, 2);
    m_index_of_widgets.insert(widget_key, index);

    // 1.3. Задачка на вывод названия времени года по месяцу
    index   = m_main_widget->addWidget(new P_1_3_TimeOfTheYear(this));
    widget_key      = makeKey(1, 3);
    m_index_of_widgets.insert(widget_key, index);

    // ==============================ЧАСТЬ 2==============================

    // 2.1. Расчёт стоимости поездки на дачу
    index   = m_main_widget->addWidget(new P_2_1_dacha(this));
    widget_key      = makeKey(2, 1);
    m_index_of_widgets.insert(widget_key, index);

    // 2.2. Расчёт размера скидки
    index   = m_main_widget->addWidget(new P_2_2_Discount (this));
    widget_key      = makeKey(2, 2);
    m_index_of_widgets.insert(widget_key, index);

    // 2.3. Игра "угадай трёхзначное положительное число"
    index   = m_main_widget->addWidget(new P_2_3_GuessTheNumber (this));
    widget_key      = makeKey(2, 3);
    m_index_of_widgets.insert(widget_key, index);

    // ==============================ЧАСТЬ 3==============================

    // 3.1. Расчёт скорости бега
    index   = m_main_widget->addWidget(new P_3_1_SpeedRunner(this));
    widget_key      = makeKey(3, 1);
    m_index_of_widgets.insert(widget_key, index);

    // 3.2. Сумма положительных чётных чисел
    index   = m_main_widget->addWidget(new P_3_2_PositiveEvenIntSum (this));
    widget_key      = makeKey(3, 2);
    m_index_of_widgets.insert(widget_key, index);

    // 3.3. Преобразователь русского языка в азбуку Морзе
    index   = m_main_widget->addWidget(new P_3_3_MorseCode (this));
    widget_key      = makeKey(3, 3);
    m_index_of_widgets.insert(widget_key, index);

    // ==============================ЧАСТЬ 4==============================

    // 4.1. Конвертирует километры в вёрсты
    index   = m_main_widget->addWidget(new P_4_1_versta(this));
    widget_key      = makeKey(4, 1);
    m_index_of_widgets.insert(widget_key, index);

    // 4.2. Рассчитывает среднее арифметическое значение элементов массива
    index   = m_main_widget->addWidget(new P_4_2_AverageOfDoubleArray (this));
    widget_key      = makeKey(4, 2);
    m_index_of_widgets.insert(widget_key, index);

    // 4.3  Соединяет два упорядоченных массива в один
    index   = m_main_widget->addWidget(new P_4_3_ArrayConcatenator (this));
    widget_key      = makeKey(4, 3);
    m_index_of_widgets.insert(widget_key, index);

    // ==============================ЧАСТЬ 4==============================

    // 5.1. Получаем ввод в минутах и переводим его в часы и минуты
    index   = m_main_widget->addWidget(new P_5_1_MinutesToHours (this));
    widget_key      = makeKey(5, 1);
    m_index_of_widgets.insert(widget_key, index);

    // 5.2. Получаем ввод в минутах и переводим его в часы и минуты
    index   = m_main_widget->addWidget(new P_5_2_PriceTable (this));
    widget_key      = makeKey(5, 2);
    m_index_of_widgets.insert(widget_key, index);

    // 5.3. Таймер, который выставляет пользователь.
    index   = m_main_widget->addWidget(new P_5_3_TimerSignal (this));
    widget_key      = makeKey(5, 3);
    m_index_of_widgets.insert(widget_key, index);

    // Сразу ставим на последний элемент
    m_part = widget_key/10;
    m_task = widget_key%10;
}

int Practice::makeKey()
{    return makeKey(m_part, m_task);    }

int Practice::makeKey(int part, int task)
{
    if(part >= 1 && part <= MAX_PARTS &&
       task >= 1 && task <= MAX_TASKS)
        return part * 10 + task;
    else
        return -1;
}

// ============================== СЛОТЫ ==============================

void Practice::slot_changeWidget()
{    
    int key = makeKey();
    m_main_widget->setCurrentIndex(m_index_of_widgets[key]);

    qDebug() << "Tracing";
    qDebug() << "m_part:   " << m_part;
    qDebug() << "m_task:   " << m_task;
    qDebug() << "key:      " << key;
    qDebug() << "map[" << key << "]: " << m_index_of_widgets[key];

    qDebug() << Qt::endl << "Element " << key << " was called";
    qDebug() << "m_main_widget Current index is " << m_main_widget->currentIndex();
}

/* Повторяющийся код.
 * Работать то он будет, но надо подумать, как сократить.
 * */
void Practice::slot_changePart(int i)
{
    m_part = i;
}

void Practice::slot_changeTask(int i)
{
    m_task = i;
}
