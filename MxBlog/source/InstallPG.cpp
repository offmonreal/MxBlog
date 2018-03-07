#include "InstallPG.h"

std::string head_install_page_en = R"(<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><title>Install MxBlog</title><meta name='viewport' content='width=device-width, initial-scale=1'><meta name='Description' lang='en' content='Install MxBlog'><meta name='author' content='XWeb' ><meta name='robots' content='index, follow'><link rel='stylesheet' href='assets/css/styles_install.css'></head><body><div class='container'><div class='header'><h1 class='header-heading'>Weclome! One step to install MxBlog!</h1></div><div class='nav-bar'><ul class='nav'><li><a href='install.html'>One step</a></li></ul></div><div class='content'><div class='main'><h1>Install MxBlog</h1><hr>)";
std::string footer_install_page_en = R"(</div></div><div class='footer'>&copy; MxBlog 2018</div></div></body></html>)";

InstallPG::InstallPG() : XWPage::XWPage(PG_TYPE::PGT_DYNAMIC_BODY, MIME::TEXT_HTML)
{
    XWPage::setConstructor(this);
    XWPage::setHead(new ByteArray(head_install_page_en));
    XWPage::setFooter(new ByteArray(footer_install_page_en));
}

ByteArray * InstallPG::build(XWHeader * head)
{
    string ulogin = head->data_post["ulogin"];
    string psw = head->data_post["psw"];

    //drop owned by adminuser

    //Test post value
    if(ulogin.empty() || psw.empty() || finde_bad_symbol(ulogin) || finde_bad_symbol(psw))
        return new ByteArray("<h3>Administrator</h3><p>Enter <code>login</code> and <code>password</code> for administrator area:</p><form name='frm_ulogin_psw' method='post'><label for='ulogin'><b>Login </b></label><input type='text' placeholder='Enter Login' name='ulogin' required><label for='psw'><b> Password </b></label><input type='password' placeholder='Enter Password' name='psw' required><hr> <h3>Data base</h3> <p>This is a demo version of MxBlog.</br>Use the full version if you have access to the database from the Internet.</p> <p>Add a user for PostgreSQL with the login '<code>MxBlog</code>' and the password '<code>MxBlog</code>' to the local system.</br> Add a database named '<code>db_mx_blog</code>' for user '<code>MxBlog</code>'.</p> <p>Sample request from the console:</p> <blockquote> $ sudo -u postgres psql</br> postgres=# create user MxBlog;</br> postgres=# alter user MxBlog password 'MxBlog';</br> postgres-# create database db_mx_blog owner MxBlog;</br> postgres-# grant all privileges on database db_mx_blog to MxBlog;</br> postgres-# \\q;</br> </blockquote> <hr> <h3>Confirm!</h3> <p>If YOU are ready</br></br> <input type='submit' class='btn' value='Submit'> </form><hr>");

    string content_string = "<h3>Result:</h3><ul>";

    DB_QUERY * q = new DB_QUERY();
    PGconn * conn = q->OpenConnect(CONNECTION_STRING);
    if(conn)
    {
        content_string += "<li><b>Test connection OK</b></li>";
    }
    else
    {
        content_string += "<li>Test connection NO</li></ul><hr><h3>Error!</h3>";
        content_string += "<p>Error connecting to database!</p><hr><p><a href='install.html' class='btn'>Go back</a></p>";
        return new ByteArray(content_string);
    }

    bool ErrorCheck = false;

    vector<Observer*> all_table;
    all_table.push_back(static_cast<Observer*> (new db_Log(conn)));
    all_table.push_back(static_cast<Observer*> (new db_Catigories(conn)));
    all_table.push_back(static_cast<Observer*> (new db_Comments(conn)));
    all_table.push_back(static_cast<Observer*> (new db_Posts(conn)));
    all_table.push_back(static_cast<Observer*> (new db_Users(conn)));
    all_table.push_back(static_cast<Observer*> (new db_Session(conn)));


    db_UserAccess * usr_lvl = new db_UserAccess(conn);

    all_table.push_back(usr_lvl);


    //Create tables
    for(Observer * obs : all_table)
    {
        content_string += "<li>Create table '" + obs->getName();
        if(obs->CreateTabele())
            content_string += "' OK</li>";
        else
        {
            content_string += "' ERROR</li>";
            content_string += "<p>Error create tables</p><hr><p>";
            content_string += obs->last_error;
            content_string += "</p><hr><p><a href='install.html' class='btn'>Go back</a></p>";
            continue;
        }

    }

    VElement * el = new VElement();
    el->add(usr_lvl->description->get("123 DESCRIPTION"));
    el->add(usr_lvl->value->get("123 VALUE"));


    usr_lvl->Insert(el->Element());

    el = new VElement();

    el->add(usr_lvl->value->get("456 VALUE"));
    el->add(usr_lvl->description->get("456 DESCRIPTION"));
    usr_lvl->Insert(el->Element());
    
    

    delete el;

    for(Observer * obs : all_table)
        delete obs;

    q->CloseConnect();

    delete q;

    return new ByteArray(content_string);
}

InstallPG::~InstallPG()
{
}

