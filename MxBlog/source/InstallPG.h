#ifndef INSTALLPG_H
#define INSTALLPG_H
#include "includes.h"
#include "defines.h"

//XWeb
#include "XW.h"

//Table MxSQL
#include "db_XQuery.h"


using namespace XW;
using namespace MxSQL;

class InstallPG : public XWPage, public XWConstructor
{
public:
    InstallPG();
public:
    virtual ByteArray * build(XWHeader * head) override final;
public:
    virtual ~InstallPG();
private:

};

#endif /* INSTALLPG_H */

