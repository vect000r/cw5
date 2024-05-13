#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

void remove_fifo() 
{
   if (unlink("fifopipe") == -1) 
   {
      perror("unlink");
      exit(1);
   }
}

int main(int argc, char *argv[]) 
{
    if (argc != 7) 
    {
        perror("Argument error");
        exit(1);
    }

    char *fifo_name = "fifopipe";
    if (mkfifo(fifo_name, 0666) == -1) 
    {
        perror("mkfifo");
        exit(1);
    }

    pid_t pid1, pid2;

    (pid1 = fork()) && (pid2 = fork()); 
    
    if (pid1 == 0) 
    {
        execlp(argv[1], argv[1], argv[2], argv[3], NULL);
    } 
    else if (pid2 == 0) 
    {
        execlp(argv[4], argv[4], argv[5], argv[6], NULL);
    } 
    else 
    {
        int status;
        waitpid(pid1, &status, 0); 
        waitpid(pid2, &status, 0);
        
    }
    atexit(remove_fifo);
    return 0;
}