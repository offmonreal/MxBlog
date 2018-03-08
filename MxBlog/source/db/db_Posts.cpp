#include "db_Posts.h"

db_Posts::db_Posts(PGconn * pConnect)
{
    Table::setName("posts");

    fk = new FProperties("key_post", TF::SERIAL4);
    fk->PrimaryKey = true;

    
    title = new FProperties("title", TF::VarChar, 255, false);
    body_preview = new FProperties("body_preview", TF::VarChar, 2500);
    body_addon = new FProperties("body_addon", TF::VarChar, 10000);
    user_id = new FProperties("user_id", TF::Int4, 0, true, UI::FALSE);
    status_id = new FProperties("status_id", TF::Int4, 0, true, UI::FALSE);
    start_date = new FProperties("start_date", TF::TimeStampTz, 0, true);
    create_date = new FProperties("create_date", TF::TimeStampTz, 0, true);
    access_level = new FProperties("access_level", TF::Int4, 0, true, UI::FALSE, "5");
    relation_categories = new FProperties("relation_categories", TF::Int4);
    relation_tag = new FProperties("relation_tag", TF::Int4);
    seo_url = new FProperties("seo_url", TF::VarChar, 255);
    fixed = new FProperties("fixed", TF::Bool, 0, true, UI::FALSE, "false");
    image_url = new FProperties("image_url", TF::VarChar, 255);


    Table::addProperties(fk);
    Table::addProperties(title);
    Table::addProperties(body_preview);
    Table::addProperties(body_addon);
    Table::addProperties(user_id);
    Table::addProperties(status_id);
    Table::addProperties(start_date);
    Table::addProperties(create_date);
    Table::addProperties(access_level);
    Table::addProperties(relation_categories);
    Table::addProperties(relation_tag);
    Table::addProperties(seo_url);
    Table::addProperties(fixed);
    Table::addProperties(image_url);


    IConnect::setConnection(pConnect);
}

db_Posts::~db_Posts()
{
}

