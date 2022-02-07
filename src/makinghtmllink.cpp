#include "makinghtmllink.h"

#include <QObject>
#include <QString>
#include <QLabel>
#include <QDebug>

const QString MakingHtmlLink::m_pattern_name = "Часть №%1: Практические задания по С++";
const QString MakingHtmlLink::m_pattern_link = "https://ravesli.com/praktika-chast-%1";
const QString MakingHtmlLink::m_pattern_html = "<a href=\"%1\">"
                                               "<div>Страница на Ravesli.com</div>"
                                               "<div>%2</div></a>";

QString MakingHtmlLink::getMyHtmlLink(QWidget *obj)
{
    qDebug() << "Making HTML-link for " << obj->objectName();

    // Вытаскиваем имя объекта
    QString temp_objectName = obj->objectName();
    qDebug() << "Cathed name: " << temp_objectName;

    // конвертируем имя в int
    int number = temp_objectName.toInt();
    qDebug() << "Converted to " << number;

    // Последняя цифра - номер задания. Выкидываем!
    number = number / 10;
    qDebug () << "Dividing by 10: " << number;

    // Если имя присвоено верно, значит оно должно
    // быть в диапазоне от 1 до 24 включительно
    if(number > 24 || number < 1)
        throw "There is error in objectName()"; // это чтобы жизнь мёдом не казалась

    // Мне очень понравился метод QString::arg()
    // Он даже с HTML работает как мне надо!
    QString name = m_pattern_name.arg(number);
    QString link = m_pattern_link.arg(number);
    QString result = m_pattern_html.arg(link, name);

    return result;
}

QLabel* MakingHtmlLink::getMyHtmlLabel(QWidget *obj)
{
    QLabel *tmp = new QLabel(getMyHtmlLink(obj), obj);
    tmp->setOpenExternalLinks(true);

    return tmp;
}
