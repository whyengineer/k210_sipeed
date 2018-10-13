/* Copyright 2018 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>
#include <unistd.h>
#include "devices.h"
#include "pin_cfg.h"
//the name must be g_fpioa_cfg
const fpioa_cfg_t g_fpioa_cfg={
    .version= PIN_CFG_VERSION,
    .functions_count=3,
    .functions={
        {.number=13,.function=FUNC_GPIO5},
        {.number=14,.function=FUNC_GPIO6},
        {.number=16,.function=FUNC_GPIOHS0}
    }
};
const power_bank_cfg_t g_power_bank_cfg={
    .version= PIN_CFG_VERSION,
    .power_banks_count=1,
    .power_banks={
        {
            .power_bank=SYSCTL_POWER_BANK2,
            .io_power_mode=SYSCTL_POWER_V33
        }
    }
};
static handle_t gpioHsH;
static handle_t gpioH;
void gpio_on_changed(uint32_t pin, void *userdata){
    //handle_t gpioHsH=(handle_t)(*userdata);
    if(gpio_get_pin_value(gpioHsH,pin)){
        gpio_set_pin_value(gpioH,5,1);
    }else{
        gpio_set_pin_value(gpioH,5,0);
    }
}
int main()
{
    gpioHsH=io_open("/dev/gpio0");
    gpioH=io_open("/dev/gpio1");

    //output led
    gpio_set_drive_mode(gpioH,6,GPIO_DM_OUTPUT);
    gpio_set_drive_mode(gpioH,5,GPIO_DM_OUTPUT);
    gpio_set_pin_value(gpioH,6,1);
    gpio_set_pin_value(gpioH,5,1);

    //input key
    gpio_set_drive_mode(gpioHsH,0,GPIO_DM_INPUT_PULL_UP);
    gpio_set_pin_edge(gpioHsH,0,GPIO_PE_BOTH);
    //install callback
    gpio_set_on_changed(gpioHsH,0,gpio_on_changed,NULL);

    uint32_t cnt=0;
    while (1)
    {   
        gpio_set_pin_value(gpioH,6,cnt%2);
        sleep(1);
        cnt++;
    }
}
