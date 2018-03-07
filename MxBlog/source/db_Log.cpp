#include "db_Log.h"

db_Log::db_Log(PGconn * pConnect)
{
    Table::setName("log");
    FProperties * fk  = new FProperties("key_log", TF::SERIAL4);
    fk->PrimaryKey = true;
    Table::addProperties(fk);
    Table::addProperties(new FProperties("value_log", TF::VarChar, 1024));
    Table::addProperties(new FProperties("date_log", TF::TimeStamp));

    IConnect::setConnection(pConnect);
}

db_Log::~db_Log()
{
}

