## Descrição

Este projeto tem como objetivo controlar os três LEDs RGB da placa Raspberry Pi Pico W, acionando cada cor em um intervalo de 3 segundos, de maneira sequencial e ininterrupta.

## Funcionamento

O funcionamento do código segue a seguinte lógica:

1. O LED vermelho acende e permanece ligado por 3 segundos.
2. Em seguida, o LED verde é ativado por 3 segundos.
3. Depois, o LED azul é acionado, também por 3 segundos.
4. O ciclo reinicia a partir do primeiro passo, repetindo-se indefinidamente.

## Exemplo de Execução

Quando o código é executado, os LEDs seguem o seguinte padrão:

- **3s** - LED vermelho ligado
- **3s** - LED verde ligado
- **3s** - LED azul ligado
- Reinicia o ciclo

Este exemplo ilustra um controle básico de LEDs na Raspberry Pi Pico W, sendo útil para aprendizagem e testes com GPIOs e temporização na plataforma.
