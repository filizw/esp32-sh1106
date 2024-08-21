#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

#define SH1106_COMMAND_SETLOWCOLADDR 0x00
#define SH1106_COMMAND_SETHIGHCOLADDR 0x10

#define SH1106_COMMAND_SETSTARTLINE 0x40
#define SH1106_COMMAND_SETCONTRAST 0x81
#define SH1106_COMMAND_SETSEGREMAP 0xA0

#define SH1106_COMMAND_NORMALDISPLAY 0xA6
#define SH1106_COMMAND_REVERSEDISPLAY 0xA7

#define SH1106_COMMAND_SETMULTIPLEX 0xA8

#define SH1106_COMMAND_DISPLAYOFF 0xAE
#define SH1106_COMMAND_DISPLAYON 0xAF

#define SH1106_COMMAND_SETPAGEADDR 0xB0

#define SH1106_COMMAND_SETOUTPUTSCANDIR 0xC0

#define SH1106_COMMAND_SETDISPLAYOFFSET 0xD3

#define SH1106_COMMAND_RMWSTART 0xE0
#define SH1106_COMMAND_RMWEND 0xEE

#define SH1106_RESOLUTION_128x64 128*64

typedef struct sh1106_t *sh1106_handle_t;

typedef struct
{
    i2c_port_num_t i2c_port;
    gpio_num_t i2c_scl;
    gpio_num_t i2c_sda;

    uint8_t display_width;
    uint8_t display_height;
} sh1106_config_t;

typedef struct
{
    uint8_t width;
    uint8_t height;

    const uint8_t *font;
} sh1106_font_t;

extern const sh1106_font_t sh1106_font5x7;

esp_err_t sh1106_init(sh1106_handle_t *const handle, const sh1106_config_t *const config);

esp_err_t sh1106_deinit(sh1106_handle_t *const handle);

esp_err_t sh1106_send_command(const sh1106_handle_t handle, const uint8_t command);

esp_err_t sh1106_send_command_with_byte(const sh1106_handle_t handle, const uint8_t command, const uint8_t byte);

esp_err_t sh1106_set_page_address(const sh1106_handle_t handle, const uint8_t address);

esp_err_t sh1106_set_column_address(const sh1106_handle_t handle, const uint8_t address);

esp_err_t sh1106_write_byte(const sh1106_handle_t handle, const uint8_t byte);

esp_err_t sh1106_write_data(const sh1106_handle_t handle, const uint8_t *const data, size_t data_size);

esp_err_t sh1106_write_memory(const sh1106_handle_t handle);

esp_err_t sh1106_clear(const sh1106_handle_t handle, const uint8_t color);

esp_err_t sh1106_draw_character(const sh1106_handle_t handle, uint8_t x, uint8_t y, char c, const sh1106_font_t *const font);

esp_err_t sh1106_draw_text(const sh1106_handle_t handle, const char *const text);
