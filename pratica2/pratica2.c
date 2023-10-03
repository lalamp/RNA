#include <stdio.h>
#include <math.h>

int main(){
    //leitura do arquivo
    char arq[100] = "C:/Users/lal4mp/Desktop/USP/RNA/pratica2/dataset_lagarto.txt";

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

    float p;
    printf("Informe um valor para p (valor entre 0 e 1 - controla o tamanho dos conjuntos de treinamento e teste): ");
    scanf("%f", &p);
    
    
    //Q1. conjunto treinamento e conjunto teste com proporção entre as duas classes
    printf("\nQ1. Gerando os conjuntos treinamento e teste com aproximadamente a mesma proporcao de dados de cada uma das classes, com base em p");

    int femeas = 0, machos = 0;
    for(k = 1; k < 26; k++){ //o programa percorre todo o vetor sexo[], analisando se é F fêmea ou M macho
        if(sexo[k] == 'F'){
            if(femeas < p*total_femeas){ //o programa analisa se o número de fêmeas colocadas no conjunto de treinamento é menor que p*quantidade total de fêmeas -> se for, mantém adicionando no conjunto de treinamento, caso contrário adiciona-se no conjunto de teste  
                conjunto[k] = 'A';
            }
            else{ 
                conjunto[k] = 'T';
            }
            femeas++;
        }
        else{
            if(machos < p*total_machos){ //o programa analisa se o número de machos colocados no conjunto de treinamento é menor que p*quantidade total de machos -> se for, mantém adicionando no conjunto de treinamento, caso contrário adiciona-se no conjunto de teste 
                conjunto[k] = 'A';
            }
            else{
                conjunto[k] = 'T';
            }
            machos++;
        }
    }

    printf("\nConjunto Treinamento:\n"); //o programa percorre todo o vetor conjunto[]
    for(k = 1; k < 26; k++){ 
        if(conjunto[k] == 'A'){ //se o valor de conjunto[k] = A, essa espécie está no conjunto de treinamento
            printf("%d: %.5f, %.5f, %.5f, %c\n", especie[k], massa[k], comprimento[k], dimensao[k], sexo[k]);
        }
    }
    printf("\nConjunto Teste:\n");
    for(k = 1; k < 26; k++){
        if(conjunto[k] == 'T'){ //se o valor de conjunto[k] = T, essa espécie está no conjunto de teste
            printf("%d: %.5f, %.5f, %.5f, %c\n", especie[k], massa[k], comprimento[k], dimensao[k], sexo[k]);
        }
    }


    //máximo e mínimo - o programa percorre p*total_dados (conjunto de treinamento) do vetor massa[], comprimento[] e dimensao[], comparando os valores para descobrir o máximo e mínimo de cada coluna

    //máximo
    float max_massa = 0, max_comprimento = 0, max_dimensao = 0;

    int i = 1, count = 0;
    while(count < floor(p*total_dados)){ 
        if(massa[i] > max_massa){
            max_massa = massa[i];
        }
        i++;
        count++;
    }

    i = 1, count = 0;
    while(count < floor(p*total_dados)){
        if(comprimento[i] > max_comprimento){
            max_comprimento = comprimento[i];
        }
        i++;
        count++;
    }

    i = 1, count = 0;
    while(count < floor(p*total_dados)){
        if(dimensao[i] > max_dimensao){
            max_dimensao = dimensao[i];
        }
        i++;
        count++;
    }
    
    //mínimo
    float min_massa = 1000, min_comprimento = 1000, min_dimensao = 1000;

    i = 1, count = 0;
    while(count < floor(p*total_dados)){
        if(massa[i] < min_massa){
            min_massa = massa[i];
        }
        i++;
        count++;
    }

    i = 1, count = 0;
    while(count < floor(p*total_dados)){
        if(comprimento[i] < min_comprimento){
            min_comprimento = comprimento[i];
        }
        i++;
        count++;
    }

    i = 1, count = 0;
    while(count < floor(p*total_dados)){
        if(dimensao[i] < min_dimensao){
            min_dimensao = dimensao[i];
        }
        i++;
        count++;
    }


    //Q3. normalizar com p = 0.75 
    //o programa percorre esses 75% dos dados totais (conjunto de treinamento) por meio dos vetores massa[], comprimento[] e dimensao[], normalizando cada um de seus valores a partir da fórmula ((valor - min)/(max - min)*2-1), sendo o max e o min respectivos a cada vetor/coluna
    printf("\n\nQ3. Conjunto de treinamento para p = 0.75 normalizado: \n");
    int j = 1;
    count = 0;
    while(count < floor(0.75*total_dados)){
        massa[j] = ((massa[j] - min_massa)/(max_massa - min_massa))*2 - 1;
        comprimento[j] = ((comprimento[j] - min_comprimento)/(max_comprimento - min_comprimento))*2 - 1;
        dimensao[j] = ((dimensao[j] - min_dimensao)/(max_dimensao - min_dimensao))*2 - 1;

        printf("%d: %.5f, %.5f, %.5f, %c\n", especie[j], massa[j], comprimento[j], dimensao[j], sexo[j]);

        j++;
        count++;
    }


    //Q4. normalizar para um exemplo qualquer (com base no p dado)
    //o programa pede o usuário para informar os dados (massa, comprimento, dimensão e sexo) do lagarto e aplica a fórmula ((valor - min)/(max - min)*2-1) para cada variável, com base no conjunto de treinamento obtido anteriormente (em p e nos máximos e mínimos), obtendo a normalização dos dados 
    printf("\n\nQ4. Normalizando dados de um exemplo qualquer de um lagarto");

    float mass, comp, dim;
    char genero;
    printf("\n\nInforme os dados do lagarto:\n");
    printf("Massa: ");
    scanf("%f", &mass);
    printf("Comprimento: ");
    scanf("%f", &comp);
    printf("Dimensao: ");
    scanf("%f", &dim);
    printf("Sexo (M ou F): ");
    scanf(" %c", &genero);

    mass = ((mass - min_massa)/(max_massa - min_massa))*2 - 1;
    comp = ((comp - min_comprimento)/(max_comprimento - min_comprimento))*2 - 1;
    dim = ((dim - min_dimensao)/(max_dimensao - min_dimensao))*2 - 1;

    printf("\nNormalizado: %.5f, %.5f, %.5f, %c\n\n", mass, comp, dim, genero);
}

