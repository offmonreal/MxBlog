#include "db_Posts.h"

db_Posts::db_Posts(PGconn * pConnect)
{
    Table::setName("posts");
    FProperties * fk = new FProperties("key_post", TF::SERIAL4);
    fk->PrimaryKey = true;
    Table::addProperties(fk);
    Table::addProperties(new FProperties("title", TF::VarChar, 255, false));
    Table::addProperties(new FProperties("body_preview", TF::VarChar, 2500));
    Table::addProperties(new FProperties("body_addon", TF::VarChar, 10000));
    Table::addProperties(new FProperties("user_id", TF::Int4, 0, true, UI::FALSE));
    Table::addProperties(new FProperties("status_id", TF::Int4, 0, true, UI::FALSE));
    Table::addProperties(new FProperties("start_date", TF::TimeStampTz, 0, true));
    Table::addProperties(new FProperties("create_date", TF::TimeStampTz, 0, true));
    Table::addProperties(new FProperties("access_level", TF::Int4, 0, true, UI::FALSE, "5"));
    Table::addProperties(new FProperties("categories", TF::Int4));
    Table::addProperties(new FProperties("tags", TF::Int4));
    Table::addProperties(new FProperties("seo_url", TF::VarChar, 255));
    Table::addProperties(new FProperties("fixed", TF::Bool, 0, true, UI::FALSE, "false"));
    Table::addProperties(new FProperties("image_url", TF::VarChar, 255));
    
    
    IConnect::setConnection(pConnect);
}

db_Posts::~db_Posts()
{
}

