import time

# Путь к файлу для чтения данных
input_file = '/dev/iio:device0'

# Путь к файлу для записи данных
output_file = 'read_test_5.txt'

buffer = []

# Открываем файл для записи
with open(output_file, 'w') as f_out:
    # Открываем файл для чтения
    with open(input_file, 'rb') as f_in:
        start_time = time.time()  # Запоминаем текущее время начала чтения
        end_time = start_time + 1  # Время окончания чтения (1 секунда)

        # Читаем данные в течение 1 секунды
        while time.time() < end_time:
            data = f_in.read(128)  # Читаем данные порциями по 128 байт
            if not data:
                break  # Прерываем цикл, если данные кончились

            # Сохраняем данные в буфер
            buffer.extend(data)

        # Записываем каждый байт как число в новой строке
        for byte in buffer:
            f_out.write(f"{byte}\n")

print("Чтение и запись завершены.")
