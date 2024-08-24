#include "sh1106.h"

#define I2C_CLK_SRC I2C_CLK_SRC_DEFAULT
#define I2C_PORT I2C_NUM_0
#define I2C_SCL GPIO_NUM_22
#define I2C_SDA GPIO_NUM_21

void app_main(void)
{
    i2c_master_bus_handle_t i2c_bus_handle;

    i2c_master_bus_config_t i2c_bus_config = {
        .clk_source = I2C_CLK_SRC,
        .i2c_port = I2C_PORT,
        .scl_io_num = I2C_SCL,
        .sda_io_num = I2C_SDA,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true
    };

    i2c_new_master_bus(&i2c_bus_config, &i2c_bus_handle);

    sh1106_init(&i2c_bus_handle);
    sh1106_buf_clear();

    sh1106_buf_set_char(0, 0, 'a', &sh1106_font5x7);
    sh1106_buf_set_char(6, 0, 'b', &sh1106_font5x7);
    sh1106_buf_set_char(12, 0, 'c', &sh1106_font5x7);
    sh1106_buf_set_char(18, 0, 'd', &sh1106_font5x7);

    sh1106_buf_set_char(24, 4, '1', &sh1106_font5x7);
    sh1106_buf_set_char(30, 4, '2', &sh1106_font5x7);
    sh1106_buf_set_char(36, 4, '3', &sh1106_font5x7);

    sh1106_buf_set_char(24, 12, 'A', &sh1106_font5x7);
    sh1106_buf_set_char(30, 12, 'A', &sh1106_font5x7);
    //sh1106_buf_set_char(30, 12, 'T', &sh1106_font5x7);

    sh1106_cpy_buf_to_disp();

    while(true)
    {
        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    sh1106_deinit();
}
