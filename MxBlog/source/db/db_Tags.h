#ifndef DB_TAGS_H
#define DB_TAGS_H

#include "../includes.h"
#include "MxSql.h"

using namespace MxSQL;

class db_Tags : public Table
{
public:
    FProperties * fk, * tag_value;
public:
    db_Tags(PGconn * pConnect = nullptr);

    virtual ~db_Tags();
private:

};

#endif /* DB_TAGS_H */

