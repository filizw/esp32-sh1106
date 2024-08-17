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

    while(true)
    {
        sh1106_clear(handle, 0x00);
        vTaskDelay(pdMS_TO_TICKS(3000));
        sh1106_clear(handle, 0xFF);
        vTaskDelay(pdMS_TO_TICKS(3000));
    }

    sh1106_deinit(&handle);
}
