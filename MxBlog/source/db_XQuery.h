#ifndef DB_QUERY_H
#define DB_QUERY_H

#include "db_Log.h"
#include "db_Catigories.h"
#include "db_Comments.h"
#include "db_Posts.h"
#include "db_Session.h"
#include "db_UserAccess.h"
#include "db_Users.h"



#include "MxSql.h"

using namespace MxSQL;

class DB_QUERY : public Table
{
public:

    DB_QUERY()
    {
    };

    virtual ~DB_QUERY()
    {
    };
private:
};

#endif /* DB_QUERY_H */

