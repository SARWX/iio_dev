import iio
import time

def main():
    # Создаем контекст
    ctx = iio.Context()

    # Находим устройство
    dev = ctx.find_device("iio:device0")
    if dev is None:
        print("Failed to find device")
        return

    # Находим канал
    chn = dev.find_channel("voltage", False)
    if chn is None:
        print("Failed to find channel")
        return

    # Активируем канал
    chn.enabled = True

    # Создаем буфер
    buf_size = 256
    buf = iio.Buffer(dev, buf_size, False)
    if buf is None:
        print("Failed to create buffer")
        return

    # Открываем файл для записи
    with open("output_data.txt", "w") as f:
        start_time = time.time()
        
        while time.time() - start_time < 1:
            buf.refill()  # Заполняем буфер новыми данными

            # Чтение данных из буфера
            data = buf.read()

            # Запись данных в файл
            for sample in data:
                f.write(f"{sample}\n")

if __name__ == "__main__":
    main()
