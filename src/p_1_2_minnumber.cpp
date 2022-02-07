#include "p_1_2_minnumber.h"

//#include <QtWidgets>

#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QDebug>

// Это чтоб не запутаться в цифрах. Ну и для наглядности.
enum Label_index
{
    WHATTD_ARRAYSIZE,   // 0
    WHATTD_NUMBERS,     // 1
    BUTTON_ARRAYSIZE,   // 2
    BUTTON_NUMBERS,     // 3
    BUTTON_FINISH,      // 4
    RESULT_ARRAYSIZE,   // 5
    RESULT_NUMBERS,     // 6
    RESULT_FINISH,      // 7
};

const QList<QString> P_1_2_MinNumber::m_label_names
    =   {"Введите размер ряда чисел (от 1 до 10):",                                         // 0 - lbl_what_to_do;
         "Введите число не меньше 0:",                                                      // 1 - lbl_what_to_do;
         "Установить размер массива",                                                       // 2 - pbt_step
         "ВВОД",                                                                            // 3 - pbt_step
         "СБРОС",                                                                           // 4 - pbt_step
         "Введите размер будущего массива\nРазмер массива не должен превышать 10 чисел",    // 5 - lbl_result
         "Введите число №%1",                                                               // 6 - lbl_result
         "Введён ряд чисел: %1\nМинимальное введённое значение: %2"};                       // 7 - lbl_result

P_1_2_MinNumber::P_1_2_MinNumber(QWidget *parent) : QWidget(parent)
{
    qDebug() << "Object " << objectName() << " constructing...";

    lbl_what_to_do  = new QLabel        (m_label_names[WHATTD_ARRAYSIZE], this);   // Что делать
    spb_number      = new QSpinBox      (this);                                    // Поле для ввода числа
    spb_number->    setRange(LENGTH_MIN, LENGTH_MAX);
    pbt_step        = new QPushButton   (m_label_names[BUTTON_ARRAYSIZE], this);   // Кнопка действия
    lbl_result      = new QLabel        (m_label_names[RESULT_ARRAYSIZE], this);   // Информационное поле и вывод результата

    QLabel  *lbl_html_page  = new QLabel
            ("<a href=\"https://ravesli.com/praktika-chast-1/\">"
             "<div>Страница на Ravesli.com</div>"
             "<div>Часть №1: Практические задания по С++</div></a>");
             lbl_html_page->setOpenExternalLinks(true);

    // Подключаем кнопку к сигналу: указать размер массива
    connect(pbt_step, SIGNAL(clicked()), this, SLOT(slot_setNewArraySize()));

    // Компонуем в столбик
    QVBoxLayout *layout_main = new QVBoxLayout(this);

    layout_main->addWidget(lbl_what_to_do, 0);
    layout_main->addWidget(spb_number,     0);
    layout_main->addWidget(pbt_step,       0);
    layout_main->addWidget(lbl_result,     5, Qt::AlignTop);
    layout_main->addWidget(lbl_html_page);
}


int P_1_2_MinNumber::minNumber()
{
    unsigned int temp = m_array[0];
    std::vector<unsigned int>::const_iterator it = m_array.begin() + 1;

    while (it != m_array.end())
    {
        if (*it < temp)
            temp = *it;
        it++;
    }

    return temp;
}

void P_1_2_MinNumber::slot_resetAllElements()
{
    m_array.clear();
    m_counter = 0;

    /* ==========ПРИМЕЧАНИЕ==========
     * Эта команда по идее отключает кнопку от всех сигналов и слотов
     * Изначально я хотел сделать отдельную кнопку сброса, чтобы
     * можно было в любой момент прервать ввод ряда чисел и начать заново
     * Но потом забил хер.
     * ============================== */
    pbt_step->disconnect();

    lbl_what_to_do->setText(m_label_names[WHATTD_ARRAYSIZE]);
    spb_number->    setRange(LENGTH_MIN, LENGTH_MAX);
    pbt_step->      setText(m_label_names[BUTTON_ARRAYSIZE]);
    lbl_result->    setText(m_label_names[RESULT_ARRAYSIZE]);

    // Подключаем сигнал кнопки к слоту: указать размер массива
    connect(pbt_step, SIGNAL(clicked()), this, SLOT(slot_setNewArraySize()));
}

void P_1_2_MinNumber::slot_setNewArraySize()
{
    m_array.resize(spb_number->value());

    /* ==========ПРИМЕЧАНИЕ==========
     * По условиям задачи при вводе отрицательного числа надо выдавать предупреждение
     * Но я в принципе заблокировал такую возможность ввода настрйоками интерфейса
     * P.S.: Да, std::numeric_limits<int>::max() - я честно стырил с интернетов  */
    spb_number->setRange(0, std::numeric_limits<int>::max());

    // Меняем слот для кнопки на: ввод значений массива
    disconnect  (pbt_step, SIGNAL(clicked()), this, SLOT(slot_setNewArraySize()));
    connect     (pbt_step, SIGNAL(clicked()), this, SLOT(slot_startCycleOfCounting()));

    // Ну и меняем надписи на всех элементах управления
    lbl_what_to_do->setText(m_label_names[WHATTD_NUMBERS]);
    pbt_step->      setText(m_label_names[BUTTON_NUMBERS]);
    lbl_result->    setText(m_label_names[RESULT_NUMBERS].arg(m_counter+1));
}

void P_1_2_MinNumber::slot_startCycleOfCounting()
{
    /* ==========ПРИМЕЧАНИЕ==========
     * По условиям задачи при вводе отрицательного числа надо выдавать предупреждение
     * Но я в принципе заблокировал такую возможность настройками интерфейса
     * ============================== */
    m_array[m_counter++] = spb_number->value();
    lbl_result->    setText(m_label_names[RESULT_NUMBERS].arg(m_counter+1));

    // Если введён последний элемент массива - пришло время собрать всю колбасу воедино
    if(m_counter >= m_array.size())
    {
        // Колбаса из значений, введённых в массив
        QString temp = "";
        for(unsigned int i = 0; i < m_array.size(); i++)
        {
            temp += "\nЧисло #" + QString::number(i+1) + ": ";
            temp += QString::number(m_array[i]) + " ";
        }
        temp+= "\n";

        // Меняем надписи на элементах управления на итоговые
        lbl_what_to_do->setText("");
        pbt_step->      setText(m_label_names[BUTTON_FINISH]);
        lbl_result->    setText(m_label_names[RESULT_FINISH].arg(temp).arg(minNumber()));

        // Не забываем поменять слоты для кнопки.
        disconnect (pbt_step, SIGNAL(clicked()), this, SLOT(slot_startCycleOfCounting()));
        connect    (pbt_step, SIGNAL(clicked()), this, SLOT(slot_resetAllElements()));
    }
}
