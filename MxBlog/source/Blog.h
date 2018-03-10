#ifndef BLOG_H
#define BLOG_H

#include "includes.h"
#include "defines.h"

#include "StartPG.h"
#include "InstallPG.h"
#include "XW.h"
#include "MxSql.h"
#include "enums.h"

using namespace XW;
using namespace MxSQL;

class Blog
{
public:
    int maximum_connect; //Максимум клиентов подключенных
private:
    //Web server
    XWeb * xw;
public:
    Blog();
public:
    bool findeBase(); //Поиск и проверка БД
public:
    void init();
    bool start(BLOG_START as = BLOG_START::AS_CONSOLE);
    void stop();
public:
    //Запись лога  
    static void writeLog(string value);
    // функция обработки сигналов
    static void signal_error(int sig, siginfo_t *si, void *ptr);
    ~Blog();
private:

};

#endif /* BLOG_H */

