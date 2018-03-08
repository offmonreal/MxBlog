#include "db_Comments.h"

db_Comments::db_Comments(PGconn * pConnect)
{
    Table::setName("comments");
    FProperties * fk = new FProperties("key_comment", TF::SERIAL4);
    fk->PrimaryKey = true;
    Table::addProperties(fk);
    Table::addProperties(new FProperties("user_id", TF::Int4, 0, true, UI::FALSE));
    Table::addProperties(new FProperties("on_moderation", TF::Bool, 0, true, UI::FALSE,"false"));
    Table::addProperties(new FProperties("date_comment", TF::TimeStampTz));


    IConnect::setConnection(pConnect);
}

db_Comments::~db_Comments()
{
}

