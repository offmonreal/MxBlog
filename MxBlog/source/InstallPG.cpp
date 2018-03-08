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

    //CLEAR ALL DATA USER DB mxblog
    q->Query("drop owned by mxblog");


    db_Categories * categories = new db_Categories(conn);
    db_CategoriesRelation * categories_relation = new db_CategoriesRelation(conn);
    db_Users * usr = new db_Users(conn);
    db_UserAccess * usr_lvl = new db_UserAccess(conn);
    db_Setting * sett = new db_Setting(conn);
    db_PostStatus * post_st = new db_PostStatus(conn);
    db_Tags * tags = new db_Tags(conn);
    db_TagsRelation * tags_relation = new db_TagsRelation(conn);
    db_Posts * posts = new db_Posts(conn);
    
    
    vector<Observer*> all_table;

    all_table.push_back(tags);
    all_table.push_back(tags_relation);
    all_table.push_back(categories);
    all_table.push_back(categories_relation);
    all_table.push_back(usr);
    all_table.push_back(usr_lvl);
    all_table.push_back(sett);
    all_table.push_back(post_st);
    all_table.push_back(posts);
    all_table.push_back(new db_Log(conn));
    all_table.push_back(new db_Comments(conn));
    all_table.push_back(new db_Session(conn));


    bool status = true;

    //Create tables
    for(Observer * obs : all_table)
    {
        content_string += "<li>Create table '" + obs->getName();
        if(obs->CreateTabele())
            content_string += "' OK</li>";
        else
        {
            content_string += "' ERROR</li>";
            content_string += "<p>Error create tables</p><hr><p>" + obs->z_last_error + "</p>";
            status = false;
        }
    }

    //Error create tables
    if(status == false)
    {
exit_now:
        content_string += "<hr><p><a href='install.html' class='btn'>Go back</a></p>";

        for(Observer * obs : all_table)
            delete obs;

        q->CloseConnect();

        delete q;
        return new ByteArray(content_string);
    }

    ///////////////////////////// INIT DATA DEFOLT VALUE /////////////////////////////

    vector<IElement*> * values = new vector<IElement*> ();

    ///////////////////////////// db_UserAccess /////////////////////////////
    content_string += "<li>Initializing the Data Table '" + usr_lvl->getName();

    initUserAccess(usr_lvl, values);

    status = usr_lvl->Insert(values);

exit_init:

    for(IElement* el : *values)
        delete el;

    values->clear();

    //
    if(status == false)
    {
        content_string += "' ERROR</li>";
        content_string += "<p>Error initializing tables</p><hr><p>" + usr_lvl->z_last_error + "</p>";
        goto exit_now;
    }
    else
    {
        content_string += "' OK</li>";
        for(IElement* el : *values)
            delete el;
        values->clear();
    }
    /////////////////////////////    E  N  D   /////////////////////////////

    ///////////////////////////// db_Setting /////////////////////////////

    content_string += "<li>Initializing the Data Table '" + sett->getName();

    initSetting(sett, values);

    status = sett->Insert(values);

    if(status == false)
    {
        goto exit_init;
    }
    else
    {
        content_string += "' OK</li>";

        for(IElement* el : *values)
            delete el;
        values->clear();
    }

    /////////////////////////////    E  N  D   /////////////////////////////

    ///////////////////////////// db_PostStatus /////////////////////////////

    content_string += "<li>Initializing the Data Table '" + post_st->getName();

    initPostStatus(post_st, values);

    status = post_st->Insert(values);

    if(status == false)
    {
        goto exit_init;
    }
    else
    {
        content_string += "' OK</li>";
        for(IElement* el : *values)
            delete el;
        values->clear();
    }

    /////////////////////////////    E  N  D   /////////////////////////////

    ///////////////////////////// ADD ADMIN !  /////////////////////////////

    VElement * val_el = new VElement();
    val_el->add(usr->nick_name->get(ulogin));
    val_el->add(usr->password->get(psw));
    val_el->add(usr->email->get(""));
    val_el->add(usr->access->get("1"));
    val_el->add(usr->locked->get("false"));
    val_el->add(usr->date_create->get(MxSQL::DateTime::now_timestamp_utc()));
    val_el->add(usr->subscribe->get("true"));



    if(!usr->Insert(val_el))
    {
        delete val_el;
        content_string += "<p>Error initializing tables</p><hr>";
        goto exit_now;
    }
    else
    {
        delete val_el;
    }
    /////////////////////////////    E  N  D   /////////////////////////////

    ///////////////////////////// ADD CATIGORIES !  /////////////////////////////
    val_el = new VElement();
    val_el->add(categories->name_category->get("General"));
    val_el->add(categories->children_category->get("0"));
    val_el->add(categories->seo_url->get(""));

    if(!categories->Insert(val_el))
    {
        delete val_el;
        content_string += "<p>Error initializing tables categories</p><hr>";
        goto exit_now;
    }
    else
    {
        delete val_el;
    }
    /////////////////////////////    E  N  D   /////////////////////////////


    ///////////////////////////// ADD POST !  /////////////////////////////
    val_el = new VElement();

    /////////////////////////////    E  N  D   /////////////////////////////




    content_string += "<hr><h3>Success!</h3><p>Admin panel:</br><code>http://your_site/mx-admin/</code></br>Start now!</p><p><a href='index.html' class='btn'>View website</a> <a href='mx-admin/' class='btn'>Admin panel</a></p>";

    return new ByteArray(content_string);

}

void InstallPG::initPostStatus(db_PostStatus * tbl, vector<IElement*> * values)
{
    VElement * el = new VElement();
    el->add(tbl->parameter->get("enable"));
    el->add(tbl->description->get("Enable on site"));
    values->push_back(el->Element());
    //
    el = new VElement();
    el->add(tbl->parameter->get("disable"));
    el->add(tbl->description->get("Disable on site"));
    values->push_back(el->Element());
    //
    el = new VElement();
    el->add(tbl->parameter->get("edit"));
    el->add(tbl->description->get("Draft"));
    values->push_back(el->Element());
}

void InstallPG::initSetting(db_Setting * tbl, vector<IElement*> * values)
{
    VElement * el = new VElement();
    el->add(tbl->parameter->get("blog_name"));
    el->add(tbl->value->get("MxBlog"));
    el->add(tbl->description->get("Name your blog"));
    values->push_back(el->Element());
    //
    el = new VElement();
    el->add(tbl->parameter->get("is_enable"));
    el->add(tbl->value->get("true"));
    el->add(tbl->description->get("Variant acess: true,false,password,filter"));
    values->push_back(el->Element());
    //
    el = new VElement();
    el->add(tbl->parameter->get("reg_new_user"));
    el->add(tbl->value->get("false"));
    el->add(tbl->description->get("Enable registration user. Varian value: true,false"));
    values->push_back(el->Element());
    //
    el = new VElement();
    el->add(tbl->parameter->get("enable_comment"));
    el->add(tbl->value->get("false"));
    el->add(tbl->description->get("Enable comment to post. Varian: true,false,only_member,only_capcha"));
    values->push_back(el->Element());
    //
    el = new VElement();
    el->add(tbl->parameter->get("post_on_page"));
    el->add(tbl->value->get("15"));
    el->add(tbl->description->get("Coun post on start page. Varian: 1-100"));
    values->push_back(el->Element());

}

void InstallPG::initUserAccess(db_UserAccess * tbl, vector<IElement*> * values)
{
    VElement * el = new VElement();
    el->add(tbl->parameter->get("admin"));
    el->add(tbl->description->get("Full access"));
    values->push_back(el->Element());
    //
    el = new VElement();
    el->add(tbl->parameter->get("poster"));
    el->add(tbl->description->get("Post access"));
    values->push_back(el->Element());
    //
    el = new VElement();
    el->add(tbl->parameter->get("reader"));
    el->add(tbl->description->get("Only read"));
    values->push_back(el->Element());
    //
    el = new VElement();
    el->add(tbl->parameter->get("friend"));
    el->add(tbl->description->get("Read and write comment VIP access"));
    values->push_back(el->Element());
    //
    el = new VElement();
    el->add(tbl->parameter->get("user"));
    el->add(tbl->description->get("Read and write comment if enable setting blog"));
    values->push_back(el->Element());

}

InstallPG::~InstallPG()
{
}

