#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

// I2C
#define SH1106_I2C_ADDR 0x3C
#define SH1106_I2C_SCL_SPEED 400000

// commands
#define SH1106_CMD_SET_LOW_COL_ADDR 0x00
#define SH1106_CMD_SET_HIGH_COL_ADDR 0x10

#define SH1106_CMD_SET_START_LINE 0x40
#define SH1106_CMD_SET_CONTRAST 0x81
#define SH1106_CMD_SET_SEG_REMAP 0xA0

#define SH1106_CMD_NORMAL_DISP 0xA6
#define SH1106_CMD_REVERSE_DISP 0xA7

#define SH1106_CMD_SET_MULTIPLEX 0xA8

#define SH1106_CMD_DISP_OFF 0xAE
#define SH1106_CMD_DISP_ON 0xAF

#define SH1106_CMD_SET_PAGE_ADDR 0xB0

#define SH1106_CMD_SET_COM_SCAN_DIR 0xC0

#define SH1106_CMD_SET_DISP_OFFSET 0xD3

#define SH1106_CMD_RMW_START 0xE0
#define SH1106_CMD_RMW_END 0xEE

// display dimensions
#define SH1106_DISP_WIDTH 128
#define SH1106_DISP_HEIGHT 64

// pixel states
#define SH1106_PIXEL_OFF 0x00
#define SH1106_PIXEL_ON 0x01
#define SH1106_PIXEL_INV 0x02

// font
typedef struct
{
    uint8_t width;
    uint8_t height;

    const uint8_t *data;
} sh1106_font_t;

extern const sh1106_font_t sh1106_font5x7;
extern const sh1106_font_t sh1106_font8x16;

esp_err_t sh1106_init(i2c_master_bus_handle_t i2c_bus_handle);

void sh1106_deinit(void);

void sh1106_send_cmd(uint8_t cmd);

void sh1106_send_double_cmd(uint8_t cmd1, uint8_t cmd2);

void sh1106_display_on(void);

void sh1106_display_off(void);

void sh1106_set_contrast(uint8_t contrast);

void sh1106_inv_x_axis(bool inv);

void sh1106_inv_y_axis(bool inv);

void sh1106_reverse(bool rev);

void sh1106_scroll(int8_t step);

void sh1106_display(void);

void sh1106_clear(void);

esp_err_t sh1106_set_pixel(uint8_t x, uint8_t y, uint8_t state);

esp_err_t sh1106_write_data(uint8_t x, uint8_t y, const uint8_t *const data, uint8_t cols, uint8_t pages);

esp_err_t sh1106_write_char(uint8_t x, uint8_t y, char c, const sh1106_font_t *const font);

esp_err_t sh1106_write_text(uint8_t x, uint8_t y, const char *text, const sh1106_font_t *const font);
