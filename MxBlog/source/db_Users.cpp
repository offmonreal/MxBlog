#include "db_Users.h"

db_Users::db_Users(PGconn * pConnect)
{
    Table::setName("users");
    fk = new FProperties("key_user", TF::SERIAL4);
    fk->PrimaryKey = true;
    Table::addProperties(fk);

    nick_name = new FProperties("nick_name", TF::VarChar, 25, true, UI::LOWER);
    password = new FProperties("password", TF::VarChar, 32, true);
    email = new FProperties("email", TF::VarChar, 32, true, UI::LOWER);
    access = new FProperties("access", TF::Int4, 0, true, UI::FALSE, "3"); //3=Reader
    locked = new FProperties("locked", TF::Bool, 0, true, UI::FALSE, "false");
    date_create = new FProperties("date_create", TF::TimeStampTz, 0, true);
    subscribe = new FProperties("subscribe", TF::Bool, 0, true, UI::FALSE, "true");


    Table::addProperties(nick_name);
    Table::addProperties(password);
    Table::addProperties(email);
    Table::addProperties(access);
    Table::addProperties(locked);
    Table::addProperties(date_create);
    Table::addProperties(subscribe);


    IConnect::setConnection(pConnect);
}

db_Users::~db_Users()
{
}

