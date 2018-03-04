#include "includes.h"
#include "StartPG.h"
#include "InstallPG.h"
#include "static_resource.h"
#include "XW.h"
#include "MxSql.h"

using namespace XW;
using namespace MxSql;

//Если база существует и работает
bool test_data_base()
{
    return false;
}

int main(int argc, char** argv)
{

    //Web server
    //XWeb * xw = new XWeb(80);
    //Local test
    XWeb * xw = new XWeb(9090);

    // ============ DIRECTORIES ============
    //Root dir (www)
    XWDir* dir = new XWDir();
    //www/asserts/
    XWDir * assets = new XWDir();
    //www/asserts/css/
    XWDir * css = new XWDir();
    //www/asserts/js/
    XWDir * js = new XWDir();

    // =========== VIRTUAL PATHS ===========
    //Add sub directories
    assets->addDir("css", css);
    assets->addDir("js", js);
    dir->addDir("assets", assets);


    // =========== STATIC CONTENT ===========
    //CSS
    css->addPage("bootstrap.css", new XWPage(__source_assets_css_bootstrap_css, __source_assets_css_bootstrap_css_len, MIME::TEXT_CSS));
    css->addPage("bootstrap.min.css", new XWPage(__source_assets_css_bootstrap_min_css, __source_assets_css_bootstrap_min_css_len, MIME::TEXT_CSS));
    css->addPage("styles.css", new XWPage(__source_assets_css_styles_css, __source_assets_css_styles_css_len, MIME::TEXT_CSS));
    css->addPage("styles_install.css", new XWPage(__source_assets_css_styles_install_css, __source_assets_css_styles_install_css_len, MIME::TEXT_CSS));
    //JS
    js->addPage("html5.js", new XWPage(__source_assets_js_html5_js, __source_assets_js_html5_js_len, MIME::TEXT_JAVASCRIPT));
    js->addPage("jquery-1.11.2.min.js", new XWPage(__source_assets_js_jquery_1_11_2_min_js, __source_assets_js_jquery_1_11_2_min_js_len, MIME::TEXT_JAVASCRIPT));
    js->addPage("respond.min.js", new XWPage(__source_assets_js_respond_min_js, __source_assets_js_respond_min_js_len, MIME::TEXT_JAVASCRIPT));
    js->addPage("bootstrap.js", new XWPage(__source_assets_js_bootstrap_js, __source_assets_js_bootstrap_js_len, MIME::TEXT_JAVASCRIPT));
    js->addPage("bootstrap.min.js", new XWPage(__source_assets_js_bootstrap_min_js, __source_assets_js_bootstrap_min_js_len, MIME::TEXT_JAVASCRIPT));


    // ============ DYNAMIC PAGE ============
    //Add root page (www)
    dir->addPage("", new StartPG());
    //Add root page (www/install.html)
    if(!test_data_base())
    dir->addPage("install.html", new InstallPG());


    // ============ SETTING SITE ============
    //Name domain
    xw->addSite("tnx.pw", dir);
    xw->addSite("tnx.pw:80", dir);
    xw->addSite("www.tnx.pw", dir);
    xw->addSite("www.tnx.pw:80", dir);

    //Local test VIRTUAL NAME in /etc/hosts
    xw->addSite("tnx.pp", dir);
    xw->addSite("tnx.pp:9090", dir);
    xw->addSite("www.tnx.pp", dir);
    xw->addSite("www.tnx.pp:9090", dir);

    //Start server
    xw->start();


    while(!xw->server_closed)
    {
        sleep(5);
    }

    delete xw;

    return 0;
}

