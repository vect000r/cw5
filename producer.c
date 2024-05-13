#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 8
int main(int argc, char *argv[])
{
    int fpipe;
    ssize_t bytes_read;

    if(argc != 3)
    {
        perror("Argument error");
        exit(1);
    }
    
    char buffer[BUFFER_SIZE];
    FILE* source_file = fopen(argv[2], "r");
    if(source_file==NULL)
    {
        perror("Failed to open source file ");
        exit(1);
    }
    
    fpipe = open(argv[1], O_WRONLY);

    if (fpipe < 0)
    {
        printf("Failed to open named pipe: %d.\n", fpipe);
        exit(1);
    }
    while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, source_file)) > 0)
    {
        // Zapisanie danych do potoku nazwanego
        int result = write(fpipe, buffer, bytes_read);

        if (result < 0)
        {
                printf("Failed to write to named pipe.\n");
                exit(1);
        }
        else
        {
                printf("%zu succesfully written to named pipe. Contents: %s\n", bytes_read, buffer);
        }
    }
    
    close(fpipe);
    fclose(source_file);
    return 0;
}