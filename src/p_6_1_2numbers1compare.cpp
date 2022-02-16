#include "p_6_1_2numbers1compare.h"

#include <QLCDNumber>
#include <QLabel>
#include <QHBoxLayout>
#include <QSlider>

#include <QDebug>

P_6_1_2Numbers1Compare::P_6_1_2Numbers1Compare(QWidget *parent) : QWidget(parent)
{
    QLCDNumber  *lcd_first      = new QLCDNumber(2, this);
                 m_sld_first    = new QSlider(Qt::Vertical, this);
                 m_sld_first->setRange(0, 99);
                 m_lbl_compare    = new QLabel("=",this);
                 m_lbl_compare->setFont(QFont("sans-serif", 48));
    QLCDNumber  *lcd_second     = new QLCDNumber(2, this);
                 m_sld_second   = new QSlider(Qt::Vertical, this);
                 m_sld_second->setRange(0, 99);

    connect(m_sld_first,    SIGNAL(valueChanged(int)), lcd_first,   SLOT(display(int)));
    connect(m_sld_second,   SIGNAL(valueChanged(int)), lcd_second,  SLOT(display(int)));
    connect(m_sld_first,    SIGNAL(valueChanged(int)), this,        SLOT(slotCompare()));
    connect(m_sld_second,   SIGNAL(valueChanged(int)), this,        SLOT(slotCompare()));

    // Вместо инициализации
    // Значения по-умолчанию ставим как в примере
    m_sld_first->setValue(48);
    m_sld_second->setValue(54);

    QHBoxLayout *layout_main    = new QHBoxLayout(this);
                 layout_main->addWidget(lcd_first);
                 layout_main->addWidget(m_sld_first);
                 layout_main->addWidget(m_lbl_compare, 0, Qt::AlignCenter);
                 layout_main->addWidget(lcd_second);
                 layout_main->addWidget(m_sld_second);
}

void P_6_1_2Numbers1Compare::slotCompare()
{

    if(m_sld_first->value() < m_sld_second->value())
        m_lbl_compare->setText("<");
    else if(m_sld_first->value() > m_sld_second->value())
        m_lbl_compare->setText(">");
    else
        m_lbl_compare->setText("=");
}
