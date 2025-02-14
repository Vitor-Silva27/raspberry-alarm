#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

/* definindo pinos do led e microfone */
#define LED_PIN 13
#define MIC_CHANNEL 2
#define MIC_PIN 28

#define SAMPLES 200
#define MIN_NOISE 2200

#define BTN 5

#define BUZZER_PIN 21
#define BUZZER_FREQUENCY 1000

uint16_t adc_buffer[SAMPLES];
bool alarm_activated = false;

/* prototipos de função */
void sample_mic();
uint16_t get_peak();
void disableAlarmIRQ();
void beep(uint pin, uint duration_ms);

int main()
{
    stdio_init_all();

    /* iniciando e configurando pinos */
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    adc_gpio_init(MIC_PIN);
    adc_init();
    adc_select_input(MIC_CHANNEL);

    gpio_init(BTN);
    gpio_set_dir(BTN, 0);
    gpio_pull_up(BTN);

    gpio_set_function(BUZZER_PIN, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(BUZZER_PIN);

    /* Configurar o PWM para o buzer */
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, clock_get_hz(clk_sys) / (BUZZER_FREQUENCY * 4096));
    pwm_init(slice_num, &config, true);
    pwm_set_gpio_level(BUZZER_PIN, 0);

    /* configurando interrupção para parar o alarme */
    gpio_set_irq_enabled_with_callback(BTN, GPIO_IRQ_EDGE_RISE, true, &disableAlarmIRQ);


    while (true) {
        sample_mic();
        int16_t peak = get_peak();
        
        if (peak > MIN_NOISE) {
            alarm_activated = true;
        }

        if (alarm_activated) {
            printf("ALERTA DE INTRUSO!!!\n");
            beep(BUZZER_PIN, 200);
            gpio_put(LED_PIN, 1);
            sleep_ms(300);
            gpio_put(LED_PIN, 0);
            sleep_ms(300);
        }
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

void disableAlarmIRQ(){
    alarm_activated = false;
}

void beep(uint pin, uint duration_ms) {
    // Obter o slice do PWM associado ao pino
    uint slice_num = pwm_gpio_to_slice_num(pin);

    pwm_set_gpio_level(pin, 2048);
    sleep_ms(duration_ms);
    pwm_set_gpio_level(pin, 0);

    // Pausa entre os beeps
    sleep_ms(100);
}