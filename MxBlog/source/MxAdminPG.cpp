#include "MxAdminPG.h"

std::string head_admin_page_en = R"(<!DOCTYPE html><html lang="en"><head><meta charset="utf-8"><meta http-equiv="X-UA-Compatible" content="IE=edge"><title>MxBlog - admin area</title><meta name="viewport" content="width=device-width, initial-scale=1"><meta name="Description" lang="en" content="Admin area"><!-- Bootstrap Core CSS file --><link rel="stylesheet" href="assets/css/bootstrap.min.css"><!-- Override CSS file - add your own CSS rules --><link rel="stylesheet" href="assets/css/styles.css"><!-- Conditional comment containing JS files for IE6 - 8 --><!--[if lt IE 9]><script src="assets/js/html5.js"></script><script src="assets/js/respond.min.js"></script><![endif]--></head>)";
std::string footer_admin_page_en = R"(<div class='footer'>&copy; MxBlog 2018</div></html>)";

std::string body_login_en = R"(<body> <div class='container col-xs-12 col-sm-offset-2 col-sm-8 col-md-offset-3 col-md-6 col-lg-offset-4 col-lg-4'> <br /> <div class='panel panel-default'> <div class='panel-heading'> <h1>Welcome</h1> </div> <form name='frm_ulogin_psw' method='post'> <div class='panel-body'/> <div class='form-group'> <div class='input-group'> <span class='input-group-addon'> <i style='width: auto'></i> </span> <input type='text' class='form-control' name='ulogin' placeholder='Login' required /> </div> </div> <div class='form-group'> <div class='input-group'> <span class='input-group-addon'> <i style='width: auto'></i> </span> <input type='password' class='form-control' name='psw' placeholder='Password' required /> </div> </div> <button id='btnLogin' runat='server' class='btn btn-default' style='width: 100%'>Sign in</button> </form> </div> </div> </body>)";

MxAdminPG::MxAdminPG() : XWPage::XWPage(PG_TYPE::PGT_DYNAMIC_BODY, MIME::TEXT_HTML)
{
    XWPage::setConstructor(this);
    XWPage::setHead(new ByteArray(head_admin_page_en));
    XWPage::setFooter(new ByteArray(footer_admin_page_en));
}

ByteArray * MxAdminPG::build(XWHeader * head)
{

    string ulogin = head->data_post["ulogin"];
    string psw = head->data_post["psw"];

    //Test post value
    if(ulogin.empty() || psw.empty() || finde_bad_symbol(ulogin) || finde_bad_symbol(psw))
        return new ByteArray(body_login_en);

    //Table users
    db_Users * u = new db_Users();

    PGconn * conn = u->OpenConnect(CONNECTION_STRING);

    if(conn == nullptr)
        return nullptr; //Вернкть нет подключения к БД


    //Условие селекта Where
    WhereList * wh = new WhereList();
    wh->add(u->nick_name->where(WhereIf::Equally, ulogin));
    wh->add(u->password->where(WhereIf::Equally, psw));

    vector<MxSQL::Value*> * select_items = u->SelectWhere(wh);

    delete wh;

    u->CloseConnect();
    delete u;


    if(select_items != nullptr)
    {
        for(MxSQL::Value * vv : *select_items)
        {
            cout << vv->ElementName.c_str() << '\n';
            cout << *vv->va_string[0];
        }


    }

    return nullptr;
}

MxAdminPG::~MxAdminPG()
{
}

