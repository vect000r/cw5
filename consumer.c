#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 4

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
    FILE* source_file = fopen(argv[2], "w");
    if(source_file==NULL)
    {
        perror("Failed to open source file ");
        exit(1);
    }
    
    fpipe = open(argv[1], O_RDONLY);

    if (fpipe < 0)
    {
        printf("Failed to read from named pipe: %d.\n", fpipe);
        exit(1);
    }
    while ((bytes_read = read(fpipe, buffer, BUFFER_SIZE)) > 0)
    {
        // Zapisanie danych do pliku
        int result = fwrite(buffer, sizeof(char), bytes_read, source_file);
        
        if (result < 0)
        {
                printf("Failed to write to file.\n");
                exit(1);
        }
        else
        {
                printf("%zu bytes recieved and written to file. Content: %s\n", bytes_read, buffer);
        }
    }
    
    close(fpipe);
    fclose(source_file);
    return 0;
}