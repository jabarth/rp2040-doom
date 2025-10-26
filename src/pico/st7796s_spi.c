
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "PICO_GAME_HAT_EP0172.h"

void lcd_write_cmd(uint8_t cmd) {
    gpio_put(TFT_CS, 0);
    gpio_put(TFT_DC, 0);
    spi_write_blocking(spi0, &cmd, 1);
    gpio_put(TFT_CS, 1);
}

void lcd_write_data(uint8_t data) {
    gpio_put(TFT_CS, 0);
    gpio_put(TFT_DC, 1);
    spi_write_blocking(spi0, &data, 1);
    gpio_put(TFT_CS, 1);
}

#include <stdio.h>

void st7796s_spi_init() {
    printf("st7796s_spi_init()\n");
    spi_init(spi0, 40 * 1000 * 1000); // 40MHz
    gpio_set_function(TFT_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(TFT_SCLK, GPIO_FUNC_SPI);

    gpio_init(TFT_CS);
    gpio_set_dir(TFT_CS, GPIO_OUT);
    gpio_put(TFT_CS, 1);

    gpio_init(TFT_DC);
    gpio_set_dir(TFT_DC, GPIO_OUT);

    gpio_init(TFT_RST);
    gpio_set_dir(TFT_RST, GPIO_OUT);

    // Reset the display
    gpio_put(TFT_RST, 0);
    sleep_ms(100);
    gpio_put(TFT_RST, 1);
    sleep_ms(100);
}
