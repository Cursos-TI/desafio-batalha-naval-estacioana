#include <stdio.h>

#define TAM_TABULEIRO 10  // Tamanho do tabuleiro
#define TAM_NAVIO 3       // Tamanho dos navios

// Função para inicializar o tabuleiro com água (valor 0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;  // 0 representa água
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0)
                printf(" 0 ");  // Água
            else if (tabuleiro[i][j] == 3)
                printf(" 3 ");  // Navio
            else
                printf(" 5 ");  // Área afetada pela habilidade
        }
        printf("\n");
    }
}

// Função para posicionar o navio horizontalmente
int podePosicionarNavioHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (coluna + TAM_NAVIO > TAM_TABULEIRO) {
        return 0;  // Não cabe no tabuleiro
    }

    // Verificar sobreposição
    for (int i = coluna; i < coluna + TAM_NAVIO; i++) {
        if (tabuleiro[linha][i] != 0) {
            return 0;  // Já existe navio nesta posição
        }
    }
    return 1;  // Pode posicionar
}

// Função para posicionar o navio horizontalmente
void posicionarNavioHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    for (int i = coluna; i < coluna + TAM_NAVIO; i++) {
        tabuleiro[linha][i] = 3;  // 3 representa o navio
    }
}

// Função para posicionar o navio verticalmente
int podePosicionarNavioVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (linha + TAM_NAVIO > TAM_TABULEIRO) {
        return 0;  // Não cabe no tabuleiro
    }

    // Verificar sobreposição
    for (int i = linha; i < linha + TAM_NAVIO; i++) {
        if (tabuleiro[i][coluna] != 0) {
            return 0;  // Já existe navio nesta posição
        }
    }
    return 1;  // Pode posicionar
}

// Função para posicionar o navio verticalmente
void posicionarNavioVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    for (int i = linha; i < linha + TAM_NAVIO; i++) {
        tabuleiro[i][coluna] = 3;  // 3 representa o navio
    }
}

// Função para gerar a matriz do Cone (expande para baixo)
void gerarHabilidadeCone(int habilidade[5][5], int centroX, int centroY) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (j >= centroY - i && j <= centroY + i && i <= centroX) {
                habilidade[i][j] = 1;  // Marca a área afetada
            } else {
                habilidade[i][j] = 0;  // Não afetado
            }
        }
    }
}

// Função para gerar a matriz da Cruz (centro em torno do ponto central)
void gerarHabilidadeCruz(int habilidade[5][5], int centroX, int centroY) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == centroX || j == centroY) {
                habilidade[i][j] = 1;  // Marca a área afetada
            } else {
                habilidade[i][j] = 0;  // Não afetado
            }
        }
    }
}

// Função para gerar a matriz do Octaedro (forma de losango)
void gerarHabilidadeOctaedro(int habilidade[5][5], int centroX, int centroY) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (abs(i - centroX) + abs(j - centroY) <= 2) {
                habilidade[i][j] = 1;  // Marca a área afetada
            } else {
                habilidade[i][j] = 0;  // Não afetado
            }
        }
    }
}

// Função para aplicar uma habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int habilidade[5][5], int linha, int coluna) {
    // Sobrepor a habilidade ao tabuleiro
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int x = linha + i - 2;  // Ajuste para o centro da habilidade
            int y = coluna + j - 2;
            if (x >= 0 && x < TAM_TABULEIRO && y >= 0 && y < TAM_TABULEIRO && habilidade[i][j] == 1) {
                tabuleiro[x][y] = 5;  // Marca a área afetada pela habilidade
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];  // Matriz para representar o tabuleiro
    int linha, coluna;

    // Inicializando o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Posicionando os navios
    linha = 3;
    coluna = 2;
    if (podePosicionarNavioHorizontal(tabuleiro, linha, coluna)) {
        posicionarNavioHorizontal(tabuleiro, linha, coluna);
    }

    linha = 1;
    coluna = 6;
    if (podePosicionarNavioVertical(tabuleiro, linha, coluna)) {
        posicionarNavioVertical(tabuleiro, linha, coluna);
    }

    // Gerar as matrizes de habilidade
    int habilidadeCone[5][5];
    int habilidadeCruz[5][5];
    int habilidadeOctaedro[5][5];

    gerarHabilidadeCone(habilidadeCone, 2, 2);  // Exemplo para gerar habilidade de Cone
    gerarHabilidadeCruz(habilidadeCruz, 2, 2);  // Exemplo para gerar habilidade de Cruz
    gerarHabilidadeOctaedro(habilidadeOctaedro, 2, 2);  // Exemplo para gerar habilidade de Octaedro

    // Aplicando as habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, habilidadeCone, 1, 1);      // Aplica cone na posição (1,1)
    aplicarHabilidade(tabuleiro, habilidadeCruz, 4, 4);      // Aplica cruz na posição (4,4)
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, 7, 7);  // Aplica octaedro na posição (7,7)

    // Exibindo o tabuleiro com os navios e as áreas de efeito
    printf("\nTabuleiro com as habilidades aplicadas:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}