#include <stdio.h>
#include <string.h>

// Definição da estrutura Territorio
// Esta struct agrupa informações relacionadas a um território
struct Territorio {
    char nome[30];     // Nome do território
    char cor[10];      // Cor do exército
    int tropas;        // Quantidade de tropas
};

int main() {
    // Vetor de structs para armazenar até 5 territórios
    struct Territorio territorios[5];

    // Loop para cadastro dos territórios
    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastro do Território %d ---\n", i + 1);

        // Leitura do nome
        printf("Digite o nome do território: ");
        scanf("%s", territorios[i].nome);

        // Leitura da cor do exército
        printf("Digite a cor do exército: ");
        scanf("%s", territorios[i].cor);

        // Leitura do número de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos territórios cadastrados
    printf("\n===== Territórios Cadastrados =====\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
