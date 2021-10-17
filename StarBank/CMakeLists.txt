cmake_minimum_required(VERSION 3.17)
project(StarBankATM_MOOP_KMA)


set(CMAKE_CXX_STANDARD 14)


add_executable(StarBankATM_MOOP_KMA Main.cpp models/accounts/AccountOld.h ATM.h CashDispencer.h CardScanner.h SessionManager.h models/User.h
        models/Transaction.cpp models/Transaction.h models/accounts/Account.h models/accounts/Account.cpp Storage.h Storage.cpp ATM.cpp CardScanner.cpp
        CashDispencer.cpp SessionManager.cpp models/User.cpp models/accounts/AccountOld.cpp models/accounts/CreditAccount.cpp models/accounts/CreditAccount.h
        models/accounts/DepositAccount.cpp models/accounts/DepositAccount.h models/accounts/UniversalAccount.cpp models/accounts/UniversalAccount.h
        models/UserOld.h models/UserOld.cpp DBService/UserService.h DBService/TransactionService.h DBService/AccountService.h models/ATM.h models/ATM.cpp)



add_compile_options(-l sqlite3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lsqlite3")
