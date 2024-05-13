#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 4

int main(int argc, char *argv[])
{
    printf("Consumer run\n");
    int fpipe;
    ssize_t bytes_read;

    if(argc != 2)
    {
        perror("Argument error");
        exit(1);
    }
    
    char buffer[BUFFER_SIZE];
    FILE* source_file = fopen("consumer.txt", "w");
    if(source_file==NULL)
    {
        perror("Failed to open source file ");
        exit(1);
    }
    
    fpipe = open(argv[1], O_RDONLY);

    if (fpipe < 0)
    {
        printf("Błąd podczas otwierania potoku nazwanego do zapisu: %d.\n", fpipe);
        exit(EXIT_FAILURE);
    }
    while ((bytes_read = read(fpipe, buffer, BUFFER_SIZE)) > 0)
    {
        // Zapisanie danych do potoku nazwanego
        int result = fwrite(buffer, sizeof(char), bytes_read, source_file);
        
        if (result < 0)
        {
                printf("Błąd podczas zapisywania danych do pliku.\n");
                exit(1);
        }
        else
        {
                printf("Dane zostały pomyślnie zapisane do pliku.\n");
        }
    }
    
    close(fpipe);
    fclose(source_file);
    return 0;
}