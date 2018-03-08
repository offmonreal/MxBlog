#include "db_Categories.h"

db_Categories::db_Categories(PGconn * pConnect)
{
    Table::setName("categories");

    //First key
    fk = new FProperties("key_categories", TF::SERIAL4);
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

db_Categories::~db_Categories()
{
}

