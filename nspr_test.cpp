//#define PR_STATIC

#include <nspr/prinit.h>
#include <nspr/prio.h>

int main(int argc, char *argv[])
{
  PR_STDIO_INIT();
  
  PR_Init(PR_USER_THREAD, PR_PRIORITY_NORMAL, 0);
  
  PRFileDesc *fd = 
    PR_Open("nspr.txt", PR_WRONLY|PR_CREATE_FILE|PR_TRUNCATE, PR_IRWXU);

  PR_Write(fd, "Hello World!\n", 13);
  PR_Write(PR_STDOUT, "Hello World!\n", 13);

  PR_Close(fd);
}
