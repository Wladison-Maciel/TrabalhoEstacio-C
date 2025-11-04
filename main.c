#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_NOME 30
#define MAX_COR 10

// Struct que representa um território
typedef struct {
    char nome[MAX_NOME];
    char cor[MAX_COR]; // cor do exército que controla o território
    int tropas;
} Territorio;

/* ---------- PROTÓTIPOS ---------- */
void cadastrarTerritorios(Territorio *mapa, int qtd);
void exibirMapa(Territorio *mapa, int qtd);
void atacar(Territorio *atacante, Territorio *defensor);
void liberarMemoria(Territorio *mapa, char **missoesJogadores, int numPlayers);
void atribuirMissao(char **destino, char *missoes[], int totalMissoes);
int verificarMissao(char *missao, Territorio *mapa, int tamanho, char *corJogador);
void exibirMissao(const char *missao);

/* ---------- Implementações ---------- */

// cadastra territórios (uso de scanf("%s") — não aceita espaços)
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// exibe o estado atual do mapa
void exibirMapa(Territorio *mapa, int qtd) {
    printf("\n====== MAPA ATUAL ======\n");
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n", i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// função que simula ataque entre territórios usando ponteiros
void atacar(Territorio *atacante, Territorio *defensor) {
    // validações externas devem garantir que cores são diferentes e atacante tenha tropas > 1
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Não é possível atacar território da mesma cor.\n");
        return;
    }
    if (atacante->tropas <= 1) {
        printf("Erro: Atacante precisa ter mais de 1 tropa para atacar.\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1; // 1..6
    int dadoDefensor = (rand() % 6) + 1;  // 1..6

    printf("\nRolagem de dados: %s(atacante) -> %d | %s(defensor) -> %d\n",
           atacante->nome, dadoAtacante, defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: Ataque bem-sucedido! %s conquista %s\n", atacante->nome, defensor->nome);

        // transfere cor
        strcpy(defensor->cor, atacante->cor);

        // transfere metade das tropas do atacante para o defensor (arredonda para baixo)
        int transferidas = atacante->tropas / 2;
        if (transferidas < 1) transferidas = 1; // garante ao menos 1 se possível

        defensor->tropas = transferidas;
        atacante->tropas -= transferidas;
    } else {
        printf("Resultado: Ataque falhou. %s perde 1 tropa.\n", atacante->nome);
        atacante->tropas -= 1;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

// atribui uma missão aleatória para destino (destino é char** — alocação dinâmica feita aqui)
void atribuirMissao(char **destino, char *missoes[], int totalMissoes) {
    int idx = rand() % totalMissoes;
    size_t len = strlen(missoes[idx]);
    *destino = (char *) malloc((len + 1) * sizeof(char));
    if (*destino == NULL) {
        printf("Erro ao alocar memória para missão!\n");
        exit(1);
    }
    strcpy(*destino, missoes[idx]);
}

// exibe missão (passagem por valor da string)
void exibirMissao(const char *missao) {
    printf("\n--- MISSÃO ATRIBUÍDA ---\n%s\n", missao);
}

// verificarMissao: retorna 1 se cumprida, 0 caso contrário
// NOTA: adicionei o parâmetro corJogador para saber qual cor pertence ao jogador
int verificarMissao(char *missao, Territorio *mapa, int tamanho, char *corJogador) {
    // Missões suportadas (strings exatas)
    // "Conquistar 3 territorios seguidos"
    // "Eliminar todas as tropas da cor Vermelha"
    // "Controlar 5 territorios"
    // "Controlar 50% dos territorios"
    // "Ter 3 territorios com mais de 10 tropas"

    if (strcmp(missao, "Conquistar 3 territorios seguidos") == 0) {
        // verificar se existe sequência de 3 territórios consecutivos controlados pela corJogador
        if (tamanho < 3) return 0;
        for (int i = 0; i <= tamanho - 3; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 &&
                strcmp(mapa[i+1].cor, corJogador) == 0 &&
                strcmp(mapa[i+2].cor, corJogador) == 0) {
                return 1;
            }
        }
        return 0;
    }

    if (strcmp(missao, "Eliminar todas as tropas da cor Vermelha") == 0) {
        // soma de tropas de cor "Vermelha" deve ser zero
        for (int i = 0; i < tamanho; i++) {
            if (strcasecmp(mapa[i].cor, "Vermelha") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }

    if (strcmp(missao, "Controlar 5 territorios") == 0) {
        int cont = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) cont++;
        }
        return (cont >= 5) ? 1 : 0;
    }

    if (strcmp(missao, "Controlar 50% dos territorios") == 0) {
        int cont = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) cont++;
        }
        // >= 50% (arredonda para cima)
        int necessario = (tamanho + 1) / 2;
        return (cont >= necessario) ? 1 : 0;
    }

    if (strcmp(missao, "Ter 3 territorios com mais de 10 tropas") == 0) {
        int cont = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0 && mapa[i].tropas > 10) cont++;
        }
        return (cont >= 3) ? 1 : 0;
    }

    // missão desconhecida -> não cumprida
    return 0;
}

// libera a memória alocada (mapa e vetor de missões)
void liberarMemoria(Territorio *mapa, char **missoesJogadores, int numPlayers) {
    if (mapa) free(mapa);
    if (missoesJogadores) {
        for (int i = 0; i < numPlayers; i++) {
            if (missoesJogadores[i]) free(missoesJogadores[i]);
        }
        free(missoesJogadores);
    }
}

/* ---------- MAIN: fluxo do jogo simplificado ---------- */
int main() {
    srand((unsigned int) time(NULL));

    // Definição de missões possíveis (pelo menos 5)
    char *missoesDisponiveis[] = {
        "Conquistar 3 territorios seguidos",
        "Eliminar todas as tropas da cor Vermelha",
        "Controlar 5 territorios",
        "Controlar 50% dos territorios",
        "Ter 3 territorios com mais de 10 tropas"
    };
    int totalMissoes = sizeof(missoesDisponiveis) / sizeof(missoesDisponiveis[0]);

    int numPlayers = 2; // este exercício considera 2 jogadores
    char **missoesJogadores = (char **) malloc(numPlayers * sizeof(char *));
    if (missoesJogadores == NULL) {
        printf("Erro ao alocar memória para missões dos jogadores.\n");
        return 1;
    }
    for (int i = 0; i < numPlayers; i++) missoesJogadores[i] = NULL;

    // Informações dos jogadores: nome e cor
    char nomes[2][MAX_NOME];
    char coresJogadores[2][MAX_COR];

    for (int i = 0; i < numPlayers; i++) {
        printf("Nome do jogador %d: ", i + 1);
        scanf("%s", nomes[i]);
        printf("Cor do jogador %d: ", i + 1);
        scanf("%s", coresJogadores[i]);
    }

    // Pergunta quantos territórios criar
    int qtdTerritorios;
    printf("Quantos territórios deseja cadastrar no mapa? ");
    scanf("%d", &qtdTerritorios);

    // alocação dinâmica do mapa de territórios
    Territorio *mapa = (Territorio *) calloc(qtdTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa.\n");
        free(missoesJogadores);
        return 1;
    }

    // cadastro dos territórios
    cadastrarTerritorios(mapa, qtdTerritorios);

    // atribuir missão para cada jogador (aloca dinamicamente string)
    for (int i = 0; i < numPlayers; i++) {
        atribuirMissao(&missoesJogadores[i], missoesDisponiveis, totalMissoes);
        printf("\nJogador %s recebeu sua missão (mostrada apenas uma vez):\n", nomes[i]);
        exibirMissao(missoesJogadores[i]);
    }

    // Loop principal: jogadores escolhem ataques alternadamente
    int jogadorAtual = 0;
    int vencedor = -1;
    while (1) {
        printf("\n----- Turno do jogador %s (cor: %s) -----\n", nomes[jogadorAtual], coresJogadores[jogadorAtual]);
        exibirMapa(mapa, qtdTerritorios);

        // verificar missão silenciosamente ao início do turno
        if (verificarMissao(missoesJogadores[jogadorAtual], mapa, qtdTerritorios, coresJogadores[jogadorAtual])) {
            vencedor = jogadorAtual;
            printf("\nParabéns %s! Você já cumpriu sua missão e venceu!\n", nomes[jogadorAtual]);
            break;
        }

        int idxAtacante, idxDefensor;
        printf("Escolha índice do território atacante (-1 para sair): ");
        scanf("%d", &idxAtacante);
        if (idxAtacante == -1) { // sair do loop
            printf("Jogo interrompido pelo usuário.\n");
            break;
        }
        printf("Escolha índice do território defensor: ");
        scanf("%d", &idxDefensor);

        // validações
        if (idxAtacante < 0 || idxAtacante >= qtdTerritorios || idxDefensor < 0 || idxDefensor >= qtdTerritorios) {
            printf("Índices inválidos. Tente novamente.\n");
            continue;
        }
        if (strcmp(mapa[idxAtacante].cor, coresJogadores[jogadorAtual]) != 0) {
            printf("Você só pode atacar com um território que você controla (cor: %s).\n", coresJogadores[jogadorAtual]);
            continue;
        }
        if (strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
            printf("Você não pode atacar um território da sua própria cor.\n");
            continue;
        }
        if (mapa[idxAtacante].tropas <= 1) {
            printf("Território atacante precisa ter mais de 1 tropa para atacar.\n");
            continue;
        }

        // realiza ataque (usa ponteiros)
        atacar(&mapa[idxAtacante], &mapa[idxDefensor]);

        // após ataque, verifica se jogador cumpriu missão
        if (verificarMissao(missoesJogadores[jogadorAtual], mapa, qtdTerritorios, coresJogadores[jogadorAtual])) {
            vencedor = jogadorAtual;
            printf("\nParabéns %s! Você cumpriu sua missão e venceu!\n", nomes[jogadorAtual]);
            break;
        }

        // troca de jogador
        jogadorAtual = (jogadorAtual + 1) % numPlayers;
    }

    // exibe mapa final
    exibirMapa(mapa, qtdTerritorios);

    // libera memória
    liberarMemoria(mapa, missoesJogadores, numPlayers);

    printf("\nFim do jogo. Memória liberada.\n");
    return 0;
}
