#include "db_Catigories.h"

db_Catigories::db_Catigories(PGconn * pConnect)
{
    Table::setName("catigories");

    //First key
    FProperties * fk = new FProperties("key_catigories", TF::SERIAL4);
    fk->PrimaryKey = true;
    Table::addProperties(fk);
    //
    Table::addProperties(new FProperties("name", TF::VarChar, 255, true, MxSQL::UI::LOWER));
    Table::addProperties(new FProperties("children", TF::Int4, 0, true, MxSQL::UI::FALSE, "0"));
    Table::addProperties(new FProperties("seo_url", TF::VarChar, 255));


    IConnect::setConnection(pConnect);
}

db_Catigories::~db_Catigories()
{
}

