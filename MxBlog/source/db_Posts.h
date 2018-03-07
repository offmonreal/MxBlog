#ifndef DB_POSTS_H
#define DB_POSTS_H

#include "includes.h"
#include "MxSql.h"

using namespace MxSQL;


class db_Posts : public Table
{
public:
    db_Posts(PGconn * pConnect = nullptr);
    virtual ~db_Posts();
private:

};

#endif /* DB_POSTS_H */

