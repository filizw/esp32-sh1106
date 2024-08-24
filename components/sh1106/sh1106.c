#include "sh1106.h"

#define SH1106_I2C_ADDR 0x3C
#define SH1106_I2C_SCL_SPEED 400000

#define DISP_RES_128x64 SH1106_DISP_WIDTH * SH1106_DISP_HEIGHT

#define CLEAR_PAGE 0
#define WRITE_PAGE 1

const uint8_t font5x7[] = {
    // ASCII 32 (space)
    0x00, 0x00, 0x00, 0x00, 0x00,
    // ASCII 33 (!)
    0x00, 0x00, 0x2F, 0x00, 0x00,
    // ASCII 34 (")
    0x00, 0x07, 0x00, 0x07, 0x00,
    // ASCII 35 (#)
    0x14, 0x7F, 0x14, 0x7F, 0x14,
    // ASCII 36 ($)
    0x24, 0x2A, 0x7F, 0x2A, 0x12,
    // ASCII 37 (%)
    0x23, 0x13, 0x08, 0x64, 0x62,
    // ASCII 38 (&)
    0x36, 0x49, 0x55, 0x22, 0x50,
    // ASCII 39 (')
    0x00, 0x05, 0x03, 0x00, 0x00,
    // ASCII 40 (()
    0x00, 0x1C, 0x22, 0x41, 0x00,
    // ASCII 41 ())
    0x00, 0x41, 0x22, 0x1C, 0x00,
    // ASCII 42 (*)
    0x14, 0x08, 0x3E, 0x08, 0x14,
    // ASCII 43 (+)
    0x08, 0x08, 0x3E, 0x08, 0x08,
    // ASCII 44 (,)
    0x00, 0x40, 0x30, 0x00, 0x00,
    // ASCII 45 (-)
    0x08, 0x08, 0x08, 0x08, 0x08,
    // ASCII 46 (.)
    0x00, 0x60, 0x60, 0x00, 0x00,
    // ASCII 47 (/)
    0x20, 0x10, 0x08, 0x04, 0x02,
    // ASCII 48 (0)
    0x3E, 0x51, 0x49, 0x45, 0x3E,
    // ASCII 49 (1)
    0x00, 0x42, 0x7F, 0x40, 0x00,
    // ASCII 50 (2)
    0x42, 0x61, 0x51, 0x49, 0x46,
    // ASCII 51 (3)
    0x21, 0x41, 0x49, 0x4F, 0x31,
    // ASCII 52 (4)
    0x18, 0x14, 0x12, 0x7F, 0x10,
    // ASCII 53 (5)
    0x27, 0x45, 0x45, 0x45, 0x39,
    // ASCII 54 (6)
    0x3C, 0x4A, 0x49, 0x49, 0x30,
    // ASCII 55 (7)
    0x01, 0x71, 0x09, 0x05, 0x03,
    // ASCII 56 (8)
    0x36, 0x49, 0x49, 0x49, 0x36,
    // ASCII 57 (9)
    0x06, 0x49, 0x49, 0x29, 0x1E,
    // ASCII 58 (:)
    0x00, 0x36, 0x36, 0x00, 0x00,
    // ASCII 59 (;)
    0x00, 0x36, 0x36, 0x00, 0x00,
    // ASCII 60 (<)
    0x08, 0x14, 0x22, 0x41, 0x00,
    // ASCII 61 (=)
    0x14, 0x14, 0x14, 0x14, 0x14,
    // ASCII 62 (>)
    0x00, 0x41, 0x22, 0x14, 0x08,
    // ASCII 63 (?)
    0x02, 0x01, 0x51, 0x09, 0x06,
    // ASCII 64 (@)
    0x32, 0x49, 0x79, 0x41, 0x3E,
    // ASCII 65 (A)
    0x7E, 0x11, 0x11, 0x11, 0x7E,
    // ASCII 66 (B)
    0x7F, 0x49, 0x49, 0x49, 0x36,
    // ASCII 67 (C)
    0x3E, 0x41, 0x41, 0x41, 0x22,
    // ASCII 68 (D)
    0x7F, 0x41, 0x41, 0x22, 0x1C,
    // ASCII 69 (E)
    0x7F, 0x49, 0x49, 0x49, 0x41,
    // ASCII 70 (F)
    0x7F, 0x09, 0x09, 0x09, 0x01,
    // ASCII 71 (G)
    0x3E, 0x41, 0x49, 0x49, 0x7A,
    // ASCII 72 (H)
    0x7F, 0x08, 0x08, 0x08, 0x7F,
    // ASCII 73 (I)
    0x41, 0x7F, 0x41, 0x00, 0x00,
    // ASCII 74 (J)
    0x20, 0x40, 0x41, 0x3F, 0x01,
    // ASCII 75 (K)
    0x7F, 0x08, 0x14, 0x22, 0x41,
    // ASCII 76 (L)
    0x7F, 0x40, 0x40, 0x40, 0x40,
    // ASCII 77 (M)
    0x7F, 0x20, 0x18, 0x20, 0x7F,
    // ASCII 78 (N)
    0x7F, 0x30, 0x0E, 0x01, 0x7F,
    // ASCII 79 (O)
    0x3E, 0x41, 0x41, 0x41, 0x3E,
    // ASCII 80 (P)
    0x7F, 0x11, 0x11, 0x11, 0x0E,
    // ASCII 81 (Q)
    0x3E, 0x41, 0x51, 0x21, 0x5E,
    // ASCII 82 (R)
    0x7F, 0x11, 0x11, 0x31, 0x4E,
    // ASCII 83 (S)
    0x32, 0x49, 0x49, 0x49, 0x26,
    // ASCII 84 (T)
    0x01, 0x01, 0x7F, 0x01, 0x01,
    // ASCII 85 (U)
    0x3F, 0x40, 0x40, 0x40, 0x3F,
    // ASCII 86 (V)
    0x07, 0x08, 0x70, 0x08, 0x07,
    // ASCII 87 (W)
    0x3F, 0x40, 0x38, 0x40, 0x3F,
    // ASCII 88 (X)
    0x63, 0x14, 0x08, 0x14, 0x63,
    // ASCII 89 (Y)
    0x03, 0x04, 0x78, 0x04, 0x03,
    // ASCII 90 (Z)
    0x61, 0x51, 0x49, 0x45, 0x43,
    // ASCII 91 ([)
    0x00, 0x7F, 0x41, 0x41, 0x00,
    // ASCII 92 (\)
    0x02, 0x04, 0x08, 0x10, 0x20,
    // ASCII 93 (])
    0x00, 0x41, 0x41, 0x7F, 0x00,
    // ASCII 94 (^)
    0x04, 0x02, 0x01, 0x02, 0x04,
    // ASCII 95 (_)
    0x40, 0x40, 0x40, 0x40, 0x40,
    // ASCII 96 (`)
    0x00, 0x01, 0x02, 0x04, 0x00,
    // ASCII 97 (a)
    0x20, 0x54, 0x54, 0x54, 0x78,
    // ASCII 98 (b)
    0x7F, 0x44, 0x44, 0x44, 0x38,
    // ASCII 99 (c)
    0x38, 0x44, 0x44, 0x44, 0x28,
    // ASCII 100 (d)
    0x38, 0x44, 0x44, 0x44, 0x7F,
    // ASCII 101 (e)
    0x38, 0x54, 0x54, 0x54, 0x18,
    // ASCII 102 (f)
    0x08, 0x7E, 0x09, 0x01, 0x02,
    // ASCII 103 (g)
    0x18, 0xA4, 0xA4, 0xA4, 0x7C,
    // ASCII 104 (h)
    0x7F, 0x08, 0x04, 0x04, 0x78,
    // ASCII 105 (i)
    0x00, 0x44, 0x7D, 0x40, 0x00,
    // ASCII 106 (j)
    0x20, 0x40, 0x44, 0x3D, 0x00,
    // ASCII 107 (k)
    0x7F, 0x08, 0x14, 0x22, 0x41,
    // ASCII 108 (l)
    0x00, 0x41, 0x7F, 0x40, 0x00,
    // ASCII 109 (m)
    0x7C, 0x04, 0x18, 0x04, 0x78,
    // ASCII 110 (n)
    0x7C, 0x08, 0x04, 0x04, 0x78,
    // ASCII 111 (o)
    0x38, 0x44, 0x44, 0x44, 0x38,
    // ASCII 112 (p)
    0xFC, 0x24, 0x24, 0x24, 0x18,
    // ASCII 113 (q)
    0x18, 0x24, 0x24, 0x24, 0xFC,
    // ASCII 114 (r)
    0x7C, 0x08, 0x04, 0x04, 0x08,
    // ASCII 115 (s)
    0x48, 0x54, 0x54, 0x54, 0x20,
    // ASCII 116 (t)
    0x04, 0x3F, 0x44, 0x40, 0x20,
    // ASCII 117 (u)
    0x7C, 0x40, 0x40, 0x20, 0x7C,
    // ASCII 118 (v)
    0x0E, 0x10, 0x20, 0x10, 0x0E,
    // ASCII 119 (w)
    0x7C, 0x20, 0x18, 0x20, 0x7C,
    // ASCII 120 (x)
    0x6C, 0x10, 0x10, 0x6C, 0x00,
    // ASCII 121 (y)
    0x6C, 0x10, 0x10, 0x0E, 0x00,
    // ASCII 122 (z)
    0x4C, 0x54, 0x54, 0x54, 0x64,
    // ASCII 123 ({)
    0x00, 0x08, 0x36, 0x41, 0x00,
    // ASCII 124 (|)
    0x00, 0x00, 0x7F, 0x00, 0x00,
    // ASCII 125 (})
    0x00, 0x41, 0x36, 0x08, 0x00,
    // ASCII 126 (~)
    0x0C, 0x52, 0x52, 0x7C, 0x00
};

const sh1106_font_t sh1106_font5x7 = {
    .width = 5,
    .height = 7,
    .font = font5x7
};

static bool is_init = false;
static i2c_master_dev_handle_t i2c_dev_handle;
static uint8_t buffer[DISP_RES_128x64] = {0};

esp_err_t sh1106_init(i2c_master_bus_handle_t i2c_bus_handle)
{
    if(i2c_bus_handle == NULL)
        return ESP_ERR_INVALID_ARG;

    is_init = true;

    i2c_device_config_t i2c_dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = SH1106_I2C_ADDR,
        .scl_speed_hz = SH1106_I2C_SCL_SPEED
    };

    i2c_master_bus_add_device(i2c_bus_handle, &i2c_dev_config, &i2c_dev_handle);

    sh1106_send_double_cmd(SH1106_CMD_SETCONTRAST, 0x10);
    sh1106_send_cmd(SH1106_CMD_SETSTARTLINE);
    sh1106_send_cmd(SH1106_CMD_NORMALDISPLAY);

    sh1106_send_cmd(SH1106_CMD_SETSEGREMAP | 1);
    sh1106_send_cmd(SH1106_CMD_SETOUTPUTSCANDIR | 8);

    vTaskDelay(pdMS_TO_TICKS(100));

    sh1106_send_cmd(SH1106_CMD_DISPLAYON);

    return ESP_OK;
}

esp_err_t sh1106_deinit(void)
{
    if(!is_init)
        return ESP_ERR_INVALID_STATE;

    return i2c_master_bus_rm_device(i2c_dev_handle);
}

esp_err_t sh1106_send_cmd(uint8_t cmd)
{
    if(!is_init)
        return ESP_ERR_INVALID_VERSION;
    
    const uint8_t buf[2] = {0x00, cmd};
    return i2c_master_transmit(i2c_dev_handle, buf, sizeof(buf), -1);
}

esp_err_t sh1106_send_double_cmd(uint8_t cmd1, uint8_t cmd2)
{
    if(!is_init)
        return ESP_ERR_INVALID_STATE;
    
    const uint8_t buf[4] = {0x80, cmd1, 0x00, cmd2};
    return i2c_master_transmit(i2c_dev_handle, buf, sizeof(buf), -1);
}

esp_err_t sh1106_set_page_addr(uint8_t addr)
{
    if(addr >= (SH1106_DISP_HEIGHT >> 3))
        return ESP_ERR_INVALID_ARG;

    return sh1106_send_cmd(SH1106_CMD_SETPAGEADDR | (addr & 0x0F));
}

esp_err_t sh1106_set_col_addr(uint8_t addr)
{
    if(addr >= SH1106_DISP_WIDTH)
        return ESP_ERR_INVALID_ARG;

    esp_err_t err;
    if((err = sh1106_send_cmd(SH1106_CMD_SETLOWCOLADDR | (addr & 0x0F))))
        return err;
    
    if((err = sh1106_send_cmd(SH1106_CMD_SETHIGHCOLADDR | ((addr >> 4) & 0x0F))))
        return err;
    
    return ESP_OK;
}

esp_err_t sh1106_write_data(const uint8_t *const data, size_t size)
{
    if(data == NULL)
        return ESP_ERR_INVALID_ARG;
    
    if(size > DISP_RES_128x64)
        return ESP_ERR_INVALID_SIZE;
    
    uint8_t *buf = calloc(size + 1, sizeof(uint8_t));
    if(buf == NULL)
        return ESP_ERR_NO_MEM;
    
    buf[0] = 0x40;
    memcpy(buf + 1, data, size);

    i2c_master_transmit(i2c_dev_handle, buf, size + 1, -1);

    free(buf);

    return ESP_OK;   
}

esp_err_t sh1106_cpy_buf_to_disp(void)
{
    if(!is_init)
        return ESP_ERR_INVALID_STATE;

    for(uint8_t page_addr = 0; page_addr < (SH1106_DISP_HEIGHT >> 3); page_addr++)
    {
        sh1106_set_page_addr(page_addr);
        sh1106_set_col_addr(0x02);

        sh1106_send_cmd(SH1106_CMD_RMWSTART);
        sh1106_write_data(buffer + SH1106_DISP_WIDTH * page_addr, SH1106_DISP_WIDTH);
        sh1106_send_cmd(SH1106_CMD_RMWEND);
    }

    return ESP_OK;
}

void sh1106_buf_clear(void)
{
    memset(buffer, 0, DISP_RES_128x64);
}

void sh1106_buf_set_pixel_on(uint8_t x, uint8_t y)
{
    if(x >= SH1106_DISP_WIDTH)
        x = SH1106_DISP_WIDTH - 1;
    
    if(y >= SH1106_DISP_HEIGHT)
        y = SH1106_DISP_HEIGHT - 1;
    
    buffer[x + SH1106_DISP_WIDTH * (y >> 3)] |= 1 << (y % 8);
}

void sh1106_buf_set_pixel_off(uint8_t x, uint8_t y)
{
    if(x >= SH1106_DISP_WIDTH)
        x = SH1106_DISP_WIDTH - 1;
    
    if(y >= SH1106_DISP_HEIGHT)
        y = SH1106_DISP_HEIGHT - 1;
    
    buffer[x + SH1106_DISP_WIDTH * (y >> 3)] &= ~(1 << (y % 8));
}

esp_err_t sh1106_buf_set_char(uint8_t x, uint8_t y, char c, const sh1106_font_t *const font)
{
    if(font == NULL)
        return ESP_ERR_INVALID_ARG;
    
    if(c < 32 || c > 126)
        c = 32;

    const uint8_t num_of_pages = (font->height >> 3) + 1;
    const uint8_t num_of_cols = font->width;

    uint8_t *data = calloc((num_of_pages + 1) * num_of_cols, sizeof(uint8_t));
    uint8_t byte;

    for(uint8_t col = 0; col < num_of_cols; col++)
    {
        for(uint8_t page = 0; page <= num_of_pages; page++)
        {
            if(page == num_of_pages)
                byte = font->font[col + num_of_cols*((c - 32)*num_of_pages + page - 1)] >> (8 - y % 8);
            else
                byte = font->font[col + num_of_cols*((c - 32)*num_of_pages + page)] << (y % 8);
            
            data[col + num_of_cols * page] = buffer[x + col + SH1106_DISP_WIDTH * ((y >> 3) + page)] | byte;
        }
    }

    for(uint8_t page = 0; page <= num_of_pages; page++)
    {
        memcpy(buffer + x + SH1106_DISP_WIDTH * ((y >> 3) + page), data + num_of_cols * page, num_of_cols);
    }

    free(data);

    return ESP_OK;
}

esp_err_t sh1106_buf_set_text(uint8_t x, uint8_t y, const char *text, const sh1106_font_t *const font)
{
    if(text == NULL || font == NULL)
        return ESP_ERR_INVALID_ARG;
    
    while(*text)
    {
        sh1106_buf_set_char(x, y, *text, font);

        x += font->width + 1;
        text++;
    }

    return ESP_OK;
}
