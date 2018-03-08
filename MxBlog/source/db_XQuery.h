#ifndef DB_QUERY_H
#define DB_QUERY_H

#include "db/db_Log.h"
#include "db/db_Comments.h"
#include "db/db_Posts.h"
#include "db/db_Session.h"
#include "db/db_UserAccess.h"
#include "db/db_Users.h"
#include "db/db_Setting.h"
#include "db/db_PostStatus.h"
#include "db/db_Tags.h"
#include "db/db_TagsRelation.h"
#include "db/db_Categories.h"
#include "db/db_CategoriesRelation.h"





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

