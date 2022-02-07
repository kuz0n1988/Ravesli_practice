/* ===========Ravesli.com===========
 * Практические задания по С++
 * Точнее - это тот говнокод, который
 * у меня получился в процессе решения
 * этих самых задач */

#include "practice.h"
#include "logfile.h"    // Самописьная библеотека для логов

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    qInstallMessageHandler(LogFile::messageToFile); // крепим логгирование в файл

    Practice w;
    w.setWindowTitle("Ravesli.com - практические задания по C++");
    w.setWindowIcon(QIcon(":/ico/main"));
    w.resize(450, 300);

    w.show();
    return a.exec();
}
