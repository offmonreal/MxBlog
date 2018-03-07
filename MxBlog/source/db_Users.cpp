#include "db_Users.h"

db_Users::db_Users(PGconn * pConnect)
{
    Table::setName("users");
    FProperties * fk = new FProperties("key_user", TF::SERIAL4);
    fk->PrimaryKey = true;
    Table::addProperties(fk);

    Table::addProperties(new FProperties("nick_name", TF::VarChar, 25, true, UI::LOWER));
    Table::addProperties(new FProperties("password", TF::VarChar, 32, true));
    Table::addProperties(new FProperties("email", TF::VarChar, 32, true, UI::LOWER));
    Table::addProperties(new FProperties("role", TF::Int4, 0, true, UI::FALSE, "0"));
    Table::addProperties(new FProperties("locked", TF::Bool, 0, true, UI::FALSE, "false"));
    Table::addProperties(new FProperties("date_create", TF::TimeStamp, 0, true));
    Table::addProperties(new FProperties("subscribe", TF::Bool, 0, true, UI::FALSE, "true"));


    IConnect::setConnection(pConnect);
}

db_Users::~db_Users()
{
}

