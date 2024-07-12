#!/bin/bash

# Устанавливаем параметры
URI="local:"
BUFFER_SIZE=256
SAMPLE_SIZE=1024
DEVICE_NAME="osciloscope"
CHANNEL_NAME="voltage"
OUTPUT_FILE="read_test_4.txt"

# Запускаем команду iio_readdev на 1 секунду и перенаправляем вывод в файл
timeout 1s iio_readdev -u $URI -b $BUFFER_SIZE -s $SAMPLE_SIZE $DEVICE_NAME $CHANNEL_NAME > $OUTPUT_FILE
