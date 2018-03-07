#ifndef DB_USERS_H
#define DB_USERS_H

#include "includes.h"
#include "MxSql.h"

using namespace MxSQL;

class db_Users  : public Table
{
public:
    db_Users(PGconn * pConnect = nullptr);
    virtual ~db_Users();
private:

};

#endif /* DB_USERS_H */

