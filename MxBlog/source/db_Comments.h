#ifndef DB_COMMENTS_H
#define DB_COMMENTS_H


#include "includes.h"
#include "MxSql.h"

using namespace MxSQL;


class db_Comments : public Table
{
public:
    db_Comments(PGconn * pConnect = nullptr);
    virtual ~db_Comments();
private:

};

#endif /* DB_COMMENTS_H */

