#include "db_PostStatus.h"

db_PostStatus::db_PostStatus(PGconn * pConnect)
{
    Table::setName("post_status");

    //First key
    fk = new FProperties("key_post_status", TF::SERIAL4);
    fk->PrimaryKey = true;

    parameter = new FProperties("parameter", TF::VarChar, 15, true, MxSQL::UI::LOWER);
    description = new FProperties("description", TF::VarChar, 255);

    Table::addProperties(fk);
    Table::addProperties(parameter);
    Table::addProperties(description);

    IConnect::setConnection(pConnect);
}

db_PostStatus::~db_PostStatus()
{
}

