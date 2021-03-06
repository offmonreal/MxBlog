#include "db_UserAccess.h"

db_UserAccess::db_UserAccess(PGconn * pConnect)
{
    Table::setName("user_access");

    //First key
    fk = new FProperties("key_usr_access", TF::SERIAL4);
    fk->PrimaryKey = true;
    
    parameter = new FProperties("parameter", TF::VarChar, 15, true, MxSQL::UI::LOWER);
    description = new FProperties("description", TF::VarChar, 255);

    Table::addProperties(fk);
    Table::addProperties(parameter);
    Table::addProperties(description);

    IConnect::setConnection(pConnect);
    
}

db_UserAccess::~db_UserAccess()
{
}

