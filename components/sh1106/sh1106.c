#include "sh1106.h"

#define SH1106_I2C_ADDR 0x3C
#define SH1106_I2C_SCL_SPEED 100000

struct sh1106_t
{
    i2c_master_bus_handle_t i2c_bus_handle;
    i2c_master_dev_handle_t i2c_dev_handle;

    uint8_t display_width;
    uint8_t display_height;
};

esp_err_t sh1106_init(sh1106_handle_t *handle, const sh1106_config_t *const config)
{
    if(handle == NULL || config == NULL)
        return ESP_ERR_INVALID_ARG;
    
    *handle = malloc(sizeof(struct sh1106_t));
    if(*handle == NULL)
        return ESP_ERR_NO_MEM;
    
    (*handle)->display_width = config->display_width;
    (*handle)->display_height = config->display_height;

    i2c_master_bus_config_t i2c_bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = config->i2c_port,
        .scl_io_num = config->i2c_scl,
        .sda_io_num = config->i2c_sda,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true
    };

    i2c_new_master_bus(&i2c_bus_config, &((*handle)->i2c_bus_handle));

    i2c_device_config_t i2c_dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = SH1106_I2C_ADDR,
        .scl_speed_hz = SH1106_I2C_SCL_SPEED
    };

    i2c_master_bus_add_device((*handle)->i2c_bus_handle, &i2c_dev_config, &((*handle)->i2c_dev_handle));

    sh1106_send_command_with_byte(*handle, SH1106_COMMAND_SETCONTRAST, 0x10);
    sh1106_send_command(*handle, SH1106_COMMAND_SETSTARTLINE);
    sh1106_send_command(*handle, SH1106_COMMAND_NORMALDISPLAY);

    vTaskDelay(pdMS_TO_TICKS(100));

    sh1106_send_command(*handle, SH1106_COMMAND_DISPLAYON);

    return ESP_OK;
}

esp_err_t sh1106_deinit(sh1106_handle_t *handle)
{
    if(handle == NULL || *handle == NULL)
        return ESP_ERR_INVALID_ARG;
    
    i2c_master_bus_rm_device((*handle)->i2c_dev_handle);
    i2c_del_master_bus((*handle)->i2c_bus_handle);

    free(*handle);
    *handle = NULL;

    return ESP_OK;
}

esp_err_t sh1106_send_command(const sh1106_handle_t handle, const uint8_t command)
{
    if(handle == NULL)
        return ESP_ERR_INVALID_ARG;
    
    const uint8_t buffer[2] = {0x00, command};
    i2c_master_transmit(handle->i2c_dev_handle, buffer, sizeof(buffer), -1);

    return ESP_OK;
}

esp_err_t sh1106_send_command_with_byte(const sh1106_handle_t handle, const uint8_t command, const uint8_t byte)
{
    if(handle == NULL)
        return ESP_ERR_INVALID_ARG;
    
    const uint8_t buffer[4] = {0x80, command, 0x00, byte};
    i2c_master_transmit(handle->i2c_dev_handle, buffer, sizeof(buffer), -1);

    return ESP_OK;
}