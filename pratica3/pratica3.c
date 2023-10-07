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
    
    //Estatísticas dos dados
    int total_dados = 0, total_femeas = 0, total_machos = 0;
    int i;
    for(i = 1; i < 26; i++){ //o programa percorre todo o vetor sexo[] e analisa cada um de seus valores: se for F é fêmea, se for M é macho e se soma ao total de cada sexo
        if(sexo[i] == 'F'){ 
            total_femeas++;
        }
        else{
            total_machos++;
        }
        total_dados++;
    }
    printf("\nTotal de dados: %d \nTotal femeas: %d \nTotal machos: %d", total_dados, total_femeas, total_machos);    
    
    //Conjunto Treinamento e Conjunto Teste 
        //com proporção entre as duas classes
    float p;
    printf("\n\nInforme um valor para p (valor entre 0 e 1 - controla o tamanho dos conjuntos de treinamento e teste): ");
    scanf("%f", &p);
    
    int femeas = 0, machos = 0, treinamento = 0, teste = 0;
    int k;
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
    int esp_trein[treinamento+1];
    float mass_trein[treinamento+1], compr_trein[treinamento+1], dim_trein[treinamento+1];
    char sexo_trein[treinamento+1];
    int b = 1;

    for(k = 1; k <= total_dados; k++){ 
        if(conjunto[k] == 'A'){ //se o valor de conjunto[k] = A, essa espécie está no conjunto de treinamento e passa os valores para os vetores de treinamento
            esp_trein[b] = especie[k];
            mass_trein[b] = massa[k];
            compr_trein[b] = comprimento[k];
            dim_trein[b] = dimensao[k];
            sexo_trein[b] = sexo[k];
            
            printf("%d: %.5f, %.5f, %.5f, %c\n", esp_trein[b], mass_trein[b], compr_trein[b], dim_trein[b], sexo_trein[b]);
            b++;
        }
    }

    printf("\nConjunto Teste: %d dados\n", teste);
    int esp_teste[teste+1];
    float mass_teste[teste+1], compr_teste[teste+1], dim_teste[teste+1];
    char sexo_teste[teste+1];
    b = 1;

    for(k = 1; k <= total_dados; k++){
        if(conjunto[k] == 'T'){ //se o valor de conjunto[k] = T, essa espécie está no conjunto de teste e passa os valores para os vetores de teste
            esp_teste[b] = especie[k];
            mass_teste[b] = massa[k];
            compr_teste[b] = comprimento[k];
            dim_teste[b] = dimensao[k];
            sexo_teste[b] = sexo[k];
            
            printf("%d: %.5f, %.5f, %.5f, %c\n", esp_teste[b], mass_teste[b], compr_teste[b], dim_teste[b], sexo_teste[b]);
            b++;
        }
    }
    printf("\n");

    //Máximo e Mínimo 
        //o programa percorre os vetores mass_trein[], compr_trein[] e dim_trein[] do conjunto treinamento, comparando os valores para descobrir o máximo e mínimo de cada coluna
    float max_massa = 0, max_comprimento = 0, max_dimensao = 0;
    float min_massa = 1000, min_comprimento = 1000, min_dimensao = 1000;

    int c = 1, count = 0;
    while(count < treinamento){
        if(mass_trein[c] > max_massa){
            max_massa = mass_trein[c];
        }
        if(mass_trein[c] < min_massa){
            min_massa = mass_trein[c];
        }  
        c++;
        count++;
    }

    c = 1, count = 0;
    while(count < treinamento){
        if(compr_trein[c] > max_comprimento){
            max_comprimento = compr_trein[c];
        }
        if(compr_trein[c] < min_comprimento){
            min_comprimento = compr_trein[c];
        } 
        c++;
        count++;
    }

    c = 1, count = 0;
    while(count < treinamento){
        if(dim_trein[c] > max_dimensao){
            max_dimensao = dim_trein[c];
        }
        if(dim_trein[c] < min_dimensao){
            min_dimensao = dim_trein[c];
        }
        c++;
        count++;
    }

    //Normalizar 
        //o programa percorre todos os dados por meio dos vetores massa, comprimento e dimensao, normalizando cada um de seus valores a partir da fórmula ((valor - min)/(max - min)*2-1), sendo o max e o min respectivos a cada vetor/coluna e para o vetor sexo normaliza com F = 1 e M = -1
    int j;
    int sexo_trein_norm[treinamento+1];
    int sexo_teste_norm[teste+1];
   
    j = 1;
    printf("\nConjunto Treinamento Normalizado: \n");
    while(j <= treinamento){
        mass_trein[j] = ((mass_trein[j] - min_massa)/(max_massa - min_massa))*2 - 1;
        compr_trein[j] = ((compr_trein[j] - min_comprimento)/(max_comprimento - min_comprimento))*2 - 1;
        dim_trein[j] = ((dim_trein[j] - min_dimensao)/(max_dimensao - min_dimensao))*2 - 1;

        if(sexo_trein[j] == 'F'){
            sexo_trein_norm[j] = 1;
        }
        else{
            sexo_trein_norm[j] = -1;
        }

        printf("%d: %.5f, %.5f, %.5f, %d\n", esp_trein[j], mass_trein[j], compr_trein[j], dim_trein[j], sexo_trein_norm[j]);

        j++;   
    }

    j = 1;
    printf("\nConjunto Teste Normalizado: \n");
    while(j <= teste){
        mass_teste[j] = ((mass_teste[j] - min_massa)/(max_massa - min_massa))*2 - 1;
        compr_teste[j] = ((compr_teste[j] - min_comprimento)/(max_comprimento - min_comprimento))*2 - 1;
        dim_teste[j] = ((dim_teste[j] - min_dimensao)/(max_dimensao - min_dimensao))*2 - 1;

        if(sexo_teste[j] == 'F'){
            sexo_teste_norm[j] = 1;
        }
        else{
            sexo_teste_norm[j] = -1;
        }

        printf("%d: %.5f, %.5f, %.5f, %d\n", esp_teste[j], mass_teste[j], compr_teste[j], dim_teste[j], sexo_teste_norm[j]); 
        
        j++;
    }

    //Treinando o Perceptron
    int N = treinamento;    //número de espécies do conjunto treinamento
    int n = 1;              //variável para percorrer os dados do conjunto treinamento durante o teste
    int v;                  //índice

    float u;     //u = ativação interna do neurônio
    int y, d, e; //e = erro (diferença entre a saída desejada e a saída real); 
                 //y = saída real;
                 //d = saída desejada;
    
    float w[4] = {0, 0, 0, 0};  //vetor peso, sendo o primero valor o bias - pesos inicializados com 0
    float neta = 0.01;          //taxa de aprendizado (learning rate)
    
    int erro_max = 0;         //erro desejado
    float erro = 1;           //controle do looping

    float E, u_E;   //E = soma dos erros quadráticos a cada reajuste de peso
                    //u_E = ativação interna de cada neurônio no cálculo do erro quadrático
    int y_E;        //y_E = saída real de cada neurônio no cálculo do erro quadrático
    
    while(erro > erro_max){ 
        printf("\n\nIteracao: %d", n);
        v = (n-1) % N + 1;

        printf("\nEspecie de Treinamento: %d", v);

        d = sexo_trein_norm[v];
        printf("\nSaida desejada: %d", d);
        
        //ativação interna do neurônio v
        u = w[0] + mass_trein[v]*w[1] + compr_trein[v]*w[2] + dim_trein[v]*w[3];
        printf("\nu= %.5f", u);

        //função de ativação
        if(u > 0){
            y = 1;
        }
        else{
            y = -1;
        }

        //erro
        e = d - y; 
        printf("\ne = d - y = %d - %d = %d", d, y, e);

        //ajuste dos pesos
        w[0] = w[0] + neta*e;
        w[1] = w[1] + mass_trein[v]*neta*e; 
        w[2] = w[2] + compr_trein[v]*neta*e;
        w[3] = w[3] + dim_trein[v]*neta*e;
        printf("\nNovos pesos: \nw[0] = %.5f \nw[1] = %.5f \nw[2] = %.5f \nw[3] = %.5f", w[0], w[1], w[2], w[3]);

        //soma dos erros quadráticos 
        E = 0;
        for(int a = 1; a <= treinamento; a++){
            u_E = w[0] + mass_trein[a]*w[1] + compr_trein[a]*w[2] + dim_trein[a]*w[3];
            
            if(u_E > 0){
                y_E = 1;
            }
            else{
                y_E = -1;
            }

            d = sexo_trein_norm[a];
            E += pow((d - y_E), 2);
        }
        E = E/N;
        erro = E;
        printf("\nerro (E) = %.5f", erro);
        
        n += 1;
    }

    //Teste do Perceptron
        //utilizando os últimos pesos obtidos no treinamento do perceptron, aplicamos para cada um dos dados do conjunto teste  
    printf("\n\nTeste:");
    printf("\nPesos: \nw[0] = %.5f \nw[1] = %.5f \nw[2] = %.5f \nw[3] = %.5f", w[0], w[1], w[2], w[3]);

    int v_femea = 0, f_femea = 0, v_macho = 0, f_macho = 0; //variáveis que armazenam valores da matriz de confusão, ou seja, quais resultados são verdadeiros e quais são falsos para cada classe (femea e macho)

    for(j = 1; j <= teste; j++){
        printf("\n\nEspecie de Teste %d", j);

        //ativação interna do neurônio j
        u = w[0] + mass_teste[j]*w[1] + compr_teste[j]*w[2] + dim_teste[j]*w[3];
        printf("\nu = %f", u);

        //função de ativação
        if(u > 0){
            y = 1;
        }
        else{
            y = -1;
        }
        d = sexo_teste_norm[j];
        printf("\ny = %d  x  d = %d", y, d); //comparação entre a saída real (y) e a saída desejada (d)

        //obtém os valores para a matriz de confusão
        if(y == d && d == 1){
            v_femea++;
        }
        else if(y == d && d == -1){
            v_macho++;
        }
        else if(y != d && d == 1){
            f_macho++;
        }
        else{
            f_femea++;
        }
    }

    //Matriz de Confusão
    printf("\n\n\n                                CLASS. TESTE:\n");
    printf("                                FEMEA           MACHO\n\n");
    printf("CLASS. REAL: FEMEA              %d              %d\n\n             MACHO              %d              %d", v_femea, f_macho, f_femea, v_macho);

    //Acurácia
        //accuracy = número de previsões corretas/número de previsões totais
    float accuracy = ((v_femea + v_macho)*1.0)/(teste *1.0);
    printf("\n\nA acuracia do conjunto teste e de %d/%d = %.5f = %.0f%%\n\n", v_femea + v_macho, teste, accuracy, accuracy*100);
}