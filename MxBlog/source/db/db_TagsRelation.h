#ifndef DB_TAGSRELATION_H
#define DB_TAGSRELATION_H

#include "../includes.h"
#include "MxSql.h"

using namespace MxSQL;


class db_TagsRelation : public Table
{
    public:
    FProperties * fk, * post_key, * tags_key;
public:
    db_TagsRelation(PGconn * pConnect = nullptr);
    virtual ~db_TagsRelation();
private:

};

#endif /* DB_TAGSRELATION_H */

