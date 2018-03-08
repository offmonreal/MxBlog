#include "db_CategoriesRelation.h"

db_CategoriesRelation::db_CategoriesRelation(PGconn * pConnect)
{
    Table::setName("categories_relation");

    fk = new FProperties("key_categories_relation", TF::SERIAL4);
    fk->PrimaryKey = true;

    post_key = new FProperties("post_key", TF::Int4, 0, true);
    category_key = new FProperties("category_key", TF::Int4, 0, true);

    Table::addProperties(fk);
    Table::addProperties(post_key);
    Table::addProperties(category_key);
    IConnect::setConnection(pConnect);

}

db_CategoriesRelation::~db_CategoriesRelation()
{
}

