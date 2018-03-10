#include "Blog.h"
#include "static_resource.h"

Blog::Blog()
{
    maximum_connect = 1024; //Максимум клиентов подключенных
    //xw = new XWeb(80);
    //Local test
    xw = new XWeb(9090);
}

bool Blog::findeBase()
{
    return false;
}

void Blog::init()
{

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
    if(!findeBase())
        dir->addPage("install.html", new InstallPG());


    // ============ SETTING SITE ============
    //Name domain
    /*
    xw->addSite("false.ga", dir);
    xw->addSite("false.ga:80", dir);
    xw->addSite("www.false.ga", dir);
    xw->addSite("www.false.ga:80", dir);
    */


    //Local test VIRTUAL NAME in /etc/hosts
    xw->addSite("mx.blog", dir);
    xw->addSite("mx.blog:9090", dir);
    xw->addSite("www.mx.blog", dir);
    xw->addSite("www.mx.blog:9090", dir);
}

bool Blog::start(BLOG_START as)
{
    init();
    //Вдруг у нас больше можно
    xw->maximum_connect = maximum_connect;

    //Start server
    if(as == BLOG_START::AS_DEAMON)
        return xw->start();
    else
        xw->start();

    while(!xw->server_closed)
    {
        sleep(5);
    }

    delete xw;
    return true;
}

void Blog::stop()
{
    xw->stop();
}

void Blog::writeLog(string value)
{

    //    if(value == nullptr || strlen(value) < 1)
    return;

    openlog("mxblog", LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_INFO, value.c_str()); //Запишим
    closelog(); //Закроем лог      


}

// функция обработки сигналов ошибок

void Blog::signal_error(int sig, siginfo_t *si, void *ptr)
{
    void* ErrorAddr;
    void* Trace[16];
    int x;
    int TraceSize;
    char** Messages;

    string out;

    // запишем в лог что за сигнал пришел
    XW::Format(out, "[DAEMON] Signal: %s, Addr: 0x%0.16X\n %s", strsignal(sig), si->si_addr);
    writeLog(out);


#if __WORDSIZE == 64 // если дело имеем с 64 битной ОС
    // получим адрес инструкции которая вызвала ошибку
    ErrorAddr = (void*) ((ucontext_t*) ptr)->uc_mcontext.gregs[REG_RIP];
#else
    // получим адрес инструкции которая вызвала ошибку
    ErrorAddr = (void*) ((ucontext_t*) ptr)->uc_mcontext.gregs[REG_EIP];
#endif

    // произведем backtrace чтобы получить весь стек вызовов
    TraceSize = backtrace(Trace, 16);
    Trace[1] = ErrorAddr;

    // получим расшифровку трасировки
    Messages = backtrace_symbols(Trace, TraceSize);
    if(Messages)
    {
        writeLog("== Backtrace ==");

        // запишем в лог
        for(x = 1; x < TraceSize; x++)
        {
            writeLog(string(Messages[x])); //"%s\n",
        }

        writeLog("== End Backtrace ==");
        free(Messages);
    }

    writeLog("[DAEMON] Stopped\n");

    //остановим все рабочие потоки и корректно закроем всё что надо
    //Stop();

    // завершим процесс с кодом требующим перезапуска
    exit(NEED_WORK);
}

Blog::~Blog()
{
}

