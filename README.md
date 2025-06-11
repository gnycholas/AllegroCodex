# AllegroCodex

Este repositório contém um exemplo simples de jogo Pong utilizando a biblioteca Allegro 5.

## Compilação

Para compilar o exemplo, certifique-se de ter a biblioteca Allegro 5 instalada em seu sistema.
Use o comando abaixo:

```bash
gcc simple_pong.c -o simple_pong \
  $(pkg-config --libs --cflags allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_main-5)
```

## Execução

Após compilar, execute o binário:

```bash
./simple_pong
```

Use as teclas **seta para cima** e **seta para baixo** para mover sua raquete. O adversário é controlado por uma IA simples.
