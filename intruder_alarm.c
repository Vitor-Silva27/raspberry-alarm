#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

/* definindo pinos do led e microfone */
#define LED_PIN 12
#define MIC_CHANNEL 2
#define MIC_PIN 28


int main()
{
    stdio_init_all();

    /* iniciando e configurando pinos */
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    adc_gpio_init(MIC_PIN);
    adc_init();
    adc_select_input(MIC_CHANNEL);


    while (true) {
        uint16_t noise = adc_read();
        printf("%u\n", noise);
        gpio_put(LED_PIN, 1);
        sleep_ms(1000);
        gpio_put(LED_PIN, 0);
        sleep_ms(1000);
    }
}
