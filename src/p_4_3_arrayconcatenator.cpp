#include "p_4_3_arrayconcatenator.h"

#include <QtWidgets>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

//#include "makinghtmllink.h"

// ==================== PRIVATE ====================

std::vector<int> P_4_3_ArrayConcatenator::putNumbersToArray(const QVBoxLayout* layout)
{
    /*  ========== ПРИМЕЧАНИЕ ==========
     * хотел использовать QLayoutIterator,
     * но он оказывается устаревший :(
     * */

    std::vector<int> temp;

    QSpinBox *tmp_spb;

    for(int i = 0; i < layout->count(); i++)
    {
        /* По идее, тут должна быть проверка типа и при невозможности
         * конвертации выбрасывать исключение
         * */
        tmp_spb = (QSpinBox*)(layout->itemAt(i)->widget());    // Явное преобразование
        temp.push_back(tmp_spb->value());
    }
    return temp;
}

void P_4_3_ArrayConcatenator::getNumbersFromArray(QVBoxLayout *layout, const std::vector<int> &arr)
{
    // Это на случай, если я совсем дурак
    if(layout->count() != static_cast<int>(arr.size()))
        throw   "Different object sizes. Perhabs, wrong pair in parameters!";

    QSpinBox *tmp_spb;
    for(int i = 0; i < layout->count(); i++)
    {
        tmp_spb = (QSpinBox*)(layout->itemAt(i)->widget());
        tmp_spb->setValue(arr[i]);
    }
}

QString P_4_3_ArrayConcatenator::vectorToQString (const std::vector<int> &arr)
{
    QString temp = "";

    for(long long unsigned int i = 0; i < arr.size()-1; i++)
        temp += QString::number(arr.at(i)) + ", ";

    temp += QString::number(arr.at(arr.size()-1));

    return temp;
}

// ==================== КОНСТРУКТОР ====================

P_4_3_ArrayConcatenator::P_4_3_ArrayConcatenator(QWidget *parent) : QWidget(parent)
{
    // Имена этих объектов придумывал "от балды".
    // Не стоит так делать.
    QLabel          *lbl_1      = new QLabel("Массив #1", this);
    QLabel          *lbl_11     = new QLabel("Длина: ", this);
    QSpinBox        *spb_1      = new QSpinBox(this);
                     spb_1->setRange(1, 10);
                     spb_1->setObjectName("spb_1");
    QLabel          *lbl_2      = new QLabel("Массив #2", this);
    QLabel          *lbl_21     = new QLabel("Длина: ", this);
    QSpinBox        *spb_2      = new QSpinBox(this);
                     spb_2->setRange(1, 10);
                     spb_2->setObjectName("spb_2");
    QPushButton     *pbt_1      = new QPushButton("Отсортировать/Соединить", this);                     
    connect(pbt_1,  &QPushButton::clicked,
            this,   &P_4_3_ArrayConcatenator::sortAndConcatenate);
                     m_result   = new QPlainTextEdit(this);
                     m_result->setReadOnly(true);

/*  Хотел реализовать ввод массивов через QTableWidget, но не разобрался, как
 *  ограничить тип вводимых данных исключительно числовыми значениями.
 *  По этому решил: буду корячиться с динамическими объектами типа QSpinBox
    */

    QGridLayout     *layout_top     = new QGridLayout();
                     layout_top->addWidget(lbl_1, 0, 0, 1, 2);
                     layout_top->addWidget(lbl_2, 0, 2, 1, 2);
                     layout_top->addWidget(lbl_11, 1, 0);
                     layout_top->addWidget(spb_1, 1, 1);
                     layout_top->addWidget(lbl_21, 1, 2);
                     layout_top->addWidget(spb_2, 1, 3);
                     layout_top->addWidget(pbt_1, 2, 0, 1, 4);

    /*QVBoxLayout*/  m_layout_left    = new QVBoxLayout();
    /*QVBoxLayout*/  m_layout_right   = new QVBoxLayout();

    // Без этих инструкций содержимое слоёв безобразно растягивается по всему окну
                     m_layout_left->setAlignment(Qt::AlignTop);
                     m_layout_right->setAlignment(Qt::AlignTop);

    connect(spb_1,  SIGNAL(valueChanged(int)),
            this,   SLOT(slotChangeArrayLength(int)));
    connect(spb_2,  SIGNAL(valueChanged(int)),
            this,   SLOT(slotChangeArrayLength(int)));

    // Обычно я такие вещи присваиваю, когда создаю виджеты
    // Но если сделать это сразу после подключения к слотам
    // они отреагируют на изменение величины и сами создадут
    // сетку с нужным количеством виджетов!
    // Это как автоматическая инициализация.
    spb_1->setValue(5);
    spb_2->setValue(5);

    // Ну и в конце компонуем всё в одну кучу
    QHBoxLayout     *layout_arrays    = new QHBoxLayout();
                     layout_arrays->addLayout(m_layout_left, 0);
                     layout_arrays->addLayout(m_layout_right, 0);

    QVBoxLayout     *layout_main    = new QVBoxLayout(this);
                     layout_main->addLayout(layout_top, 0);
                     layout_main->addLayout(layout_arrays, 1);
                     layout_main->addWidget(m_result, 2);
//                     layout_main->addWidget(MakingHtmlLink::getMyHtmlLabel(this), 0, Qt::AlignBottom);

}

// ==================== PUBLIC ====================

std::vector<int> P_4_3_ArrayConcatenator::concatenateSortedArrays
    (const std::vector<int> &arr1,
     const std::vector<int> &arr2)
{
    /* ==================== ПРИМЕЧАНИЕ ====================
     * Первое, что приходит в голову - это тупо склеить два
     * массива в один и отсортировать по-возрастанию.
     * Но так не интересно! И производительность пострадает.
     * Тем более, по условиям задачи, нам даны два УЖЕ
     * отсортированных массива. А значит процесс склеивания
     * можно оптимизировать, исключив сортировку. Главное
     * применить правильный алгоритм ;-)
     * */

    // Сначала берём два итератора и пустой вектор
    std::vector<int>::const_iterator it_1 = arr1.begin();
    std::vector<int>::const_iterator it_2 = arr2.begin();
    std::vector<int> result;

    // Создаём условие, при котором цикл будет работать
    // пока один из итераторов не достигнет конца
    while (it_1 != arr1.end() &&
           it_2 != arr2.end())
    {
        // Сравниваем значения
        *it_1 < *it_2 ?
                    // записываем наименьшее значение в итоговый
                    // массив одновременно перемещая соответствующий
                    // итератор на одну позицию
                    result.push_back(*(it_1++)) :
                    result.push_back(*(it_2++));
    }

    // Если цикл закончился, значит один из итераторов прошел
    // через весь массив. Осталось определить, в каком массиве
    // остался хвостик и докинуть его в конец.
    if(it_1 != arr1.end())
        result.insert(result.end(), it_1, arr1.end());
    else if (it_2 != arr2.end())
        result.insert(result.end(), it_2, arr2.end());
    else
        throw "Something goes wrong with those iterators";

    return result;
}

// ==================== СЛОТЫ ====================

void P_4_3_ArrayConcatenator::slotChangeArrayLength(int new_rows)
{
    QVBoxLayout *ptr_box;
    int add_to_new; // это чтобы новые элементы инициализировать красивым значением

    // Вот тут мы определяем, левый или правый слой нам нужно поменять
    // Основываемся на имени отправителя (присвоенному заранее)
    if(sender()->objectName() == "spb_1")
    {
        ptr_box = m_layout_left;
        add_to_new = 1;
    }
    else if (sender()->objectName() == "spb_2")
    {
        ptr_box = m_layout_right;
        add_to_new = 2;
    }
    else
        throw "UNINDEFINED SENDER!!!";  // a это чтобы жизнь мёдом не казалась

    if(new_rows > ptr_box->count())
    {
        QSpinBox *tmp_spb;

        for(int i = ptr_box->count(); i < new_rows; i++)
        {
            ptr_box->addWidget(new QSpinBox(this), 0, Qt::AlignTop);
            tmp_spb = (QSpinBox*)(ptr_box->itemAt(i)->widget());    // Явное преобразование
            //if(tmp_spb) // а эта херня всё равно не работает так, как я задумывал
                tmp_spb->setValue(i*2+add_to_new);
        }
    }
    if(new_rows < ptr_box->count())
    {
        QLayoutItem *tmp;
        for(int i = ptr_box->count(); i > new_rows; i--)
        {
            // Вот это я стырил из документации
            // (хорошо, что там был конкретный пример)
            tmp = ptr_box->takeAt(i-1);
            delete tmp->widget();
            delete tmp;
        }
    }
}

void P_4_3_ArrayConcatenator::sortAndConcatenate()
{
    // Вытряхиваем данные из SpinBox-ов, путём запихивания
    // содержащих их слоёв в заранее заготовленный метод
    m_arr1 = putNumbersToArray(m_layout_left);
    m_arr2 = putNumbersToArray(m_layout_right);

    // Сотрируем их стандартными методами
    std::sort(m_arr1.begin(), m_arr1.end());
    std::sort(m_arr2.begin(), m_arr2.end());

    // Для красоты, запихиваем данные обратно в SpinBox-ы.
    // А то вдруг пользователь забыл (а пользователь всегда
    // что-нибудь забывает), или не знал (как подсказывает
    // опыт, он обычно ничего и никогда знать не хочет)
    // что вводиться должны отсортированнные данные
    getNumbersFromArray(m_layout_left, m_arr1);
    getNumbersFromArray(m_layout_right, m_arr2);

    // Получаем склеенный вектор
    std::vector<int> result = concatenateSortedArrays(m_arr1, m_arr2);

    // Выводим отчёт
    QString pattern =   "Массив #1: %1\n"
                        "Массив #2: %2\n"
                        "Результат объединения:\n%3";

    m_result->setPlainText(pattern.arg(vectorToQString(m_arr1),
                                       vectorToQString(m_arr2),
                                       vectorToQString(result)));
}
