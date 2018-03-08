#include "db_TagsRelation.h"

db_TagsRelation::db_TagsRelation(PGconn * pConnect)
{
    Table::setName("tags_relation");

    fk = new FProperties("key_tags_relation", TF::SERIAL4);
    fk->PrimaryKey = true;

    post_key = new FProperties("post_key", TF::Int4, 0, true);
    tags_key = new FProperties("tags_key", TF::Int4, 0, true);

    Table::addProperties(fk);
    Table::addProperties(post_key);
    Table::addProperties(tags_key);
    
    
    IConnect::setConnection(pConnect);
}

db_TagsRelation::~db_TagsRelation()
{
}

