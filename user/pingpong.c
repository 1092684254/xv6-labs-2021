#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char * argv[])
{
    int pidF[2];
    int pidC[2];
    pipe(pidF);
    pipe(pidC);

    int pid = fork();
    if(pid > 0)
    {
        //父进程
        close(pidF[0]);//关闭父进程的读端
        close(pidC[1]);//关闭子进程的写端
        
        write(pidF[1],"f",2);
        close(pidF[1]);//关闭父进程的写端

        char buf[4] = {0};

        read(pidC[0],buf,sizeof(buf));
        // close(pidC[0]);//关闭子进程的读端

        printf("%d: received pong\n",getpid());
        close(pidC[0]);//关闭子进程的读端

    }
    else
    {
        //子进程
        close(pidF[1]);//关闭父进程的写端
        close(pidC[0]);//关闭子进程的读端

        char buf[4] = {0};

        read(pidF[0],buf,sizeof(buf));
        printf("%d: received ping\n",getpid());
        close(pidF[0]);//关闭父进程的读端
        
        
        write(pidC[1],"c",2);
        close(pidC[1]);//关闭子进程的写端

       

        

    }



    exit(0);
}