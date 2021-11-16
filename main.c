#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<locale.h>

/*
    *Fernando Augusto Serafim
    *João Pedro Carvalho de Alencar
    *Disciplina : Cálculo Numérico II
    *Professora: Thays Aparecida de Abreu Santos
    *Curso : Ciencias da Computação - Noturno
*/

float** aloca_matriz(int* restricao, int* normais);
float* aloca_vetor(int* restricao);
void le_matriz(float** matriz, float* restricao, float* normais);
void Maximizar_Minimizar(float** matriz, int* objetivo, float* restricao, float* normais){
bool verifica_solucao(float** matriz_coeficientes, int* restricao, int* normais);
void desalocaMatrizes(float** matriz, float* vetor, int* restricao);
void PosicaoEMenorValor(float** matriz_coeficientes, float *menorValorLinha, int *guarda_coluna, int* restricao, int* normais);
void DivisoesEMenorPositivo(float* divisao_equacoes, float** matriz_coeficientes, int guarda_coluna, int* restricao, int* normais);
void MenorPositivo(float *menorValorDivisao,float* divisao_equacoes, int *guarda_linha, int* restricao);
float EstabelecePivo(float** matriz_coeficientes, int guarda_linha, int guarda_coluna);
void NovaLinhaPivo(float** matriz_coeficientes, int guarda_linha, float variavel_pivo, int* restricao, int* normais);
void ExibeMatriz(float** matriz_coeficientes, int *iteracoes, int* restricao, int* normais);
void NovasLinhas(float variavel_oposta, float** matriz_coeficientes, int guarda_coluna, int guarda_linha, int* restricao, int* normais);
void SolucaoBasicaFactivel(float** matriz, int* restricao, int* normais, int objetivo);


int main()
{
    setlocale(LC_ALL,"Portuguese_Brazil");

    float **matriz_coeficientes;
    float *divisao_equacoes;
    int guarda_coluna = 0, guarda_linha = 0, iteracoes = 0;
    float menorValorLinha = 0.0, menorValorDivisao = 0;
    float variavel_pivo = 0;
    float variavel_oposta = 0;
    int normais, restricao;
    int j, objetivo;

    printf("NÃO HÁ NECESSIDADE DE INSERIR OS DADOS PASSANDO O SEGUNDO MEMBRO DA FUNÇÃO OBJETIVA PARA O LADO DIREITO\n\n");
    system("pause");
    printf("\n");
    printf("Digite a quantidade de variáveis normais\n");
    scanf("%d", &normais);
    printf("Digite a quantidade de funções de restrição\n");
    scanf("%d", &restricao);
    printf("[1]MAXIMIZAR \n [2] MINIMIZAR\n [0]SAIR\n");
    scanf("%d", &objetivo);

    matriz_coeficientes = aloca_matriz(&restricao, &normais);
    divisao_equacoes = aloca_vetor(&restricao);
    le_matriz(matriz_coeficientes, &restricao, &normais);
    Maximizar_Minimizar(matriz_coeficientes, &objetivo, &restricao, &normais);
    ExibeMatriz(matriz_coeficientes, &iteracoes, &restricao, &normais);

    do{
        guarda_coluna = 0, guarda_linha = 0;
        menorValorLinha = 0.0;
        variavel_pivo = 0;
        variavel_oposta = 0;

        PosicaoEMenorValor(matriz_coeficientes, &menorValorLinha, &guarda_coluna, &restricao, &normais);

        DivisoesEMenorPositivo(divisao_equacoes, matriz_coeficientes, guarda_coluna, &restricao, &normais);

        MenorPositivo(&menorValorDivisao, divisao_equacoes, &guarda_linha, &restricao);

        variavel_pivo = EstabelecePivo(matriz_coeficientes, guarda_linha, guarda_coluna);

        NovaLinhaPivo(matriz_coeficientes, guarda_linha, variavel_pivo, &restricao, &normais);

        NovasLinhas(variavel_oposta, matriz_coeficientes, guarda_coluna, guarda_linha, &restricao, &normais);

        ExibeMatriz(matriz_coeficientes, &iteracoes, &restricao, &normais);

        system("pause");
        system("cls");

    }while(verifica_solucao(matriz_coeficientes, &restricao, &normais));

    SolucaoBasicaFactivel(matriz_coeficientes, &restricao, &normais, objetivo);

    desalocaMatrizes(matriz_coeficientes, divisao_equacoes, &restricao);

    return 0;
}
float** aloca_matriz(int* restricao, int* normais){

    int i;
    float** matriz_coeficientes;

    matriz_coeficientes = malloc( (*restricao + 1) * sizeof(float*)); //quantidade de linhas
    for( i = 0; i < (*restricao + 1); i++){ matriz_coeficientes[i] = malloc( (*normais + *restricao + 2) * sizeof(float)); }
    //for com a quantidade de colunas

    return matriz_coeficientes;
}

float* aloca_vetor(int* restricao){

    float* divisao_equacoes;

    divisao_equacoes  = malloc( (*restricao + 1) * sizeof(float));

    return divisao_equacoes;
}

void le_matriz(float** matriz, float* restricao, float* normais){

    int i, j;
    printf("DIGITE A MATRIZ A SER TRABALHADA:\n\n");
    for(i=0; i< *restricao + 1; i++){
        for(j=0; j< *normais + *restricao + 2; j++){
            scanf("%f", &matriz[i][j]);
        }
    }

}

void Maximizar_Minimizar(float** matriz, int* objetivo, float* restricao, float* normais){

    if(*objetivo == 1){
        for(j = 1; j< *restricao+*normais+2; j++){//AQUI EU EXCLUO A POSSIBILIDADE DE DAR RUIM
                                                //COM O COEFICIENTE DE Z
            matriz_coeficientes[0][j] = matriz_coeficientes[0][j] * (-1);

        }
    }

}

void PosicaoEMenorValor(float** matriz_coeficientes, float *menorValorLinha, int *guarda_coluna, int* restricao, int* normais){

      int j;

        /*
            LOOPING PARA CALCULAR O MENOR VALOR PRESENTE NA LINHA DA F. OBJETIVA
            E GUARDAR A POSIÇÃO DA COLUNA REFERENTE AO MENOR VALOR (VARIÁVEL QUE ENTRA).
        */

        for(j = 0; j < *restricao+*normais+2 ;j++){
            if(matriz_coeficientes[0][j] < *menorValorLinha){
                *menorValorLinha = matriz_coeficientes[0][j];
                *guarda_coluna = j;
            }
        }

        printf("O MENOR VALOR DA FUNÇÃO OBJETIVA É: %.2f\n", *menorValorLinha);
        printf("E A COLUNA REFERENTE AO VALOR É: %d\n", *guarda_coluna + 1);

        printf("\n\n");
}

void DivisoesEMenorPositivo(float* divisao_equacoes, float** matriz_coeficientes, int guarda_coluna, int* restricao, int* normais){
    int i;

    printf("AQUI TEMOS AS SEGUINTES DIVISÕES:\n");
    for(i = 0; i < *restricao+1 ; i++){
        divisao_equacoes[i] = matriz_coeficientes[i][*restricao+*normais+1]/matriz_coeficientes[i][guarda_coluna];
        printf("%.2f/%.2f = %.2f\n", matriz_coeficientes[i][*restricao+*normais+1], matriz_coeficientes[i][guarda_coluna], divisao_equacoes[i]);
    }

    printf("\n\n");
}

void MenorPositivo(float *menorValorDivisao,float* divisao_equacoes, int *guarda_linha, int* restricao){
    int i;

    *menorValorDivisao = 1000000;

//FOR PARA VERIFICAR QUAL VALOR DO VETOR DIVISAO_EQUAÇÕES É O MENOR POSITIVO
for(i = 1; i <= *restricao+1; i++){
    if(divisao_equacoes[i] < *menorValorDivisao && divisao_equacoes[i] > 0 && *menorValorDivisao > 0){
            *menorValorDivisao = divisao_equacoes[i];
            *guarda_linha = i;
        }
    }
    printf("LOGO, O MENOR VALOR POSITIVO É: %.2f\n\n", *menorValorDivisao);
    printf("CONLUÍMOS ENTÃO QUE A LINHA QUE SAÍ É A LINHA %d\n", *guarda_linha + 1);

    printf("\n\n");
}

float EstabelecePivo(float** matriz_coeficientes, int guarda_linha, int guarda_coluna){
    //PIVÔ TRATA-SE DO CRUZAMENTO ENTRE A VARIÁVEL QUE ENTRA A LINHA QUE SAI.
    float variavel_pivo;

    variavel_pivo = matriz_coeficientes[guarda_linha][guarda_coluna];

    printf("O PIVÔ CORRESPONDENTE É: %.2f\n", variavel_pivo);

    printf("\n\n");

    return variavel_pivo;
}

void  NovaLinhaPivo(float** matriz_coeficientes, int guarda_linha, float variavel_pivo, int* restricao, int* normais){
        int j;

        for(j = 0; j < *restricao + *normais + 2; j++){
            matriz_coeficientes[guarda_linha][j] = matriz_coeficientes[guarda_linha][j]/variavel_pivo;
        }

        printf("AGORA, DIVIDINDO A LINHA QUE SAÍ PELO PIVÔ, TEMOS A SEGUINTE LINHA PIVÔ:\n");
         for(j = 0; j < *restricao + *normais + 2; j++){
                printf("%.2f ", matriz_coeficientes[guarda_linha][j]);
        }
        printf("\n\n");
}

void  ExibeMatriz(float** matriz_coeficientes, int *iteracoes, int* restricao, int* normais){
    int i,j;

    if(*iteracoes == 0){

            printf("TEMOS A SEGUINTE MATRIZ A SER TRATADA:\n\n");
            printf("_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n\n");

            for(i = 0; i < *restricao + 1; i++){

                    for(j = 0; j < *restricao + *normais + 2; j++){

                        printf("%.2f ", matriz_coeficientes[i][j]);

                }
                    printf("\n");
            }
            printf("\n");
            printf("_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n");
            printf("\n\n");

    }else{
            printf("MATRIZ DE COEFICIENTES APÓS A %dª ITERAÇÃO:\n\n", *iteracoes);
            printf("_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n\n");

            for(i = 0; i < *restricao + 1; i++){

                    for(j = 0; j < *restricao + *normais + 2; j++){

                        printf("%.2f ", matriz_coeficientes[i][j]);

                }
                    printf("\n");
            }
            printf("\n");
            printf("_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n");
            printf("\n\n");
    }

*iteracoes = *iteracoes + 1;
}

void NovasLinhas(float variavel_oposta, float** matriz_coeficientes, int guarda_coluna, int guarda_linha, int* restricao, int* normais){
    int i, j;

    printf("TEMOS, ENTÃO, O SEGUINTE PROCESSO PARA OBTENÇÃO DAS NOVAS LINHAS:\n");

    for(i = 0; i < *restricao + 1; i++){

        if(i != guarda_linha){
                printf("NOVA %dª LINHA: \n", i+1);
            }

        variavel_oposta =  -1 * matriz_coeficientes[i][guarda_coluna];

        for(j = 0; j < *restricao + *normais + 2; j++){

                if(i == guarda_linha){
                    break;
                }
                else{
                    matriz_coeficientes[i][j] = (variavel_oposta * matriz_coeficientes[guarda_linha][j]) + matriz_coeficientes[i][j];

                    printf("(%.2f * %.2f) + %.2f = %.2f\n", variavel_oposta, matriz_coeficientes[guarda_linha][j], matriz_coeficientes[i][j], matriz_coeficientes[i][j]);
                }

        }
        printf("\n");
    }

    printf("\n\n");

}

bool verifica_solucao(float** matriz_coeficientes, int* restricao, int* normais){

/*ESSA FUNCÃO VERIFICA SE TODOS AS VARIÁVEIS ENTRE A PRIMEIRA E A ÚLTIMA COLUNA
DA MATRIZ DE COEFICIENTES SÃO MAIORES OU IGUAIS A ZERO*/

    int contador = 0, j;

    for(j = 1; j < *restricao + *normais + 1; j++){
        if(matriz_coeficientes[0][j] >= 0) contador++;
    }

    if(contador == *restricao + *normais) return false;
    else return true;
}

void SolucaoBasicaFactivel(float** matriz, int* restricao, int* normais, int objetivo){
  //A PRIMEIRA LINHA CONTÉM O PONTO ÓTIMO
  //PRECISO VERIFICAR AS COLUNAS ED VER QUAL TERMO VALE 1 E QUAL TERMO É DIFERENTE DE 1
  int i, j, contador = 0;
  float solucao[*restricao + *normais];

  //restricao vale 3 e normais vale 2

      for(j=1; j <= *restricao+*normais; j++){ //j VAI DE 1 ATÉ 5

            contador = 0;

            for(i=1; i < *restricao + 1; i++){ //O I VAI DE 1 ATÉ 3

                if(matriz[i][j] == 1) solucao[j-1] = matriz[i][*restricao+*normais+1];
                else contador++;
            }
            if(contador == *restricao+1) solucao[j-1] = 0;
        }

    if(objetivo == 2){
        printf("O PONTO ÓTIMO É: [%.2f]\n\n", -1 * matriz[0][*restricao + *normais + 1]);
    }else printf("O PONTO ÓTIMO É: [%.2f]\n\n", matriz[0][*restricao + *normais + 1]);

    printf("E A SOLUÇÃO BÁSICA FACTÍVEL É DADA POR:\n\n");

    printf("_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n\n");

    for(j=0; j < *restricao+*normais; j++) printf("[%.3f] ", solucao[j]);
    printf("\n\n");

    printf("_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n\n");

}

void desalocaMatrizes(float** matriz, float* vetor, int* restricao){
    int i;

    free(vetor); vetor = NULL;

    for(i=0; i < *restricao + 1; i++){ free(matriz[i]); matriz[i] = NULL;}
    free(matriz); matriz = NULL;

printf("SISTEMA LIMPO COM SUCESSO\n");
}

