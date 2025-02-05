#include <stdio.h>
#include <hardware/timer.h>
#include <pico/stdlib.h>

// Definição dos pinos dos LEDs RGB
#define LED_PIN_RED 13
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12

// Definição do pino do botão
#define BUTTON_PIN 5

// Definição do tempo de debounce e intervalo de desligamento dos LEDs
#define DEBOUNCE_TIME_MS 50
#define LED_OFF_INTERVAL_MS 3000

// Enumeração para os estados dos LEDs
typedef enum
{
    LED_STATE_RED,
    LED_STATE_GREEN,
    LED_STATE_BLUE,
    LED_STATE_OFF
} LedState;

// Variáveis para controle do estado do LED
static LedState led_state = LED_STATE_OFF;
static bool led_on = false;

// Função de callback para o timer
int64_t turn_off_callback(alarm_id_t id, void *user_data)
{
    switch (led_state)
    {
    case LED_STATE_RED:
        gpio_put(LED_PIN_RED, 0);
        printf("RED OFF\n");
        led_state = LED_STATE_GREEN;
        add_alarm_in_ms(LED_OFF_INTERVAL_MS, turn_off_callback, NULL, false);
        break;

    case LED_STATE_GREEN:
        gpio_put(LED_PIN_GREEN, 0);
        printf("GREEN OFF\n");
        led_state = LED_STATE_BLUE;
        add_alarm_in_ms(LED_OFF_INTERVAL_MS, turn_off_callback, NULL, false);
        break;

    case LED_STATE_BLUE:
        gpio_put(LED_PIN_BLUE, 0);
        printf("BLUE OFF\n");
        led_state = LED_STATE_OFF;
        led_on = false; // Todos os LEDs foram desligados
        break;

    default:
        break;
    }

    return 0;
}

// Função para inicializar os pinos
void initialize_pins()
{
    // Inicialização dos pinos dos LEDs
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);

    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);

    // Inicialização do botão
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);
}

// Função principal
int main()
{
    // Inicialização serial
    stdio_init_all();

    // Inicialização dos pinos
    initialize_pins();

    // Loop infinito
    while (true)
    {
        // Verifica se o botão foi pressionado
        if (gpio_get(BUTTON_PIN) == 0 && !led_on)
        {
            sleep_ms(DEBOUNCE_TIME_MS); // Debounce

            // Confirma se o botão ainda está pressionado após debounce
            if (gpio_get(BUTTON_PIN) == 0)
            {
                // Acende todos os LEDs
                gpio_put(LED_PIN_RED, 1);
                gpio_put(LED_PIN_GREEN, 1);
                gpio_put(LED_PIN_BLUE, 1);

                // Atualiza o estado do LED
                led_on = true;
                led_state = LED_STATE_RED;

                // Agenda o primeiro callback para desligar os LEDs após 3 segundos
                add_alarm_in_ms(LED_OFF_INTERVAL_MS, turn_off_callback, NULL, false);
            }
        }

        // Evitar sobrecarga na CPU
        sleep_ms(10);
    }

    return 0;
}