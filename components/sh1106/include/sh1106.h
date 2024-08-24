#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

// commands
#define SH1106_CMD_SETLOWCOLADDR 0x00
#define SH1106_CMD_SETHIGHCOLADDR 0x10

#define SH1106_CMD_SETSTARTLINE 0x40
#define SH1106_CMD_SETCONTRAST 0x81
#define SH1106_CMD_SETSEGREMAP 0xA0

#define SH1106_CMD_NORMALDISPLAY 0xA6
#define SH1106_CMD_REVERSEDISPLAY 0xA7

#define SH1106_CMD_SETMULTIPLEX 0xA8

#define SH1106_CMD_DISPLAYOFF 0xAE
#define SH1106_CMD_DISPLAYON 0xAF

#define SH1106_CMD_SETPAGEADDR 0xB0

#define SH1106_CMD_SETOUTPUTSCANDIR 0xC0

#define SH1106_CMD_SETDISPLAYOFFSET 0xD3

#define SH1106_CMD_RMWSTART 0xE0
#define SH1106_CMD_RMWEND 0xEE

// display dimensions
#define SH1106_DISP_WIDTH 128
#define SH1106_DISP_HEIGHT 64

// font
typedef struct
{
    uint8_t width;
    uint8_t height;

    const uint8_t *font;
} sh1106_font_t;

extern const sh1106_font_t sh1106_font5x7;

esp_err_t sh1106_init(i2c_master_bus_handle_t i2c_bus_handle);

esp_err_t sh1106_deinit(void);

esp_err_t sh1106_send_cmd(uint8_t cmd);

esp_err_t sh1106_send_double_cmd(uint8_t cmd1, uint8_t cmd2);

esp_err_t sh1106_set_page_addr(uint8_t addr);

esp_err_t sh1106_set_col_addr(uint8_t addr);

esp_err_t sh1106_write_data(const uint8_t *const data, size_t size);

esp_err_t sh1106_cpy_buf_to_disp(void);

void sh1106_buf_clear(void);

void sh1106_buf_set_pixel_on(uint8_t x, uint8_t y);

void sh1106_buf_set_pixel_off(uint8_t x, uint8_t y);

esp_err_t sh1106_buf_set_char(uint8_t x, uint8_t y, char c, const sh1106_font_t *const font);

esp_err_t sh1106_buf_set_text(uint8_t x, uint8_t y, const char *text, const sh1106_font_t *const font);
