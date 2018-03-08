#include "db_Setting.h"

db_Setting::db_Setting(PGconn * pConnect)
{
    Table::setName("setting");

    //First key
    fk = new FProperties("key_setting", TF::SERIAL4);
    fk->PrimaryKey = true;

    parameter = new FProperties("parameter", TF::VarChar, 15, true, MxSQL::UI::LOWER);
    value = new FProperties("value", TF::VarChar, 255);
    description = new FProperties("description", TF::VarChar, 512);

    Table::addProperties(fk);
    Table::addProperties(parameter);
    Table::addProperties(value);
    Table::addProperties(description);

    IConnect::setConnection(pConnect);

}

db_Setting::~db_Setting()
{
}

