#ifndef DB_SETTING_H
#define DB_SETTING_H
#include "includes.h"
#include "MxSql.h"

using namespace MxSQL;

class db_Setting : public Table
{
public:
    FProperties * fk, *parameter, * value, * description;
public:
    db_Setting(PGconn * pConnect = nullptr);
    virtual ~db_Setting();
private:

};

#endif /* DB_SETTING_H */

