#include "p_4_3_arrayconcatenator.h"

#include <QtWidgets>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "makinghtmllink.h"

std::vector<int> P_4_3_ArrayConcatenator::putNumbersToArray(const QVBoxLayout* layout)
{
    /*  ========== ПРИМЕЧАНИЕ ==========
     * хотел использовать QLayoutIterator,
     * но он оказывается устаревший :(
     * */

    qDebug() << "Start putting";
    std::vector<int> temp;

    QSpinBox *tmp_spb;
    for(int i = layout->count(); i < layout->count(); i++)
    {
        /* По идее, тут должна быть проверка типа и при невозможности
         * конвертации выбрасывать исключение
         * */
        qDebug() << "Iteration " << i;
        tmp_spb = (QSpinBox*)(layout->itemAt(i)->widget());    // Явное преобразование
        temp.push_back(tmp_spb->value());
    }
    return temp;
    qDebug() << "Finish putting";
}

P_4_3_ArrayConcatenator::P_4_3_ArrayConcatenator(QWidget *parent) : QWidget(parent)
{
    setObjectName("43");

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
                     m_result   = new QPlainTextEdit(this);

/*  Хотел реализовать ввод массивов через QTableWidget, но не разобрался, как
 *  ограничить тип вводимых данных исключительно числовыми значениями.
 *  По этому решил: буду корячиться с динамическими объектами типа QSpinBox
    QTableWidget    *qtw_1  = new QTableWidget(5, 1, this);
    qtw_1->setHorizontalHeaderLabels({"Первый ряд"});
    QTableWidget    *qtw_2  = new QTableWidget(5, 1, this);
    qtw_2->setHorizontalHeaderLabels({"Второй ряд"});
    */

    // Вот тут я хотел напрямую соединить сигнал QSPinBox::valueChanged
    // с QTableWidget::setColumnCount, но последний оказалось не слот!

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

    QHBoxLayout     *layout_arrays    = new QHBoxLayout();
                     layout_arrays->addLayout(m_layout_left, 0);
                     layout_arrays->addLayout(m_layout_right, 0);

    QVBoxLayout     *layout_main    = new QVBoxLayout(this);
                     layout_main->addLayout(layout_top, 0);
                     layout_main->addLayout(layout_arrays, 1);
//                     layout_main->addStretch(2);
                     layout_main->addWidget(m_result, 1, Qt::AlignBottom);
                     layout_main->addWidget(MakingHtmlLink::getMyHtmlLabel(this), 1, Qt::AlignBottom);

    //  ==========ТЕСТ==========
    m_arr1 = putNumbersToArray(m_layout_left);
    m_arr2 = putNumbersToArray(m_layout_right);

    qDebug () << m_arr1 << Qt::endl << m_arr2;
}

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

    qDebug () << ptr_box->count();

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
