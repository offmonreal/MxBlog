#ifndef MXADMINPG_H
#define MXADMINPG_H

#include "includes.h"
#include "defines.h"
#include "Random.h"

//XWeb
#include "XW.h"

//Table MxSQL
#include "db_XQuery.h"


using namespace XW;
using namespace MxSQL;

class MxAdminPG : public XWPage, public XWConstructor
{
public:
    MxAdminPG();
public:
    virtual ByteArray * build(XWHeader * head) override final;
public:
    static int getLevelAccess(string login, string password, PGconn * conn);
public:
    ~MxAdminPG();
private:

};

#endif /* MXADMINPG_H */

