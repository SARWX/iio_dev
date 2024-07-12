#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#define IIO_DEV_PATH "/sys/bus/iio/devices/iio:device0/in_voltage_raw" // Путь к raw значению (измените по необходимости)

void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int fd;
    char buffer[16];
    struct timespec start, current;
    FILE *file;
    ssize_t bytes_read;

    // Открытие файла для записи
    file = fopen("output_data.txt", "w");
    if (!file) {
        error_exit("fopen");
    }

    // Открытие устройства для чтения
    fd = open(IIO_DEV_PATH, O_RDONLY);
    if (fd < 0) {
        fclose(file);
        error_exit("open");
    }

    // Получаем текущее время
    if (clock_gettime(CLOCK_MONOTONIC, &start) == -1) {
        close(fd);
        fclose(file);
        error_exit("clock_gettime");
    }

    // Читаем данные в течение 2 секунд
    while (1) {
        if (clock_gettime(CLOCK_MONOTONIC, &current) == -1) {
            close(fd);
            fclose(file);
            error_exit("clock_gettime");
        }

        if ((current.tv_sec - start.tv_sec) >= 2) {
            break;
        }

        // Сбрасываем указатель чтения файла на начало
        lseek(fd, 0, SEEK_SET);

        bytes_read = read(fd, buffer, sizeof(buffer) - 1);
        if (bytes_read < 0) {
            if (errno == EAGAIN) {
                // Данные временно недоступны, повторяем попытку
                continue;
            } else {
                close(fd);
                fclose(file);
                error_exit("read");
            }
        }

        // Завершаем строку нулевым символом
        buffer[bytes_read] = '\0';

        // Записываем прочитанные данные в файл
        if (fprintf(file, "%s\n", buffer) < 0) {
            close(fd);
            fclose(file);
            error_exit("fprintf");
        }
    }

    // Закрытие файла и устройства
    close(fd);
    fclose(file);

    printf("Data successfully written to output_data.txt\n");
    return 0;
}