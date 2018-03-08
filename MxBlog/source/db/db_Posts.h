#ifndef DB_POSTS_H
#define DB_POSTS_H

#include "../includes.h"
#include "MxSql.h"

using namespace MxSQL;

class db_Posts : public Table
{
public:
    FProperties * fk, * title, * body_preview, * body_addon, * user_id, * status_id, * start_date, * create_date, * access_level, * relation_categories, * relation_tag, * seo_url, * fixed, * image_url;
public:
    db_Posts(PGconn * pConnect = nullptr);
    virtual ~db_Posts();
private:

};

#endif /* DB_POSTS_H */

