#include "db_Catigories.h"

db_Catigories::db_Catigories(PGconn * pConnect)
{
    Table::setName("catigories");

    //First key
    fk = new FProperties("key_catigories", TF::SERIAL4);
    fk->PrimaryKey = true;
    Table::addProperties(fk);
    //
    name_category = new FProperties("name_category", TF::VarChar, 255, true, MxSQL::UI::LOWER);
    children_category = new FProperties("children_category", TF::Int4, 0, true, MxSQL::UI::FALSE, "0");
    seo_url = new FProperties("seo_url", TF::VarChar, 255);


    Table::addProperties(name_category);
    Table::addProperties(children_category);
    Table::addProperties(seo_url);

    IConnect::setConnection(pConnect);
}

db_Catigories::~db_Catigories()
{
}

