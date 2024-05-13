#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 8
int main(int argc, char *argv[])
{
    printf("Producer run\n");
    int fpipe;
    ssize_t bytes_read;

    if(argc != 2)
    {
        perror("Argument error");
        exit(1);
    }
    
    char buffer[BUFFER_SIZE];
    FILE* source_file = fopen("producer.txt", "r");
    if(source_file==NULL)
    {
        perror("Failed to open source file ");
        exit(1);
    }
    
    fpipe = open(argv[1], O_WRONLY);

    if (fpipe < 0)
    {
        printf("Błąd podczas otwierania potoku nazwanego do zapisu: %d.\n", fpipe);
        exit(1);
    }
    while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, source_file)) > 0)
    {
        // Zapisanie danych do potoku nazwanego
        int result = write(fpipe, buffer, bytes_read);

        if (result < 0)
        {
                printf("Błąd podczas zapisywania danych do potoku nazwanego.\n");
                exit(1);
        }
        else
        {
                printf("Dane zostały pomyślnie zapisane do potoku nazwanego.\n");
        }
    }
    
    close(fpipe);
    fclose(source_file);
    return 0;
}