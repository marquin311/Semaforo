#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_VERMELHO 13
#define LED_AMARELO 12
#define LED_VERDE 11

// Estados do semáforo
typedef enum {
    VERMELHO,
    AMARELO,
    VERDE
} EstadoSemaforo;

volatile EstadoSemaforo estado_atual = VERMELHO; // Começa no vermelho

// Prototipação da função de callback
bool mudar_sinal_callback(struct repeating_timer *t);

// Timer do semáforo
struct repeating_timer timer_semaforo;

int main() {
    stdio_init_all();

    // Configuração dos LEDs
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);

    gpio_init(LED_AMARELO);
    gpio_set_dir(LED_AMARELO, GPIO_OUT);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);

    // Inicializa o semáforo no vermelho
    gpio_put(LED_VERMELHO, 1);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);

    // Timer para alterar o sinal a cada 3 segundos
    add_repeating_timer_ms(3000, mudar_sinal_callback, NULL, &timer_semaforo);

    while (true) {
        printf("Semáforo está no estado: %d\n", estado_atual);
        sleep_ms(1000); // Imprime a cada 1 segundo
    }
}

// Callback que altera os LEDs do semáforo
bool mudar_sinal_callback(struct repeating_timer *t) {
    // Desliga todos os LEDs antes de mudar de estado
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_AMARELO, 0);
    gpio_put(LED_VERDE, 0);

    // Alterna o estado do semáforo
    switch (estado_atual) {
        case VERMELHO:
            estado_atual = AMARELO;
            gpio_put(LED_AMARELO, 1);
            break;
        case AMARELO:
            estado_atual = VERDE;
            gpio_put(LED_VERDE, 1);
            break;
        case VERDE:
            estado_atual = VERMELHO;
            gpio_put(LED_VERMELHO, 1);
            break;
    }

    return true; // Mantém o timer ativo
}
