#include "StartPG.h"

StartPG::StartPG() : XWPage::XWPage(PG_TYPE::PGT_DYNAMIC_ALL, MIME::TEXT_HTML)
{
    XWPage::setConstructor(this);
}

ByteArray * StartPG::build(XWHeader * head)
{
    string testDynamciContent;
    testDynamciContent = "<!DOCTYPE html><html><body><h1>My First Dynamic PAGE!</h1><p>Server time: ";
    testDynamciContent += XW::getTime() + "</p></body></html>";

    return new ByteArray(testDynamciContent);
}

StartPG::~StartPG()
{
}

