#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define SH1106_COMMAND_SETLOWCOLADDR 0x00
#define SH1106_COMMAND_SETHIGHCOLADDR 0x10

#define SH1106_COMMAND_SETSTARTLINE 0x40
#define SH1106_COMMAND_SETCONTRAST 0x81
#define SD1106_COMMAND_SETSEGREMAP 0xA0

#define SH1106_COMMAND_NORMALDISPLAY 0xA6
#define SH1106_COMMAND_REVERSEDISPLAY 0xA7

#define SH1106_COMMAND_SETMULTIPLEX 0xA8

#define SH1106_COMMAND_DISPLAYOFF 0xAE
#define SH1106_COMMAND_DISPLAYON 0xAF

#define SH1106_COMMAND_SETPAGEADDR 0xB0

#define SH1106_COMMAND_SETDISPLAYOFFSET 0xD3

typedef struct sh1106_t *sh1106_handle_t;

typedef struct
{
    i2c_port_num_t i2c_port;
    gpio_num_t i2c_scl;
    gpio_num_t i2c_sda;

    uint8_t display_width;
    uint8_t display_height;
} sh1106_config_t;

esp_err_t sh1106_init(sh1106_handle_t *handle, const sh1106_config_t *const config);

esp_err_t sh1106_deinit(sh1106_handle_t *handle);

esp_err_t sh1106_send_command(const sh1106_handle_t handle, const uint8_t command);

esp_err_t sh1106_send_command_with_byte(const sh1106_handle_t handle, const uint8_t command, const uint8_t byte);
