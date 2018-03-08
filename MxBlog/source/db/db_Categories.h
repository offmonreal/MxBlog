#ifndef DB_CATIGORIES_H
#define DB_CATIGORIES_H

#include "../includes.h"
#include "MxSql.h"

using namespace MxSQL;

class db_Categories : public Table
{
public:
    FProperties * fk, * name_category, * children_category, * seo_url;
public:
    db_Categories(PGconn * pConnect = nullptr);
    virtual ~db_Categories();
private:

};

#endif /* DB_CATIGORIES_H */

