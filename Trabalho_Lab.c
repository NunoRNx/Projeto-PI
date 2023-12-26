#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define Valor 100

typedef struct {
    int codigo;
    char nome[Valor];
    char telefone[Valor];
} Paciente;

typedef struct {
    int codigo;
    int dia;
    int mes;
    int ano;
    char refeicao[Valor];
    char alimento[Valor];
    int calorias;
} Dieta;

typedef struct {
    int codigo;
    int dia;
    int mes;
    int ano;
    char refeicao[Valor];
    int caloriasMin;
    int caloriasMax;
} PlanoNutricional;

void mostrarAjuda() {
    printf("\n");
    printf("Bem vindo ao programa.\n");
    printf("Este programa auxilia um gabinete de nutricao, a estudar os seus pacientes.\n");
    printf("Permite o carregamento de dados em estruturas, calculo de calorias consumidas, \n");
    printf("listagem de pacientes, tabelas de planos, entre outros.\n");
    printf("Quando executa o codigo ira lhe ser exibida esta informacao,\n");
    printf("para que perceba de que se trata e como funciona o programa.\n");
    printf("Vamos entao comecar por explicar.\n");
    printf("O carregamento do conteudo nas estruturas de dados pode ser feito atraves de ficheiros diferentes.\n"); 
    printf("Se o utilizador pretender carregar o conteudo a partir de ficheiros txt (;),\n");
    printf("devera passar como argumentos -p.txt -d.txt -pl.txt.\n");
    printf("Os argumentos nao necessitam de estar por esta ordem, precisam e de estar corretos.\n");
    printf("O programa ira identificar quais argumentos o utilizador inseriu\n");
    printf("e informar quais foram encontrados e quais faltam inserir.\n");
    printf("Se faltarem argumentos o utilizador devera preencher os dados manualmente,\n");
    printf("ou entao se quiser colocar novamente os argumentos corretos, devera sair\n");
    printf("do programa e inicia-lo novamente com a passagem dos argumentos corretos.\n");
    printf("Se o utilizador pretender carregar o conteudo a partir de ficheiros csv (excel),\n");
    printf("devera passar como argumentos -p.csv -d.csv -pl.csv.\n");
    printf("\n");
}

int lerPaciente(Paciente Saude[]) {
    FILE *fp;
    int i = 0, codigo;
    char nome[Valor], telefone[Valor];

    fp = fopen("pacientes.txt", "rt");

    if (fp != NULL) {
        printf("\nSucesso ao abrir o ficheiro pacientes.\n");
        do {
            fscanf(fp, "%d;%[^;];%s\n", &codigo, nome, telefone);
            Saude[i].codigo = codigo;
            strcpy(Saude[i].nome, nome);
            strcpy(Saude[i].telefone, telefone);

            printf("%d;%s;%s\n", Saude[i].codigo, Saude[i].nome, Saude[i].telefone);

            i++;
        } while ((!feof(fp) && (i < Valor)));  // end of file  feof ==> >0

        fclose(fp);
        return (i);
    } else {
        printf("\nErro ao abrir o ficheiro pacientes.\n");
        return (0);
    }
}

int lerDieta(Dieta Saude1[]) {
    FILE *fp;
    int i = 0, codigo, dia, mes, ano, calorias;
    char refeicao[Valor], alimento[Valor];

    fp = fopen("dietas.txt", "rt");

    if (fp != NULL) {
        printf("\nSucesso ao abrir o ficheiro dietas.\n");

        do {
            if (fscanf(fp, "%d;%d-%d-%d;%[^;];%[^;];%d cal\n", &codigo, &dia, &mes, &ano, refeicao, alimento, &calorias) ==
                7) {
                Saude1[i].codigo = codigo;
                Saude1[i].dia = dia;
                Saude1[i].mes = mes;
                Saude1[i].ano = ano;
                strcpy(Saude1[i].refeicao, refeicao);
                strcpy(Saude1[i].alimento, alimento);
                Saude1[i].calorias = calorias;

                printf("%d;%02d-%02d-%04d;%s;%s;%d cal\n", Saude1[i].codigo, Saude1[i].dia, Saude1[i].mes,
                       Saude1[i].ano,
                       Saude1[i].refeicao, Saude1[i].alimento, Saude1[i].calorias);
                i++;
            } else {
                break;  // Encerra o loop se a leitura falhar
            }
        } while (i < Valor && !feof(fp));

        fclose(fp);
        return i;
    } else {
        printf("\nErro ao abrir o ficheiro dietas.\n");
        return 0;
    }
}

int lerPlano(PlanoNutricional Saude2[]) {
    FILE *fp;
    int i = 0;

    fp = fopen("planosNutricionais.txt", "rt");

    if (fp != NULL) {
        printf("\nSucesso ao abrir o ficheiro planosNutricionais.\n");

        char linha[100];

        while (fgets(linha, sizeof(linha), fp) != NULL && i < Valor) {
            if (sscanf(linha, "%d;%d-%d-%d;%[^;];%d Cal, %d Cal",
                       &Saude2[i].codigo, &Saude2[i].dia, &Saude2[i].mes, &Saude2[i].ano,
                       Saude2[i].refeicao, &Saude2[i].caloriasMin, &Saude2[i].caloriasMax) == 7 && i < Valor) {

                printf("%d;%02d-%02d-%04d;%s;%d Cal, %d Cal\n",
                       Saude2[i].codigo, Saude2[i].dia, Saude2[i].mes, Saude2[i].ano,
                       Saude2[i].refeicao, Saude2[i].caloriasMin, Saude2[i].caloriasMax);

                i++;
            }
        }
        fclose(fp);
        return i;
    } else {
        printf("\nErro ao abrir o ficheiro planosNutricionais.\n");
        return 0;
    }
}

// Função para inserir manualmente os dados na estrutura Paciente
void inserirManualmentePaciente(Paciente Saude[], int *contador) {
    
    printf("Insira os dados do Paciente:\n");
    // Dados usados para inserir paciente
    Saude[*contador].codigo = *contador + 1; 
    printf("Codigo: "); scanf("%d", &Saude[*contador].codigo);
    printf("Nome: "); scanf("%s", Saude[*contador].nome);
    printf("Telefone: "); scanf("%s", Saude[*contador].telefone);
    (*contador)++;
}

// Função para inserir manualmente os dados na estrutura Dieta
void inserirManualmenteDieta(Dieta Saude1[], int *contador) {
    
    printf("Insira os dados da Dieta:\n");
    // Dados usados para inserir dieta
    printf("Codigo: "); scanf("%d", &Saude1[*contador].codigo);
    printf("Dia: "); scanf("%d", &Saude1[*contador].dia);
    printf("Mes: "); scanf("%d", &Saude1[*contador].mes);
    printf("Ano: "); scanf("%d", &Saude1[*contador].ano);
    printf("Refeicao: "); scanf(" %[^\n]", Saude1[*contador].refeicao);
    printf("Alimento: "); scanf("%s", Saude1[*contador].alimento);
    printf("Calorias: "); scanf("%d", &Saude1[*contador].calorias);   
    (*contador)++;
}

// Função para inserir manualmente os dados na estrutura PlanoNutricional
void inserirManualmentePlano(PlanoNutricional Saude2[], int *contador) {

    printf("Insira os dados do PlanoNutricional:\n");
    // Dados usados para inserir plano
    printf("Codigo: "); scanf("%d", &Saude2[*contador].codigo);
    printf("Dia: "); scanf("%d", &Saude2[*contador].dia);
    printf("Mes: "); scanf("%d", &Saude2[*contador].mes);
    printf("Ano: "); scanf("%d", &Saude2[*contador].ano);
    printf("Refeicao: "); scanf(" %[^\n]", Saude2[*contador].refeicao);
    printf("CaloriasMin: "); scanf("%d", &Saude2[*contador].caloriasMin);
    printf("CaloriasMax: "); scanf("%d", &Saude2[*contador].caloriasMax);
    (*contador)++;
}

int main(int argc, char *argv[]) {

    // Exibe a ajuda se o programa for iniciado sem argumentos ou se -ajuda for fornecido
    if (argc == 1 || (argc == 2 && strcmp(argv[1], "-ajuda") == 0)) {
        mostrarAjuda();
        return 0;
    }

    printf("\nParametros inseridos: \n");
    for (int i = 0; i < argc; i++) {
        printf("%s ", argv[i]);
    }
    printf("\n");

    // Flags para verificar se cada parâmetro foi fornecido corretamente
    int parametroP = 0;
    int parametroD = 0;
    int parametroPL = 0;

    // Verificar os parâmetros fornecidos pelo utilizador
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p.txt") == 0) {
            parametroP = 1;
        } else if (strcmp(argv[i], "-d.txt") == 0) {
            parametroD = 1;
        } else if (strcmp(argv[i], "-pl.txt") == 0) {
            parametroPL = 1;
        }
    }

    // Executar as funções correspondentes ou inserir manualmente se necessário
    int contadorP = 0, contadorD = 0, contadorPL = 0; Paciente Saude[Valor]; Dieta Saude1[Valor]; PlanoNutricional Saude2[Valor];

    if (parametroP) {
        Paciente Saude[Valor];
        printf("\nParametro -p.txt encontrado.\n");
        lerPaciente(Saude);

    } else {
        printf("\nErro: Falta inserir o parametro -p.txt.\n");
        // Inserir paciente manualmente enquanto o utilizador desejar
        while (1) {
            inserirManualmentePaciente(Saude, &contadorP);
            printf("Deseja inserir mais um paciente manualmente? (S/N): ");
            char resposta;
            scanf(" %c", &resposta);
            if (toupper(resposta) != 'S') break;
        }

    // Imprimir os valores dos pacientes inseridos manualmente pelo utilizador
    printf("\nPacientes inseridos pelo utilizador: \n");
    for (int i = 0; i < contadorP; i++) {
        printf("Codigo: %d, Nome: %s, Telefone: %s\n", Saude[i].codigo, Saude[i].nome, Saude[i].telefone);
        }
    }

    if (parametroD) {
        Dieta Saude1[Valor];
        printf("\nParametro -d.txt encontrado.\n");
        lerDieta(Saude1);
    } else {
        printf("\nErro: Falta inserir o parametro -d.txt.\n");
        //Inserir dieta manualmente enquanto o utilizador desejar
        while (1) {
            inserirManualmenteDieta(Saude1, &contadorD);
            printf("Deseja inserir mais uma dieta manualmente? (S/N): ");
            char resposta;
            scanf(" %c", &resposta);
            if (toupper(resposta) != 'S') break;
        }

    // Imprimir os valores das dietas inseridos manualmente pelo utilizador
    printf("\nDietas inseridos pelo utilizador: \n");
    for (int i = 0; i < contadorD; i++) {
        printf("Codigo: %d, Data: %02d-%02d-%04d, Refeicao: %s, Alimento: %s, Calorias: %d\n", 
        Saude1[i].codigo, Saude1[i].dia, Saude1[i].mes, Saude1[i].ano,
        Saude1[i].refeicao, Saude1[i].alimento, Saude1[i].calorias);
        }
    }

if (parametroPL) {
        PlanoNutricional Saude2[Valor];
        printf("\nParametro -pl.txt encontrado.\n");
        lerPlano(Saude2);
    } else {
        printf("\nErro: Falta inserir o parametro -pl.txt.\n");
        //Inserir plano nutricional manualmente enquanto o utilizador desejar
        while (1) {
            inserirManualmentePlano(Saude2, &contadorPL);
            printf("Deseja inserir mais um plano nutricional manualmente? (S/N): ");
            char resposta;
            scanf(" %c", &resposta);
            if (toupper(resposta) != 'S') break;
        }

        // Imprimir os valores dos planos nutricionais inseridos manualmente pelo utilizador
        printf("\nPlanos Nutricionais inseridos pelo utilizador: \n");
        for (int i = 0; i < contadorPL; i++) {
        printf("Codigo: %d, Data: %02d-%02d-%04d, Refeicao: %s, CaloriasMin: %d, CaloriasMax: %d\n", 
        Saude2[i].codigo, Saude2[i].dia, Saude2[i].mes, Saude2[i].ano,
        Saude2[i].refeicao, Saude2[i].caloriasMin, Saude2[i].caloriasMax);
        }
    }

    return 0;
}