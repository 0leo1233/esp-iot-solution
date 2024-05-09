/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ntc_driver.h"

const static char *TAG = "NTC demo";

/**
 * @brief ADC1 Channels
 */
#define EXAMPLE_ADC1_CHAN3          ADC_CHANNEL_3
#define EXAMPLE_ADC_ATTEN           ADC_ATTEN_DB_11

void app_main(void)
{
    //Select the NTC sensor and initialize the hardware parameters
    ntc_config_t ntc_config = {
        .b_value = 3950,
        .r25_ohm = 10000,
        .fixed_ohm = 10000,
        .vdd_mv = 3300,
        .atten = EXAMPLE_ADC_ATTEN,
        .channel = EXAMPLE_ADC1_CHAN3,
        .unit = ADC_UNIT_1
    };

    //Create the NTC Driver and Init ADC
    ntc_device_handle_t ntc = NULL;
    adc_oneshot_unit_handle_t adc_handle = NULL;
    ESP_ERROR_CHECK(ntc_dev_create(&ntc_config, &ntc, &adc_handle));
    ESP_ERROR_CHECK(ntc_dev_get_adc_handle(ntc, &adc_handle));

    for (int i = 0; i < 10; i++) {
        float temp = ntc_dev_get_temperature(ntc);
        ESP_LOGI(TAG, "NTC temperature = %.2f ℃", temp);
    }
    ESP_ERROR_CHECK(ntc_dev_delete(ntc));
}
