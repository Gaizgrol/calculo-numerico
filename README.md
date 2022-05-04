# Cálculo Numérico - UFRJ 2022.1

Repositório para guardar as implementações dos métodos numéricos vistos em sala de aula.

## Requisitos
- GCC com suporte à especificação C++17
- Uma máquina com suporte a números de ponto flutuante de precisão de 128 bits

## Executando o projeto

Compile o projeto com

```sh
g++ main.cc methods.cc -std=c++17
```

e execute com

```sh
./a.out
```

## Tipos novos

Os tipos de ponto flutuante padrão foram renomeados para uma forma mais consistente (parecido com as nomeações de `stdint.h`). Os novos tipos estão definidos em `floats.h` e possuem a seguinte implementação:

```cpp
typedef float           float32_t;
typedef double          float64_t;
typedef long double     float128_t;
```