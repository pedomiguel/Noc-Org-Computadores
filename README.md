# Projeto Redes em Chipe (Trabalho Unidade 2 Organização de Computadores - DIM0129)

## Setup

Exporte a variável de ambiente `SYSTEMC_PATH` apontando para onde está instalado o systemc

Exemplos:
```sh
export SYSTEMC_PATH="$HOME/systemc/install"
export SYSTEMC_PATH="$HOME/systemc-install"
```

## Rodando

```sh
make build
make build/test_top
make run-top size=<size> algorithm=<algorithm> pkg_size=<pkg_size>
```

- `<size>` - Tamanho da dimensão da rede (um quadrado de tamanho `size`*`size`)
- `<algorithm> - Algoritmo de roteamento dos roteadores, `0` para XY `1` para WEST_FIRST
- `<pkg_size>` - Quantidade de pacotes para serem trafegados na rede