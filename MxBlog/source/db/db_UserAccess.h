#ifndef DB_ACCESS_H
#define DB_ACCESS_H

#include "../includes.h"
#include "MxSql.h"

using namespace MxSQL;

class db_UserAccess : public Table
{
public:
    FProperties * fk, * parameter, * description;
public:
    db_UserAccess(PGconn * pConnect = nullptr);
    virtual ~db_UserAccess();
private:

};

#endif /* DB_ACCESS_H */

