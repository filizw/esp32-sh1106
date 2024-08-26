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

    sh1106_init(i2c_bus_handle);
    sh1106_inv_x_axis(true);
    sh1106_inv_y_axis(true);
    sh1106_clear();

    sh1106_write_text(10, 18, "HELLO WORLD!", &sh1106_font8x16);

    uint8_t data[10 * 2];
    memset(data, 0xFF, 20);
    sh1106_write_data(50, 43, data, 10, 2);
    sh1106_display();

    bool rev = false;
    int8_t step = 2;

    while(true)
    {
        for(uint8_t i = 0; i < SH1106_DISP_WIDTH; i += 2)
        {
            sh1106_set_pixel(i, 10, SH1106_PIXEL_ON);
            
            if(i >= 10)
                sh1106_set_pixel(i - 10, 10, SH1106_PIXEL_OFF);
            else
                sh1106_set_pixel(SH1106_DISP_WIDTH + i - 10, 10, SH1106_PIXEL_OFF);
            
            sh1106_display();

            vTaskDelay(pdMS_TO_TICKS(100));

            sh1106_scroll(step);
        }

        step *= -1;

        rev = !rev;
        sh1106_reverse(rev);
    }

    sh1106_deinit();
}
