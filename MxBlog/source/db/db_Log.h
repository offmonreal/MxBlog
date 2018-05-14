#ifndef DB_LOG_H
#define DB_LOG_H

#include "../includes.h"
#include "MxSql.h"

using namespace MxSQL;

class db_Log : public Table
{
    public:
    FProperties * fk, * value_log, * date_log;
public:
    db_Log(PGconn * pConnect = nullptr);
    virtual ~db_Log();
private:

};

#endif /* DB_LOG_H */

