#include "logfile.h"

#include <QFile>
#include <QDateTime>
#include <QTextStream>

#include <QDir>

void LogFile::messageToFile(       QtMsgType           type,
                             const QMessageLogContext& context,
                             const QString&            msg)
{
    // Логи будут сохраняться в поддиректорию /log
    // Если она не существует - значит её надо создать!
    QString* log_dir = tryToCreateFolder();

    // Собираем имя файла по шаблону: Protocol-yyyy.MM.dd.log
    QString filename("log/Protocol-");
    filename += QDate::currentDate().toString("yyyy.MM.dd");
    filename += ".log";

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        delete log_dir;
        return; // если не открывается - ничего не поделаешь!
    }

    QString strDateTime = QDateTime::currentDateTime().toString("dd.MM.yy-hh:mm");

    QTextStream out (&file);

    // если папку пришлось создавать - надо об этом упомянуть!
    if(log_dir)
    {
        out << strDateTime << *log_dir << Qt::endl;
        delete log_dir; // без неё мне даже креатор носом ткнул на потенциальную утечку памяти!
    }

    out << strDateTime; // не люблю дублировать код.
    switch (type)
    {
    // Если ошибка фатальная - выводим тупо всё сообщение и закрываемся
    case QtFatalMsg:        
        out << "FATAL: " << msg
            << ", " << context.file << Qt::endl;
        abort();

    // Если ошибка не фатальная - начинаем изощряться,
    // а именно, сначала выводим только тип сообщения...

    case QtInfoMsg:     out << " Info: ";        break;
    case QtDebugMsg:    out << " Debug: ";       break;
    case QtWarningMsg:  out << " Warning: ";     break;
    case QtCriticalMsg: out << " Critical: ";    break;
    }

    //...и только потом всё остальное содержимое
    out  << msg << ", " << context.file << Qt::endl;
}

QString* LogFile::tryToCreateFolder()
{
    QDir *log_dir = new QDir();
    if(!log_dir->exists("log"))
    {
        log_dir->mkdir("log");
        // понятия не имею, удалится ли объект автоматически.
        // Лучше перестраховаться!
        delete log_dir;

        return new QString(
                    "\n==================================================================="
                    "\nWARNING:\n"
                    "A log-folder was just created!\n"
                    "There is a possibility that the old log-folder has been deleted\n"
                    "===================================================================\n"
                    );
    }
    else
    {
        // понятия не имею, удалится ли объект автоматически.
        // Лучше перестраховаться!
        delete log_dir;
        return nullptr;
    }
}
