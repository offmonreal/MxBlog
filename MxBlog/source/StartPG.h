#ifndef STARTPG_H
#define STARTPG_H

#include "includes.h"

#include "XW.h"
#include "MxSql.h"

using namespace XW;
using namespace MxSQL;

class StartPG : public XWPage, public XWConstructor
{
public:
    StartPG();
public:
     virtual ByteArray * build(XWHeader * head) override final;
public:
    ~StartPG();
private:

};

#endif /* STARTPG_H */

