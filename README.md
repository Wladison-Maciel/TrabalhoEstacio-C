# 🎮 WAR Estruturado — Simulação com Ataques e Missões

Este projeto é uma simulação do jogo **WAR** desenvolvida em **C**, com foco em:
- Uso de ponteiros
- Alocação dinâmica de memória
- Modularização
- Lógica de batalha entre territórios
- Sistema de missões estratégicas individuais

---

## 🧠 Funcionalidades

- ✅ Cadastro dinâmico de territórios
- 🎲 Sistema de ataque com rolagem de dados (1 a 6)
- ⚔️ Conquista de territórios com mudança de cor e tropas
- 🎯 Missões estratégicas sorteadas para cada jogador
- 🏆 Verificação automática de vitória por missão
- 🧹 Liberação de memória com `free()`

---

## 📦 Estrutura da `struct Territorio`

| Campo | Tipo | Descrição |
|------|------|----------|
| `nome` | `char[30]` | Nome do território |
| `cor` | `char[10]` | Cor/controle do jogador |
| `tropas` | `int` | Quantidade de tropas |

---

## 🔧 Funções principais

| Função | Descrição |
|--------|----------|
| `atacar()` | Simula uma batalha entre dois territórios |
| `atribuirMissao()` | Sorteia missão para o jogador |
| `verificarMissao()` | Checa se a missão foi cumprida |
| `exibirMapa()` | Mostra os territórios e informações |
| `liberarMemoria()` | Libera memória alocada dinamicamente |

---

## 🛠️ Tecnologias Utilizadas

- Linguagem C
- Bibliotecas:
  - `stdio.h`
  - `stdlib.h`
  - `string.h`
  - `time.h`

---

## ▶️ Como executar

Compile com GCC:

```bash
gcc main.c -o war
```
Execute:

```bash
./war
```