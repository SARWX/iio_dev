#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iio.h>
#include <unistd.h>

#define FILENAME "iio_data.txt"

int main(void) {
    struct iio_context *ctx;
    struct iio_device *dev;
    struct iio_channel *chn;
    FILE *fp;
    int ret;
    uint8_t buffer[256];
    struct timespec ts_sleep = {1, 0}; // 1 секунда задержки
    struct timespec start, current;
    clock_gettime(CLOCK_MONOTONIC, &start);
    double elapsed_time = 0;
    uint8_t result[500000];

    // Создание контекста IIO
    ctx = iio_create_local_context();
    if (!ctx) {
        perror("Failed to create IIO context");
        return EXIT_FAILURE;
    }

    // Находим устройство IIO (предположим, что устройство уже известно)
    dev = iio_context_find_device(ctx, "iio:device0");
    if (!dev) {
        fprintf(stderr, "Failed to find IIO device\n");
        ret = EXIT_FAILURE;
        goto out;
    }

    // Находим канал
    chn = iio_device_find_channel(dev, "voltage", false);
    if (!chn) {
        fprintf(stderr, "Failed to find channel\n");
        ret = EXIT_FAILURE;
        goto out;
    }

    

    // Открываем файл для записи данных
    fp = fopen(FILENAME, "w");
    if (!fp) {
        perror("Failed to open file");
        ret = EXIT_FAILURE;
        goto out;
    }





while (elapsed_time < 1.0) {
    ssize_t len = iio_channel_read(chn, dev->buffer, result, sizeof(dev->buffer));
    if (len < 0) {
        fprintf(stderr, "Failed to read channel\n");
        ret = EXIT_FAILURE;
        break;
    }

    // Записываем данные в файл
    fwrite(result, 1, len, fp);

    // Обновляем текущее время и вычисляем прошедшее время
    clock_gettime(CLOCK_MONOTONIC, &current);
    elapsed_time = (current.tv_sec - start.tv_sec) + (current.tv_nsec - start.tv_nsec) / 1e9;
}






out:
    // Освобождаем ресурсы
    if (ctx)
        iio_context_destroy(ctx);

    return ret;
}
