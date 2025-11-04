#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios
void cadastrarTerritorios(Territorio *mapa, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i+1);

        printf("Nome: ");
        scanf("%s", mapa[i].nome);

        printf("Cor do exército: ");
        scanf("%s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibe todos os territórios cadastrados
void exibirTerritorios(Territorio *mapa, int qtd) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < qtd; i++) {
        printf("\nTerritório %d\n", i);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
    }
}

// Função que simula um ataque entre territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n❌ Você não pode atacar um território da sua própria cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("\n❌ O atacante precisa ter mais de 1 tropa para atacar!\n");
        return;
    }

    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n🎲 Dados rolados!\n");
    printf("%s (Atacante): %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n✅ Ataque bem-sucedido! Você conquistou o território!\n");

        // Defensor muda de cor
        strcpy(defensor->cor, atacante->cor);

        // Metade das tropas do atacante vai para o território conquistado
        defensor->tropas = atacante->tropas / 2;

        // Atacante perde essas tropas que foram transferidas
        atacante->tropas -= defensor->tropas;
    } else {
        printf("\n❌ O ataque falhou! O atacante perde 1 tropa.\n");
        atacante->tropas -= 1;
    }
}

// Liberação da memória alocada dinamicamente
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL)); // garante aleatoriedade dos dados

    int qtd;

    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &qtd);

    // Alocação dinâmica do vetor de Territorios
    Territorio *mapa = (Territorio *) malloc(qtd * sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, qtd);

    int atacante, defensor;

    while (1) {
        exibirTerritorios(mapa, qtd);

        printf("\nEscolha o índice do território atacante (-1 para sair): ");
        scanf("%d", &atacante);
        if (atacante == -1) break;

        printf("Escolha o índice do território defensor: ");
        scanf("%d", &defensor);

        if (atacante < 0 || atacante >= qtd || defensor < 0 || defensor >= qtd) {
            printf("\n❌ Índices inválidos!\n");
            continue;
        }

        atacar(&mapa[atacante], &mapa[defensor]);
    }

    liberarMemoria(mapa);

    printf("\n✅ Memória liberada e programa finalizado!\n");
    return 0;
}
