#ifndef LOGFILE_H
#define LOGFILE_H

#include <QtGlobal>

class LogFile
{

public:
    // Логи будут сохраняться в поддиректорию /log/
    // Имя файла: Protocol-yy.MM.dd.log
    static void messageToFile(      QtMsgType           type,
                              const QMessageLogContext& context,
                              const QString&            msg);
private:
    static QString* tryToCreateFolder();
    // оно будет проверять и создавать папку /log/
    // Если папка существует - возвращает nullptr
    // Если папка не существует - возвращает строку
};

#endif // LOGFILE_H
