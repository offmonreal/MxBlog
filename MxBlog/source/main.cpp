#include "includes.h"
#include "enums.h"
#include "Blog.h"
using namespace XW;
using namespace MxSQL;

using namespace std;

void SetPidFile(const char* Filename)
{
    FILE* f;

    f = fopen(Filename, "w+");
    if(f)
    {
        fprintf(f, "%u", getpid());
        fclose(f);
    }

    // Theoretically, the file may not be available for opening w +
    // No error handling
}

int WorkProc(Blog * blog)
{
    struct sigaction sigact;
    sigset_t sigset;
    int signo;
    int status;

    // error signals in the program will be scratched more carefully
    // indicate that we want to receive extended error information
    sigact.sa_flags = SA_SIGINFO;
    // set the signal handler function
    sigact.sa_sigaction = Blog::signal_error;

    sigemptyset(&sigact.sa_mask);

    // set our handler to signals

    sigaction(SIGFPE, &sigact, 0); // error FPU
    sigaction(SIGILL, &sigact, 0); // erroneous instruction
    sigaction(SIGSEGV, &sigact, 0); // memory access error
    sigaction(SIGBUS, &sigact, 0); // bus error, when accessing physical memory

    sigemptyset(&sigset);

    // block the signals that we expect
    // process stop signal
    sigaddset(&sigset, SIGQUIT);

    // signal to stop the process by the user from the terminal
    sigaddset(&sigset, SIGINT);

    // signal the process completion request
    sigaddset(&sigset, SIGTERM);

    // user signal that we will use to update the config
    sigaddset(&sigset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    // Set the maximum number of disks that can be opened
    //SetFdLimit(FD_LIMIT);

    // write to the log that our demon started
    Blog::writeLog("[DAEMON] Started\n");

    // start all workflows
    status = blog->start(BLOG_START::AS_DEAMON);
    if(!status)
    {
        // a cycle of liquefying messages
        for(;;)
        {
            // wait for the specified messages
            sigwait(&sigset, &signo);

            // если то сообщение обновления конфига
            /* if (signo == SIGUSR1)
             {
                     // обновим конфиг
                     status = blog->ReloadConfig();
                     if (status == 0)
                     {
                             Blog::writeLog("[DAEMON] Reload config failed");
                     }
                     else
                     {
                             Blog::writeLog("[DAEMON] Reload config success");
                     }
             }
             else // если какой-либо другой сигнал, то выйдим из цикла
             {
                     break;
             }*/
        }

        // stop all working threads and close everything correctly
        blog->stop();
    }
    else
    {
        Blog::writeLog("[DAEMON] Create work thread failed");
    }

    Blog::writeLog("[DAEMON] Stopped");

    // return the code not requiring restart
    return NEED_TERMINATE;
}

int MonitorProc(Blog * srv)
{
    int pid;
    int status;
    int need_start = 1;
    sigset_t sigset;
    siginfo_t siginfo;

    // set up the signals that we will process
    sigemptyset(&sigset);

    // process stop signal
    sigaddset(&sigset, SIGQUIT);

    // signal to stop the process by the user from the terminal
    sigaddset(&sigset, SIGINT);

    // signal the process completion request
    sigaddset(&sigset, SIGTERM);

    // signal sent when the status of the child process changes
    sigaddset(&sigset, SIGCHLD);

    // signal sent when the status of the child process changes
    sigaddset(&sigset, SIGCHLD);

    // user signal that we will use to update the config
    sigaddset(&sigset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    // this function will create a file with our PID
    SetPidFile(PID_FILE);

    // an endless cycle of work
    for(;;)
    {
        // if you want to create a child
        if(need_start)
        {
            // create a child
            pid = fork();
        }

        need_start = 1;

        if(pid == -1) // if an error occurred
        {
            // write to the log message about this
            string out;
            XW::Format(out, "[MONITOR] Fork failed %s", strerror(errno));
            Blog::writeLog(out);
        }
        else if(!pid) // if we are a child
        {
            // this code is executed in the child

            // run the function responsible for running the daemon
            status = WorkProc(srv);

            // end the process
            exit(status);
        }
        else // if we are a parent
        {
            // this code is executed in the parent

            // expect signal arrival
            sigwaitinfo(&sigset, &siginfo);

            // if the signal came from the child
            if(siginfo.si_signo == SIGCHLD)
            {
                // get the status of completion
                wait(&status);

                // convert the status to normal view
                status = WEXITSTATUS(status);

                // if the child has finished working with the code saying that there is no need to continue working
                if(status == NEED_TERMINATE)
                {
                    // write to the log message about this
                    Blog::writeLog("[MONITOR] Childer stopped");

                    // break the loop
                    break;
                }
                else if(status == NEED_WORK) // if you want to restart the child
                {
                    // log this event
                    Blog::writeLog("[MONITOR] Childer restart");
                }
            }
            else if(siginfo.si_signo == SIGUSR1) // if there was a signal that it is necessary to reload the config
            {
                kill(pid, SIGUSR1); // send it to the child
                need_start = 0; // set the flag that we do not need to run the child again
            }
            else // if any other expected signal came
            {
                // log to the log information about the incoming signal
                string out;
                XW::Format(out, "[MONITOR] Signal  %s", strsignal(siginfo.si_signo));
                Blog::writeLog(out);

                // kill the child
                kill(pid, SIGTERM);
                status = 0;
                break;
            }
        }
    }

    // write in the log that we stopped
    Blog::writeLog("[MONITOR] Stopped");

    // delete the file with PID
    unlink(PID_FILE);

    return status;
}

// function of setting the maximum number of descriptors that can be opened

int SetFdLimit(int MaxFd)
{
    struct rlimit lim;
    int status;

    // set the current limit for the number of open descriptors
    lim.rlim_cur = MaxFd;
    // set the maximum limit for the number of open descriptors
    lim.rlim_max = MaxFd;

    // set the specified count
    status = setrlimit(RLIMIT_NOFILE, &lim);

    return status;
}

bool start_as_deamon(Blog * blog)
{

    // create a child
    int pid = fork();
    int status;

    if(pid == -1)// if the child could not be started
    {
        // display the error and its description
        printf("Start Daemon Error: %s\n", strerror(errno));

        return false;
    }
    else if(!pid) // если это потомок
    {
        // this code is already executing in the process of the child
        // allow to set all bits of rights to the created files,
        // otherwise we may have problems with access rights
        umask(0);

        //create a new session so that it does not depend on the parent
        setsid();

        // go to the root of the disk, if we do not, then there may be problems.
        // for example, with unmounting disks
        chdir("/");

        //we close the input / output / error descriptors, since we do not need them any more
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        // This function will monitor the process
        status = MonitorProc(blog);

        return status;
    }
    else // if it's a parent
    {
        // complete the process, because The main task (launching the daemon), we performed
        printf("Start Daemon success...\n");
        return true;
    }

}

//Information on the commands

static void show_usage(std::string name)
{
    std::cerr << "MxBlog free WEB CMS on C++\n"
            << "Options:\n"
            << "-h,--help\tShow this help message\n"
            << "-d,--daemon\tSATART MxBlog as daemon\n"
            << "-c,--console\tSATART MxBlog in console mode\n"
            << "-r,--reinstall \tSATART MxBlog for reinstall (remove all data in database)\n"
            << std::endl;
}

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        show_usage(argv[0]);
        return 0;
    }

    for(int i = 1; i < argc; ++i)
    {
        std::string arg;
        if(argv[i] != NULL)
            arg = string(argv[i]);

        if((arg == "-h") || (arg == "--help"))
        {
            show_usage(argv[0]);
            return 0;
        }
        else if((arg == "-d") || (arg == "--daemon"))
        {

            Blog * blog = new Blog();

            // Remove the restrictions from 1024 on what we need ...
            SetFdLimit(blog->maximum_connect);

            // Start the server
            if(start_as_deamon(blog))
                return 1;
            else
                return 0;

            // Run the server as a daemon
            //https://habrahabr.ru/post/129207/
        }
        else if((arg == "-c") || (arg == "--console"))
        {
            // Run the server in the console
            Blog * blog = new Blog();
            // Remove the restrictions from 1024 on what we need ...
            SetFdLimit(blog->maximum_connect);
            // Run the server
            blog->start(BLOG_START::AS_CONSOLE);

        }
        else if((arg == "-r") || (arg == "--reinstall"))
        {

        }
        else
        {
            //Параметры не верные
            show_usage(argv[0]);
            return 0;
        }
    }

    return 0;
}

