#include "db_Log.h"

db_Log::db_Log(PGconn * pConnect)
{
    Table::setName("log");
    FProperties * fk = new FProperties("key_log", TF::SERIAL4);
    fk->PrimaryKey = true;

    value_log = new FProperties("value_log", TF::VarChar, 1024);
    date_log = new FProperties("date_log", TF::TimeStampTz);

    Table::addProperties(fk);
    Table::addProperties(value_log);
    Table::addProperties(date_log);

    IConnect::setConnection(pConnect);
}

db_Log::~db_Log()
{
}

