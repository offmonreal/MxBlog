#ifndef DB_CATEGORIESRELATION_H
#define DB_CATEGORIESRELATION_H

#include "../includes.h"
#include "MxSql.h"

using namespace MxSQL;

class db_CategoriesRelation : public Table
{
public:
    FProperties * fk, * post_key, * category_key;
public:
    db_CategoriesRelation(PGconn * pConnect = nullptr);
    virtual ~db_CategoriesRelation();
private:

};

#endif /* DB_CATEGORIESRELATION_H */

