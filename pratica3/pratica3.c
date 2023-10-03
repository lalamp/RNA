#include <stdio.h>
#include <math.h>

int main(){
    //Leitura do arquivo
    char arq[100] = "C:/Users/lal4mp/Desktop/USP/RNA/pratica3/dataset_lagarto.txt";

    FILE *file = fopen(arq, "r"); //abrir o arquivo
    if(file == NULL){
		printf("Falha na leitura do arquivo\n");
		return(1);
	}
    else{
        printf("\nArquivo aberto para leitura com sucesso\n\n");
    }

    printf("DADOS:\n");
    int especie[25];
    float massa[25], comprimento[25], dimensao[25];
    char sexo[25], conjunto[25];

    int ind = 0;
    char line[100];
    while(fgets(line, sizeof(line), file) != NULL){ //ler linha por linha do arquivo
        if(ind != 0){
            printf("%s", line); //mostrar os dados do arquivo por linha, exceto o da primeira linha(ind = 0)
            sscanf(line, "%d %f %f %f %c", &especie[ind], &massa[ind], &comprimento[ind], &dimensao[ind], &sexo[ind]); //pegar os dados da linha, tranformá-los de string para float/char e armazená-los nos respectivos vetores 
        }
        ind++;
    }

    fclose(file);
    
    int total_dados = 0, total_femeas = 0, total_machos = 0;
    int k;
    for(k = 1; k < 26; k++){ //o programa percorre todo o vetor sexo[] e analisa cada um de seus valores: se for F é fêmea, se for M é macho e se soma ao total de cada sexo
        if(sexo[k] == 'F'){ 
            total_femeas++;
        }
        else{
            total_machos++;
        }
        total_dados++;
    }
    printf("\nTotal de dados: %d \nTotal femeas: %d \nTotal machos: %d\n\n", total_dados, total_femeas, total_machos);    
    
    //Conjunto Treinamento e Conjunto Teste 
        //com proporção entre as duas classes
    float p;
    printf("\n\nInforme um valor para p (valor entre 0 e 1 - controla o tamanho dos conjuntos de treinamento e teste): ");
    scanf("%f", &p);
    
    int femeas = 0, machos = 0, treinamento = 0, teste = 0;
    for(k = 1; k < 26; k++){ //o programa percorre todo o vetor sexo[], analisando se é F fêmea ou M macho
        if(sexo[k] == 'F'){
            if(femeas < p*total_femeas){ //o programa analisa se o número de fêmeas colocadas no conjunto de treinamento é menor que p*quantidade total de fêmeas -> se for, mantém adicionando no conjunto de treinamento, caso contrário adiciona-se no conjunto de teste  
                conjunto[k] = 'A';
                treinamento++;
            }
            else{ 
                conjunto[k] = 'T';
                teste++;
            }
            femeas++;
        }
        else{
            if(machos < p*total_machos){ //o programa analisa se o número de machos colocados no conjunto de treinamento é menor que p*quantidade total de machos -> se for, mantém adicionando no conjunto de treinamento, caso contrário adiciona-se no conjunto de teste 
                conjunto[k] = 'A';
                treinamento++;
            }
            else{
                conjunto[k] = 'T';
                teste++;
            }
            machos++;
        }
    }

    printf("\nConjunto Treinamento: %d dados\n", treinamento); //o programa percorre todo o vetor conjunto[]
    for(k = 1; k < 26; k++){ 
        if(conjunto[k] == 'A'){ //se o valor de conjunto[k] = A, essa espécie está no conjunto de treinamento
            printf("%d: %.5f, %.5f, %.5f, %c\n", especie[k], massa[k], comprimento[k], dimensao[k], sexo[k]);
        }
    }
    printf("\nConjunto Teste: %d dados\n", teste);
    for(k = 1; k < 26; k++){
        if(conjunto[k] == 'T'){ //se o valor de conjunto[k] = T, essa espécie está no conjunto de teste
            printf("%d: %.5f, %.5f, %.5f, %c\n", especie[k], massa[k], comprimento[k], dimensao[k], sexo[k]);
        }
    }
    printf("\n");

    //Máximo e Mínimo 
        //o programa percorre os vetores massa[], comprimento[] e dimensao[] do conjunto treinamento, comparando os valores para descobrir o máximo e mínimo de cada coluna
    float max_massa = 0, max_comprimento = 0, max_dimensao = 0;
    float min_massa = 1000, min_comprimento = 1000, min_dimensao = 1000;

    int i = 1, count = 0;
    while(count < total_dados){
        if(conjunto[i] == 'A'){
            if(massa[i] > max_massa){
                max_massa = massa[i];
            }
            if(massa[i] < min_massa){
                min_massa = massa[i];
            }  
        }
        i++;
        count++;
    }

    i = 1, count = 0;
    while(count < total_dados){
        if(conjunto[i] == 'A'){
            if(comprimento[i] > max_comprimento){
                max_comprimento = comprimento[i];
            }
            if(comprimento[i] < min_comprimento){
                min_comprimento = comprimento[i];
            } 
        }
        i++;
        count++;
    }

    i = 1, count = 0;
    while(count < total_dados){
        if(conjunto[i] == 'A'){
            if(dimensao[i] > max_dimensao){
                max_dimensao = dimensao[i];
            }
            if(dimensao[i] < min_dimensao){
                min_dimensao = dimensao[i];
            }
        }
        i++;
        count++;
    }

    //Normalizar 
        //o programa percorre todos os dados por meio dos vetores massa[], comprimento[] e dimensao[], normalizando cada um de seus valores a partir da fórmula ((valor - min)/(max - min)*2-1), sendo o max e o min respectivos a cada vetor/coluna e para o vetor sexo[] normaliza com F = 1 e M = -1
    int j = 1;
    count = 0;
    int sexo_norm[25];

    printf("\nConjunto Treinamento Normalizado: \n");
    while(count < total_dados){
        if(conjunto[j] == 'A'){
            massa[j] = ((massa[j] - min_massa)/(max_massa - min_massa))*2 - 1;
            comprimento[j] = ((comprimento[j] - min_comprimento)/(max_comprimento - min_comprimento))*2 - 1;
            dimensao[j] = ((dimensao[j] - min_dimensao)/(max_dimensao - min_dimensao))*2 - 1;

            if(sexo[j] == 'F'){
                sexo_norm[j] = 1;
            }
            else{
                sexo_norm[j] = -1;
            }

            printf("%d: %.5f, %.5f, %.5f, %d\n", especie[j], massa[j], comprimento[j], dimensao[j], sexo_norm[j]);
        }

        j++;
        count++;    
    }

    j = 1;
    count = 0;
    printf("\nConjunto Teste Normalizado: \n");
    while(count < total_dados){
        if(conjunto[j] == 'T'){
            massa[j] = ((massa[j] - min_massa)/(max_massa - min_massa))*2 - 1;
            comprimento[j] = ((comprimento[j] - min_comprimento)/(max_comprimento - min_comprimento))*2 - 1;
            dimensao[j] = ((dimensao[j] - min_dimensao)/(max_dimensao - min_dimensao))*2 - 1;

            if(sexo[j] == 'F'){
                sexo_norm[j] = 1;
            }
            else{
                sexo_norm[j] = -1;
            }

            printf("%d: %.5f, %.5f, %.5f, %d\n", especie[j], massa[j], comprimento[j], dimensao[j], sexo_norm[j]);
        }

        j++;
        count++;    
    }

    //Treinando o Perceptron
    int y[treinamento+1];
    float u, e;
    float w[4] = {0, 0, 0, 0};
    float neta = 0.01;
    int iteracao = 1;

    while(iteracao <= 4){
        for(j = 1; j <= total_dados; j++){
            if(conjunto[j] == 'A'){
                u = w[0] + massa[j]*w[1] + comprimento[j]*w[2] + dimensao[j]*w[3];
                printf("\n\nu= %.5f", u);

                if(u > 0){
                    y[j] = 1;
                }
                else{
                    y[j] = -1;
                }

                e = sexo_norm[j] - y[j];
                printf("\ne = d[%d] - y[%d] = %d - %d = %.5f", j, j, sexo_norm[j], y[j], e);

                w[0] = w[0] + neta*e;
                w[1] = w[1] + massa[j]*neta*e; 
                w[2] = w[2] + comprimento[j]*neta*e;
                w[3] = w[3] + dimensao[j]*neta*e;
                printf("\nNovos pesos: \nw[0] = %.5f \nw[1] = %.5f \nw[2] = %.5f \nw[3] = %.5f", w[0], w[1], w[2], w[3]);

                printf("\nPesos ajustados para a especie %d", j);
            }
        }
        iteracao++;
    }

    //Teste do Perceptron
    int v_femea = 0, f_femea = 0, v_macho = 0, f_macho = 0;
    printf("\nTeste: \n");
    printf("\nPesos: \nw[0] = %.5f \nw[1] = %.5f \nw[2] = %.5f \nw[3] = %.5f", w[0], w[1], w[2], w[3]);
    for(j = 1; j <= total_dados; j++){
        if(conjunto[j] == 'T'){
            u = w[0] + massa[j]*w[1] + comprimento[j]*w[2] + dimensao[j]*w[3];
            printf("\n\nu = %f", u);

            if(u > 0){
                y[j] = 1;
            }
            else{
                y[j] = -1;
            }
            printf("\ny[%d] = %d  x  d[%d] = %d", j, y[j], j, sexo_norm[j]);

            if(y[j] == sexo_norm[j] && sexo_norm[j] == 1){
                v_femea++;
            }
            else if(y[j] == sexo_norm[j] && sexo_norm[j] == -1){
                v_macho++;
            }
            else if(y[j] != sexo_norm[j] && sexo_norm[j] == 1){
                f_macho++;
            }
            else{
                f_femea++;
            }
        }
    }

    //Matriz de Confusão
    printf("\n\n\n                                CLASSIFICACAO TESTE\n");
    printf("                                FEMEA           MACHO\n\n");
    printf("CLASS. REAL: FEMEA              %d              %d\n\n             MACHO              %d              %d", v_femea, f_macho, f_femea, v_macho);

    //Acurácia
    float accuracy = ((v_femea + v_macho)*1.0)/(teste *1.0);
    printf("\n\nA acuracia do conjunto teste e de %d/%d = %.5f\n\n", v_femea + v_macho, teste, accuracy);

}