#ifndef DB_SESSION_H
#define DB_SESSION_H

#include "includes.h"
#include "MxSql.h"

using namespace MxSQL;

class db_Session  : public Table
{
public:
    db_Session(PGconn * pConnect = nullptr);
    virtual ~db_Session();
private:

};

#endif /* DB_SESSION_H */

