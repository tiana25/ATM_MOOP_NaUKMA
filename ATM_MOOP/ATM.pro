QT += core gui sql
# set PROJECT_PATH to the "project path" with a trailing slash
DEFINES += PROJECT_PATH=\"\\\"$${_PRO_FILE_PWD_}/\\\"\"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    AccountsService.cpp \
    CasseteDB.cpp \
    SessionManager.cpp \
    TransactionService.cpp \
    UserService.cpp \
    main.cpp \
    mainwindow.cpp \
    menuwindow.cpp \
    menuwindowcredit.cpp \
    menuwindowdeposit.cpp \
    passwordwindow.cpp \
    putmoneytoanotheraccount.cpp \
    putmoneytomyaccount.cpp \
    putmoneywindow.cpp \
    question.cpp \
    setlimitwindow.cpp \
    transactionhistorywindow.cpp \
    withdrawalwindow.cpp\
    ATMdata/ATMSources/Account.cpp\
    ATMdata/ATMSources/CreditAccount.cpp\
    ATMdata/ATMSources/DepositAccount.cpp\
    ATMdata/ATMSources/UniversalAccount.cpp\
    ATMdata/ATMSources/Transaction.cpp\
    ATMdata/ATMSources/User.cpp\

HEADERS += \
    AccountsService.h \
    CasseteDB.h \
    DBPath.h \
    SessionManager.h \
    TransactionService.h \
    UserService.h \
    mainwindow.h \
    menuwindow.h \
    menuwindowcredit.h \
    menuwindowdeposit.h \
    passwordwindow.h \
    putmoneytoanotheraccount.h \
    putmoneytomyaccount.h \
    putmoneywindow.h \
    question.h \
    setlimitwindow.h \
    transactionhistorywindow.h \
    withdrawalwindow.h\
    ATMdata/ATMHeaders/accounts/Account.h\
    ATMdata/ATMHeaders/accounts/CreditAccount.h\
    ATMdata/ATMHeaders/accounts/DepositAccount.h\
    ATMdata/ATMHeaders/accounts/UniversalAccount.h\
    ATMdata/ATMHeaders/Transaction.h\
    ATMdata/ATMHeaders/User.h\
FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainwindow.ui \
    menuwindow.ui \
    menuwindowcredit.ui \
    menuwindowdeposit.ui \
    passwordwindow.ui \
    putmoneytoanotheraccount.ui \
    putmoneytomyaccount.ui \
    putmoneywindow.ui \
    question.ui \
    setlimitwindow.ui \
    transactionhistorywindow.ui \
    withdrawalwindow.ui

DISTFILES += \
    ATM.db
