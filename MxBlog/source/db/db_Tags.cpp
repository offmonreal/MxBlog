#include "db_Tags.h"

db_Tags::db_Tags(PGconn * pConnect)
{
    Table::setName("tags");
    FProperties * fk = new FProperties("key_tags", TF::SERIAL4);
    fk->PrimaryKey = true;

    tag_value = new FProperties("tag_value", TF::VarChar, 25, true, UI::LOWER);

    Table::addProperties(fk);
    Table::addProperties(tag_value);

    IConnect::setConnection(pConnect);
}

db_Tags::~db_Tags()
{
}

