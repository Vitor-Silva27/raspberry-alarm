#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

/* definindo pinos do led e microfone */
#define LED_PIN 12
#define MIC_CHANNEL 2
#define MIC_PIN 28

#define SAMPLES 200
#define MIN_NOISE 2500

uint16_t adc_buffer[SAMPLES];
bool led_state = false;

/* prototipos de funcção */
void sample_mic();
uint16_t get_peak();

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
        sample_mic();
        int16_t peak = get_peak();
        
        /* verificando se o som é mais alto que o valor minimo que defini */
        if (peak > MIN_NOISE) {
            /* alternando o valor do estado do led, para mantelo apagado ou aceso */
            led_state = !led_state;
            gpio_put(LED_PIN, led_state);
            sleep_ms(500);
        }
        
        printf("%u\n", peak);
    }
}


/* lendo o microfone a diconando em um buffer, para ter uma leitura mais precisa */
void sample_mic() {
    for (uint i = 0; i < SAMPLES; i++) {
        adc_buffer[i] = adc_read();
    }
}

/* pegando o som mais alto */
uint16_t get_peak() {
    uint16_t max_value = 0;
    for (uint i = 0; i < SAMPLES; i++) {
        if (adc_buffer[i] > max_value) {
            max_value = adc_buffer[i];
        }
    }
    return max_value;
}