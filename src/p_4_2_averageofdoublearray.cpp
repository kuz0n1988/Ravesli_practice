#include "p_4_2_averageofdoublearray.h"

#include <limits>

#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>

#include <QDebug>

#include "makinghtmllink.h"

const QStringList    P_4_2_AverageOfDoubleArray::m_labels = {
    "Введите количество чисел:",                                                    // 0 m_what_to_do
    "Введите элемент №%1",                                                          // 1 m_what_to_do

    "ВВОД ЗНАЧЕНИЯ",                                                                // 2 m_do

    "Введите длину ряда десятичных чисел от 1 до 10",                               // 3 m_info
    "Введите в поле значение элемента №%1",                                         // 4 m_info
    "Вы ввели следующий ряд чисел:\n%1\n"                                           // 5 arg.1 m_info
    "Среднее аримфетическое его значений:\t%2\n"                                    // 5 arg.2 m_info
    "Минимальное значение ряда:          \t\t%3\n"                                  // 5 arg.3 m_info
    "Максимальное значение ряда:         \t\t%4\n"                                  // 5 arg.4 m_info
};

P_4_2_AverageOfDoubleArray::P_4_2_AverageOfDoubleArray(QWidget *parent) : QWidget(parent)
{
    setObjectName("42");

                 m_what_to_do    = new QLabel(this);
                 m_array_length  = new QSpinBox(this);
                 m_array_length->setRange(1, 10);
// дубль             m_array_length->setValue(5);

                 m_array_element = new QDoubleSpinBox(this);
                 m_array_element->setDecimals(6);
                 m_array_element->setRange
                         (1.0 - std::numeric_limits<double>::max(),
                          std::numeric_limits<double>::max());
                /* Изначально в качестве нижней границы я пробовал
                 * std::numeric_limits<double>::min() и
                 * std::numeric_limits<double>::denorm_min(), но с этими
                 * параметрами было невозможно ввести никакие отрицательные
                 * значения.
                 * std::numeric_limits<double>::min_exponent позволяло
                 * ввести минимальное значение -1021,00
                 * std::numeric_limits<double>::min_exponent10 вообще давало
                 * возможность ввести минимум -307,00
                 * qDebug для std::numeric_limits<double>::min()
                 * выдал значение 2.22507e-308
                 * Пробовал ввести его ручками в качестве нижней границы.
                 * Нифига не сработало! Почему? Не знаю!
                 * Возможно, какие-то ограничения QDoubleSpinBox, хотя в
                 * документации ничего такого не нашел.
                 * */

// дубль           m_array_element->setValue(5.5);
// дубль           m_array_element->hide();

                 m_do            = new QPushButton(m_labels[2], this);
// дубль           connect(m_do, &QPushButton::clicked,
//                         this, &P_4_2_AverageOfDoubleArray::slotGetArrayLength);

                 m_info          = new QLabel(this);
                 m_info->setFrameStyle(QFrame::Panel);

                 slotResetAllElements();    // это вместо дублирования кода

    // Я таки решил запилить отдельную кнопку сброса
    QPushButton *btn_reset       = new QPushButton("Cброс", this);
                connect(btn_reset, &QPushButton::clicked,
                        this, &P_4_2_AverageOfDoubleArray::slotResetAllElements);

    QVBoxLayout *layout_main     = new QVBoxLayout(this);
    layout_main->addWidget(m_what_to_do);
    layout_main->addWidget(m_array_length);
    layout_main->addWidget(m_array_element);
    layout_main->addWidget(m_do);
    layout_main->addWidget(m_info, 5);
    layout_main->addWidget(btn_reset);
    layout_main->addWidget(MakingHtmlLink::getMyHtmlLabel(this), 1, Qt::AlignBottom);
}

// ====================МЕТОДЫ===================

const QString P_4_2_AverageOfDoubleArray::getAarrayElementsColumn()
{
    QString temp = "";

    for (unsigned long long i = 0; i < m_array.size(); i++)
    {
         temp += "Элемент № " +
                 QString::number(i+1) + ":\t" +
                 QString::number(m_array.at(i), 'f', 6) + '\n';
    }

    return temp;
}

double P_4_2_AverageOfDoubleArray::getArrayAverage(const std::vector<double> &array)
{
    double temp = 0.0;

    std::vector<double>::const_iterator it;
    for (it = array.begin(); it != array.end(); ++it)
        temp += *it;

    return temp / array.size();
}

// Изначально этот метод был слотом. Но потом я передумал :)
void    P_4_2_AverageOfDoubleArray::showResult()
{
    m_what_to_do->setText("");
    m_array_element->hide();

    // Вообще, поиск минимального и максимального значений
    // (да и среднего тоже), можно было бы завернуть в метод
    // slotGetArrayElements() и вычислялись бы они там сразу
    // в процессе ввода, сохраняя промежуточные результаты в
    // какие-нибудь private-переменные.
    // Но мне очень хотелось попробовать стандартные методы
    // обработки STL-контейнеров
    double min;
    double max;

    std::vector<double>::const_iterator it;
    it = std::min_element(m_array.begin(), m_array.end());
    min = *it;
    it = std::max_element(m_array.begin(), m_array.end());
    max = *it;

    /* Изначально я сделал m_labels[5].arg(...).arg(...).arg(...).arg(...)
     * но кутя сказала, что это "crazy-arg", по этому переделал.
     * */
    m_info->setText(m_labels[5].arg(
        getAarrayElementsColumn(),                          // 1 - весь ряд
        QString::number(getArrayAverage(m_array), 'f', 4),  // 2 - среднее
        QString::number(min,                      'f', 4),  // 3 - минимальное
        QString::number(max,                      'f', 4)));// 4 - максимальное
}

// ====================СЛОТЫ====================

void    P_4_2_AverageOfDoubleArray::slotGetArrayLength()
{
    m_array.resize(m_array_length->value());
    m_array_length->hide();  // прячем     QSpinBox
    m_array_element->show(); // показываем QDoubleSpinBox

    // Меняем надписи
    m_what_to_do->setText(m_labels[1].arg(QString::number(1)));
    m_info      ->setText(m_labels[4].arg(QString::number(1)));

    // Переподключаем кнопку к новому сигналу
    disconnect(m_do, &QPushButton::clicked,
               this, &P_4_2_AverageOfDoubleArray::slotGetArrayLength);
    connect(m_do, &QPushButton::clicked,
            this, &P_4_2_AverageOfDoubleArray::slotGetArrayElements);
}

void    P_4_2_AverageOfDoubleArray::slotGetArrayElements()
{
    m_array[m_counter++] = m_array_element->value();

    // Меняем надписи
    m_what_to_do->setText(m_labels[1].arg(QString::number(m_counter+1)));
    m_info      ->setText(m_labels[4].arg(QString::number(m_counter+1)));

    if(m_counter >= static_cast<int>(m_array.size()))
    {
        showResult();
        m_array_element->hide();
        m_do->hide();
    }
}

void    P_4_2_AverageOfDoubleArray::slotResetAllElements()
{
    m_array.clear();
    m_counter = 0;

    m_what_to_do->setText(m_labels[0]);

    m_array_length->setValue(5);
    m_array_length->show();

    m_array_element->setValue(5.555505);
    m_array_element->hide();

    // Мы не знаем, к какому сигналу была подключена кнопка m_do
    // по этому отключаем ВСЕ
    m_do->disconnect();
    m_do->show();
    connect(m_do, &QPushButton::clicked,
            this, &P_4_2_AverageOfDoubleArray::slotGetArrayLength);

    m_info->setText(m_labels[3]);
}
