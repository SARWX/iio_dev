#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

#define IIO_DEV_PATH "/sys/bus/iio/devices/iio:device0/in_voltage_raw"

void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    int fd;
    int value;
    struct timespec start, current;
    FILE *file;

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

        // Читаем целое число напрямую из файла
        printf("TWWWWEWESASRESATT");
        if (fscanf(file, "%d", &value) < 0) {                   // ВОТ ТУТ ПРОБЛЕМА, ВОЗМОЖНО ПРОСТО ФОРМАТ НЕПРАВИЛЬНО ЗАДАН, ТИПО НЕ %d А " %d \n" НЕ ЗНАЮ КОРОЧЕ, ОШИБКА ЗДЕСЬ 
            close(fd);
            fclose(file);
            error_exit("fscanf");
        }

        // Записываем прочитанное число в файл
        if (fprintf(file, "%d\n", value) < 0) {
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
