#include "sh1106.h"

#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

void app_main(void)
{
    sh1106_handle_t handle;

    sh1106_config_t config = {
        .i2c_port = I2C_NUM_0,
        .i2c_scl = GPIO_NUM_22,
        .i2c_sda = GPIO_NUM_21,
        .display_width = DISPLAY_WIDTH,
        .display_height = DISPLAY_HEIGHT
    };

    sh1106_init(&handle, &config);
    sh1106_clear(handle, 0x00);

    sh1106_draw_character(handle, 0, 0, 'a', &sh1106_font5x7);
    sh1106_draw_character(handle, 6, 0, 'b', &sh1106_font5x7);
    sh1106_draw_character(handle, 12, 0, 'c', &sh1106_font5x7);
    sh1106_draw_character(handle, 18, 0, 'd', &sh1106_font5x7);

    sh1106_draw_character(handle, 24, 4, '1', &sh1106_font5x7);
    sh1106_draw_character(handle, 30, 4, '2', &sh1106_font5x7);
    sh1106_draw_character(handle, 36, 4, '3', &sh1106_font5x7);

    sh1106_draw_character(handle, 24, 12, 'A', &sh1106_font5x7);
    sh1106_draw_character(handle, 30, 12, 'A', &sh1106_font5x7);
    //sh1106_draw_character(handle, 30, 12, 'T', &sh1106_font5x7);

    sh1106_write_memory(handle);

    while(true)
    {
        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    sh1106_deinit(&handle);
}
