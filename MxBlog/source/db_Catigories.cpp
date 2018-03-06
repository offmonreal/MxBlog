#include "db_Catigories.h"

db_Catigories::db_Catigories(PGconn * pConnect)
{
    Table::setName("catigories_test");

    //First key
    FProperties * fk = new FProperties("key_catigories", MxSQL::SERIAL8);
    fk->PrimaryKey = true;
    Table::addProperties(fk);
    //
    Table::addProperties(new FProperties("name", MxSQL::VarChar, 255, true, true));
    Table::addProperties(new FProperties("children", MxSQL::Int4, 0, true, false, "0"));
    Table::addProperties(new FProperties("seo_url", MxSQL::VarChar, 255));


    IConnect::setConnection(pConnect);
}

db_Catigories::~db_Catigories()
{
}

