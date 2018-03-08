#include "db_Session.h"

db_Session::db_Session(PGconn * pConnect)
{
    Table::setName("session");
    Table::addProperties(new FProperties("user_id", TF::Int4));
    Table::addProperties(new FProperties("session_id", TF::VarChar, 32));
    Table::addProperties(new FProperties("date_expired", TF::TimeStampTz, 0, true));
    Table::addProperties(new FProperties("value_cookie", TF::VarChar, 32));
    Table::addProperties(new FProperties("ip_address", TF::VarChar, 15));
    
    IConnect::setConnection(pConnect);
}

db_Session::~db_Session()
{
}

