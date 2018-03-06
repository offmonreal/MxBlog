#ifndef DB_CATIGORIES_H
#define DB_CATIGORIES_H

#include "includes.h"
#include "MxSql.h"

using namespace MxSQL;

class db_Catigories : public Table
{
public:
    db_Catigories(PGconn * pConnect = nullptr);
    virtual ~db_Catigories();
private:

};

#endif /* DB_CATIGORIES_H */

