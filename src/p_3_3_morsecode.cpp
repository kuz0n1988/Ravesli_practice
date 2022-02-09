#include "p_3_3_morsecode.h"

#include <string>
#include <iostream>
#include <cstdint>
#include <windows.h>    // для пищалки

#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QChar>
#include <QValidator>
#include <QRegExp>

#include <QDebug>

#include "makinghtmllink.h"

/* ======== НЕМНОГО О МАГИИ КЛАССА QValidator ========
 * Очень хочтелось опробовать, как работает валидатор в Qt
 * Три часа возни к RegExp (потому что я всё ещё плохо
 * умею в регулярные выражения), периодические возгласы
 * "почему же ты, сука, не хочешь работать" и о чудо -
 * ОНО РАБОТАЕТ!!! Причём именно так, как я хотел!
 * К сожалению, я не совсем понимаю КАК оно работает!
 * */

class StringValidator : public QValidator
{
public:
    StringValidator(QObject *parent = nullptr) : QValidator(parent)
    {}

    virtual State validate(QString &str, int &pos) const
    {
        Q_UNUSED(pos)

        QRegExp rxp = QRegExp("[^А-яЁё ]");
        if(str.contains(rxp))
            return Invalid;

        return Acceptable;
    }
};

//  ==================ПОДСКАЗКА==================
/*  А	·−      Б	−···	В	·−−     Г	−−·
    Д	−··     Е	·       Ж	···−	З	−−··
    И	··      Й	·−−−	К	−·−     Л	·−··
    М	−−      Н	−·      О	−−−     П	·−−·
    Р	·−·     С	···     Т	−       У	··−
    Ф	··−·	Х	····	Ц	−·−·	Ч	−−−·
    Ш	−−−−	Щ	−−·−	Ъ	·−−·−·	Ы	−·−−
    Ь	−··−	Э	··−··	Ю	··−−	Я	·−·− */
//  ==================ПОДСКАЗКА==================

const std::array<std::string, 36> P_3_3_MorseCode::M_ABC_MORSE =
    {"·−",      "−···",     "·−−",      "−−·",      // А-0,     Б-1,    В-2,    Г-3
     "−··",     "·",        "···−",     "−−··",     // Д-4,     Е,Ё-5,  Ж-6,    З-7
     "··",      "·−−−",     "−·−",      "·−··",     // И-8,     Й-9,    К-10,   Л-11
     "−−",      "−·",       "−−−",      "·−−·",     // М-12,    Н-13,   О-14,   П-15
     "·−·",     "···",      "−",        "··−",      // Р-16,    С-17,   Т-18,   У-19
     "··−·",    "····",     "−·−·",     "−−−·",     // Ф-20,    Х-21,   Ц-22,   Ч-23
     "−−−−",    "−−·−",     "·−−·−·",   "−·−−",     // Ш-24,    Щ-25,   Ъ-26,   Ы-27
     "−··−",    "··−··",    "··−−",     "·−·−"      // Ь-28,    Э-29,   Ю-30,   Я-31
    };

P_3_3_MorseCode::P_3_3_MorseCode(QWidget *parent) : QWidget(parent)
{
    setObjectName("33");

    QLabel      *lbl_title  = new QLabel("Введите текст:", this);
    QLineEdit   *led_input  = new QLineEdit(this);

    // *****МАГИЯ*****
    StringValidator *validator  = new StringValidator(led_input);
    led_input->setValidator(validator);
    // *****МАГИЯ*****

                 m_morse    = new QPlainTextEdit(this);
                 m_morse->setReadOnly(true);
                 connect(led_input,  &QLineEdit::textEdited,
                         this,       &P_3_3_MorseCode::slotConvertToMorse);

    QPushButton *pbt_beep   = new QPushButton("Воспроизвести код через динамик", this);

    connect(pbt_beep,   &QPushButton::clicked,
            this,       &P_3_3_MorseCode::slotBeepTheMorse);

    QVBoxLayout *layout_main = new QVBoxLayout(this);
                 layout_main->addWidget(lbl_title);
                 layout_main->addWidget(led_input);
                 layout_main->addWidget(m_morse, 5, Qt::AlignTop);
                 layout_main->addWidget(pbt_beep);
                 layout_main->addWidget(MakingHtmlLink::getMyHtmlLabel(this), 1, Qt::AlignBottom);
}

std::string P_3_3_MorseCode::getMorseCode(const std::wstring &source)
{
    // собирать морзянку будем сюда
    std::string morse = "";

    // чтобы не создавать wchar каждый цикл - объявим переменную сразу.
    int temp;
    int length = static_cast<int>(source.length());

    for(int i = 0; i < length; i++)
    {
        temp = static_cast<wchar_t>(source[i]);

        // Для заглавных букв (диапазон в UTF-16: 1040-1071)
        if (temp > 1039 && temp < 1072)
            morse += M_ABC_MORSE[temp - 1040] + " ";

        // Для прописных букв (диапазон в UTF-16: 1072-1103)
        if (temp > 1071 && temp < 1104)
            morse += M_ABC_MORSE[temp - 1072];

        // Отдельный пункт для обрабокти буквы 'Ё' или 'ё'
        if(static_cast<int>(temp) == 1025 ||    // Ё
           static_cast<int>(temp) == 1105)      // ё
            morse += M_ABC_MORSE[5];

        /*  То что я наваял ниже - самый настоящий индусский говнокод
         *  Есть более изящное решение: преобразовать wchar_t в int
         *  отнять от него магическое число и подставить в качестве
         *  индекса в M_ABC_MORSE
         *  Удалять не стал - закомментировал на память
         * */

        /*
        // А-0
        if      (temp == L'А' || temp == L'а')
            morse += M_ABC_MORSE[0];
        // Б-1
        if      (temp == L'Б' || temp == L'б')
            morse += M_ABC_MORSE[1];
        // В-2
        if      (temp == L'В' || temp == L'в')
            morse += M_ABC_MORSE[2];
        // Г-3
        if      (temp == L'Г' || temp == L'г')
            morse += M_ABC_MORSE[3];
        // Д-4
        if      (temp == L'Д' || temp == L'д')
            morse += M_ABC_MORSE[4];
        // Е,Ё-5
        if      (temp == L'Е' || temp == L'е' || temp == L'ё'|| temp == L'Ё')
            morse += M_ABC_MORSE[5];
        // Ж-6
        if      (temp == L'Ж' || temp == L'ж')
            morse += M_ABC_MORSE[6];
        // З-7
        if      (temp == L'З' || temp == L'з')
            morse += M_ABC_MORSE[7];
        // И-8
        if      (temp == L'И' || temp == L'и')
            morse += M_ABC_MORSE[8];
        // Й-9
        if      (temp == L'Й' || temp == L'й')
            morse += M_ABC_MORSE[9];
        // К-10
        if      (temp == L'К' || temp == L'к')
            morse += M_ABC_MORSE[10];
        // Л-11
        if      (temp == L'Л' || temp == L'л')
            morse += M_ABC_MORSE[11];
        // М-12
        if      (temp == L'М' || temp == L'м')
            morse += M_ABC_MORSE[12];
        // Н-13
        if      (temp == L'Н' || temp == L'н')
            morse += M_ABC_MORSE[13];
        // О-14
        if      (temp == L'О' || temp == L'о')
            morse += M_ABC_MORSE[14];
        // П-15
        if      (temp == L'П' || temp == L'п')
            morse += M_ABC_MORSE[15];
        // Р-16
        if      (temp == L'Р' || temp == L'р')
            morse += M_ABC_MORSE[16];
        // С-17
        if      (temp == L'С' || temp == L'с')
            morse += M_ABC_MORSE[17];
        // Т-18
        if      (temp == L'Т' || temp == L'т')
            morse += M_ABC_MORSE[18];
        // У-19
        if      (temp == L'У' || temp == L'у')
            morse += M_ABC_MORSE[19];
        // Ф-20
        if      (temp == L'Ф' || temp == L'ф')
            morse += M_ABC_MORSE[20];
        // Х-21
        if      (temp == L'Х' || temp == L'х')
            morse += M_ABC_MORSE[21];
        // Ц-22
        if      (temp == L'Ц' || temp == L'ц')
            morse += M_ABC_MORSE[22];
        // Ч-23
        if      (temp == L'Ч' || temp == L'ч')
            morse += M_ABC_MORSE[23];
        // Ш-24
        if      (temp == L'Ш' || temp == L'ш')
            morse += M_ABC_MORSE[24];
        // Щ-25
        if      (temp == L'Щ' || temp == L'щ')
            morse += M_ABC_MORSE[25];
        // Ъ-26
        if      (temp == L'Ъ' || temp == L'ъ')
            morse += M_ABC_MORSE[26];
        // Ы-27
        if      (temp == L'Ы' || temp == L'ы')
            morse += M_ABC_MORSE[27];
        // Ь-28
        if      (temp == L'Ь' || temp == L'ь')
            morse += M_ABC_MORSE[28];
        // Э-29
        if      (temp == L'Э' || temp == L'э')
            morse += M_ABC_MORSE[29];
        // Ю-30
        if      (temp == L'Ю' || temp == L'ю')
            morse += M_ABC_MORSE[30];
        // Я-31
        if      (temp == L'Я' || temp == L'я')
            morse += M_ABC_MORSE[31];
            */
    }

    return morse;
}

void P_3_3_MorseCode::slotConvertToMorse(const QString& source)
{
    // Поскольку алгоритм реализован стандартными средствами С++
    // тут будет много возни с преобразованием типов

    // Сначала преобразуем QString в std::wstring;
    std::wstring temp = source.toStdWString();

    // потом получаем морзянку std::string из статической функции getMorseCode
    std::string  s_morse = getMorseCode(temp);

    // После преобразуем морзянку из std::string в QString
    QString      q_morse = QString::fromStdString(s_morse);

    /* Этот алгоритм больше не нужен, поскольку я решил
     * добавлять после каждой буквы символ пробела
    for(int i = 10; i < q_morse.size(); i = i + 10)
        q_morse.insert(i, '\n');
    */

    // И только потом пихаем всё это счастье в поле для вывода
    m_morse->setPlainText(q_morse);
}

void P_3_3_MorseCode::slotBeepTheMorse()
{
    const QChar beep_long   = L'−';
    const QChar beep_short  = L'·';

    QString the_code = m_morse->toPlainText();
    int     length   = the_code.length();

    for(int i = 0; i < length; i++)
    {
        if(the_code[i] == beep_long)
            Beep(1000, 500);
        else if(the_code[i] == beep_short)
            Beep(1000, 200);
        /* После добавления валидатора эта хрень больше не нужна
        else if(the_code[i] != ' ')
            Beep(300, 5000);
            */
    }
}
