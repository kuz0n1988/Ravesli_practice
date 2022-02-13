QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    logfile.cpp \
    main.cpp \
    makinghtmllink.cpp \
    p_1_1_sandwich.cpp \
    p_1_2_minnumber.cpp \
    p_1_3_timeoftheyear.cpp \
    p_2_1_dacha.cpp \
    p_2_2_discount.cpp \
    p_2_3_guessthenumber.cpp \
    p_3_1_speedrunner.cpp \
    p_3_2_positiveevenintsum.cpp \
    p_3_3_morsecode.cpp \
    p_4_1_versta.cpp \
    p_4_2_averageofdoublearray.cpp \
    p_4_3_arrayconcatenator.cpp \
    p_5_1_minutestohours.cpp \
    p_5_2_pricetable.cpp \
    p_5_3_timersignal.cpp \
    practice.cpp

HEADERS += \
    logfile.h \
    makinghtmllink.h \
    p_1_1_sandwich.h \
    p_1_2_minnumber.h \
    p_1_3_timeoftheyear.h \
    p_2_1_dacha.h \
    p_2_2_discount.h \
    p_2_3_guessthenumber.h \
    p_3_1_speedrunner.h \
    p_3_2_positiveevenintsum.h \
    p_3_3_morsecode.h \
    p_4_1_versta.h \
    p_4_2_averageofdoublearray.h \
    p_4_3_arrayconcatenator.h \
    p_5_1_minutestohours.h \
    p_5_2_pricetable.h \
    p_5_3_timersignal.h \
    practice.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
