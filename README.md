
## Animação de Cubos 3D em Terminal
Este programa em C exibe uma animação de cubos em uma tela de terminal. Ele calcula a projeção 3D dos cubos e utiliza uma técnica de buffer para desenhá-los com diferentes caracteres ASCII, resultando em uma visualização em 2D da rotação dos cubos.

## Descrição
O programa projeta cubos 3D em um espaço 2D utilizando cálculos matemáticos para determinar a posição e rotação dos cubos. A técnica de buffer utilizada assegura que a renderização seja feita de maneira eficiente, permitindo uma animação suave. Os cubos são representados por caracteres ASCII variados, criando uma visualização interessante na interface do terminal.

## Funcionalidades
Projeção 3D de cubos em um espaço 2D

Animação de rotação dos cubos

Utilização de caracteres ASCII para a representação gráfica

Técnica de buffer para renderização eficiente

## Requisitos
Compilador C (por exemplo, GCC)

Terminal compatível com ANSI

## Como Compilar e Executar
1. Clone o repositório ou baixe os arquivos do programa.

2. Abra o terminal e navegue até o diretório onde os arquivos estão localizados.

3. Compile o programa utilizando o compilador C:

```bash

gcc -o animacao_cubos animacao_cubos.c -lm
```

4. Execute o programa:
```bash
./animacao_cubos
```     
## Uso
Ao executar o programa, a animação dos cubos será exibida no terminal. Use as teclas de controle (se implementadas) para interagir com a animação e explorar diferentes perspectivas dos cubos.
