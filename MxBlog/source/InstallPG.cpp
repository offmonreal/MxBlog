#include "InstallPG.h"

InstallPG::InstallPG() : XWPage::XWPage(PG_TYPE::PGT_DYNAMIC_BODY, MIME::TEXT_HTML)
{
    XWPage::setConstructor(this);
    XWPage::setHead(new ByteArray("<!DOCTYPE html><html lang='en'><head><meta charset='utf-8'><meta http-equiv='X-UA-Compatible' content='IE=edge'><title>Install MxBlog</title><meta name='viewport' content='width=device-width, initial-scale=1'><meta name='Description' lang='en' content='Install MxBlog'><meta name='author' content='XWeb' ><meta name='robots' content='index, follow'><!-- Override CSS file - add your own CSS rules --><link rel='stylesheet' href='assets/css/styles_install.css'></head><body><div class='container'><div class='header'><h1 class='header-heading'>Weclome! One step to install MxBlog!</h1></div><div class='nav-bar'><ul class='nav'><li><a href='install.html'>One step</a></li></ul></div>"));
    XWPage::setFooter(new ByteArray("<div class='footer'>&copy; MxBlog 2018</div></div></body></html>"));
}

ByteArray * InstallPG::build(XWHeader * head)
{
   
    return new ByteArray("<div class='content'><div class='main'><h1>Install MxBlog</h1><hr> <h3>Administrator</h3><p>Enter <code>login</code> and <code>password</code> for administrator area:</p><form action='install.html'><label for='ulogin'><b>Login</b></label><input type='text' placeholder='Enter Login' name='ulogin' required><label for='psw'><b>Password</b></label><input type='password' placeholder='Enter Password' name='psw' required> <hr> <h3>Data base</h3> <p>This is a demo version of MxBlog.</br>Use the full version if you have access to the database from the Internet.</p> <p>Add a user for PostgreSQL with the login '<code>MxBlog</code>' and the password '<code>MxBlog</code>' to the local system.</br> Add a database named '<code>db_mx_blog</code>' for user '<code>MxBlog</code>'.</p> <p>Sample request from the console:</p> <blockquote> $ sudo -u postgres psql</br> postgres=# create user MxBlog;</br> postgres=# alter user MxBlog password 'MxBlog';</br> postgres-# create database db_mx_blog owner MxBlog;</br> postgres-# grant all privileges on database db_mx_blog to MxBlog;</br> postgres-# \q;</br> </blockquote> <hr> <h3>Confirm!</h3> <p>If YOU are ready</br></br><a href='install.html' class='btn'>Submit</a></p> </form><hr></div></div>");
}

InstallPG::~InstallPG()
{
}

