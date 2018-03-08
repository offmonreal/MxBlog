#ifndef DB_POSTSTATUS_H
#define DB_POSTSTATUS_H
#include "includes.h"
#include "MxSql.h"

using namespace MxSQL;

class db_PostStatus : public Table
{
    public:
    FProperties * fk, *parameter, * description;
public:
    db_PostStatus(PGconn * pConnect = nullptr);
    virtual ~db_PostStatus();
private:

};

#endif /* DB_POSTSTATUS_H */

