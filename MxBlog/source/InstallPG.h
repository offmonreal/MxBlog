#ifndef INSTALLPG_H
#define INSTALLPG_H
#include "includes.h"

#include "XW.h"
#include "MxSql.h"

using namespace XW;
using namespace MxSql;

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

