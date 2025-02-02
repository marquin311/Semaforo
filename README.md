Inicialização dos LEDs:

Configura GPIOs 11, 12 e 13 como saída.
O LED vermelho acende primeiro.

Configuração do Timer:

O temporizador add_repeating_timer_ms(3000, mudar_sinal_callback, NULL, &timer_semaforo); chama a função mudar_sinal_callback() a cada 3 segundos.

Callback do Timer (mudar_sinal_callback):

Desliga todos os LEDs.
Alterna o estado do semáforo (Vermelho → Amarelo → Verde → Vermelho).
Liga o LED correspondente ao novo estado.

Loop Principal (while):

Imprime o estado atual do semáforo no terminal UART a cada 1 segundo.
