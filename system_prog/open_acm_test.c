#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define LENGTH 32

int main()
{
    int fd = open ("/dev/ttyACM0", O_RDONLY);
    if (fd == -1)
    {
        /* ошибка */
        printf("ERROR IN OPEN FUNCTION");
        return(-1);
    }
    else 
    {
        printf("fd = %d\n", fd);
        printf("reading:\n");
        char *buf;
        int i = 0;
        buf = malloc(sizeof(char) * LENGTH * 2);

        /* считываем по 8 байт 'buf' из 'fd' */
            while(1)
            {
                int nr = read (fd, buf, (sizeof (char)) * LENGTH);
                if (nr == -1)
                {
                    /* ошибка */
                    printf("ERROR IN READ FUNCTION");
                    return(-1);
                }
                else
                {
                    i++;
                    // printf("nr = %d\n", nr);    
                    // printf("read string = %s\n", buf);    
                    if (i % 10 == 0)
                    {
                        printf("ok\n");
                    }
                }
            }


    }   
}
