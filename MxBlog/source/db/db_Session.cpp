#include "db_Session.h"

db_Session::db_Session(PGconn * pConnect)
{
    Table::setName("session");
    user_id = new FProperties("user_id", TF::Int4);
    session_id = new FProperties("session_id", TF::VarChar, 39, true, MxSQL::UI::LOWER);
    date_expired = new FProperties("date_expired", TF::TimeStampTz, 0, true);
    value_cookie = new FProperties("value_cookie", TF::VarChar, 32);
    ip_address = new FProperties("ip_address", TF::VarChar, 15);

    Table::addProperties(user_id);
    Table::addProperties(session_id);
    Table::addProperties(date_expired);
    Table::addProperties(value_cookie);
    Table::addProperties(ip_address);

    IConnect::setConnection(pConnect);
}

db_Session::~db_Session()
{
}

