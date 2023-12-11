#define max 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data {
    int dia;
    int mes;
    int ano;
    int full;
};
struct Lista {
    char codec[max];
    char refeicao[max];
    int codei;
};
struct Lpac {
    char code[max];
    char nome[max];
    char tele[max];
};
struct Lnut {
    char code[max];
    struct Data data;
    char refeicao[max];
    char alimento[max];
    int cal;
};
struct Lplan {
    char code[max];
    struct Data data;
    char refeicao[max];
    int calmin;
    int calmax;
};

int verificarFile(char* filename);
int paciente(struct Lpac pac[], int qt[]);
int nutricao(struct Lpac pac[],struct Lnut nut[], int qt[]);
int plano(struct Lpac pac[],struct Lplan pl[], int qt[]);
int leitura(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[], int qt[]);
int periodo(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[],int qt[]);
int ListarPaciente(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[], int qt[]);
int refeicao(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[], int qt[]);
int medRefeicao(struct Lpac pac[],struct Lnut nut[], int qt[]);
int remover(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[], int qt[], char apagado[], int v);
int data(int *dia, int *mes, int *ano);
int verifperiodo(int *data0, int *data1);

int main() {
    FILE *file; // Declare a file pointer
    char filename[3][max], apagado[max], resp2[1];
    int resp=0,v=0, i, qt[3];
    struct Lnut nut[max];
    struct Lpac pac[max];
    struct Lplan plan[max];
    strcpy(filename[0], "paciente.txt");
    strcpy(filename[1], "nutricao.txt");
    strcpy(filename[2], "plano.txt");
    system("CLS");

    for (i = 0; i < 3; i++)
    {
        if (!verificarFile(filename[i]))
        {
        file = fopen(filename[i], "w");
        printf("\nFicheiro %s criado.", filename[i]);
        fclose(file);
        }
        else{
            file = fopen(filename[i], "a");
        }
    }
    printf("\n\n");
    leitura(pac,nut,plan,qt);
    system("pause");
    do
    {
        system("CLS");
        printf("1-Criar novo resgistro de paciente\n");
        printf("2-Criar novo registro de alimentacao\n");
        printf("3-Criar novo plano de nutricao\n");
        printf("4-Numero de pacientes que ultrapassaram determinada quantidade de calorias, num determinado periodo\n");
        printf("5-Listagem de Pacientes querealizaram alguma refeição com quantidade de calorias fora do intervalo\n");
        printf("6-Plano nutricional de um paciente para determinada refeição\n");
        printf("7-Medias da calorias consumidas por refeição por cada paciente\n");
        printf("8-Remover dados de um paciente\n");
        printf("9-Sair\n\n");
        printf("Resp:\t");
        scanf("%d", &resp);
        switch (resp)
        {
        case 1:
            paciente(pac,qt);
            leitura(pac,nut,plan,qt);
            if (v>0)
            {
                remover(pac,nut,plan,qt,apagado,v);
            }
            system("pause");
            break;
        case 2:
            nutricao(pac,nut,qt);
            leitura(pac,nut,plan,qt);
            system("pause");
            break;
        case 3:
            plano(pac,plan,qt);
            leitura(pac,nut,plan,qt);
            system("pause");
            break;
        case 4:
            periodo(pac,nut,plan,qt);
            system("pause");
            break;
        case 5:
            ListarPaciente(pac,nut,plan,qt);
            system("pause");
            break;
        case 6:
            refeicao(pac,nut,plan,qt);
            system("pause");
            break;
        case 7:
            medRefeicao(pac,nut,qt);
            system("pause");
            break;
        case 8:
            printf("Deseja remover algum paciente e todos os seus dados? (S/N)\nO paciente nao ira ser apagado dos ficheiro apenas nao ira ser mais utilizado nesta sessao.\n");
            scanf(" %c",resp2);
            if (resp2 =="s" || resp2 == "S")
            {
                printf("Qual o codigo do paciente que deseja remover?\nResp: ");
                scanf(" %[^\n]%*c", apagado[v]);
                v=remover(pac,nut,plan,qt,apagado,v);
            }
            system("pause");
            break;
        case 9:
            break;
        default:
            printf("Por favor insira um dos valores indicados\n");
            system("pause");
            break;
        }
    } while (resp!=9);
    return 0;
}

int verificarFile(char* filename){
    FILE *file; // Declare a file pointer
    file=fopen(filename, "r");

    if(file==NULL){
        printf("%s nao existe, a criar...\n", filename);
        return 0;
    }else{
        printf("%s ja existe\n", filename);
        return 1;
    }
    fclose(file);
}

int paciente(struct Lpac pac[], int qt[]){
    FILE *file; // Declare a file pointer
    char nump[max], numt[max], nome[max];
    int i, x=0;
    file = fopen("paciente.txt", "a");
    do{
        printf("\nNumero de paciente?\n");
        scanf(" %[^\n]%*c", nump);
        for (i = 0; i < qt[0]; i++)
        {
            if (strcmp(pac[i].code,nump)==0)
            {
                printf("Codigo ja foi utilizado, tente um codigo diferente.\n");
            }else{
                x++;
            }
        }
    }while(x==0);
    
    fprintf(file, "%s;", nump);
    printf("\nNome do paciente?\n");
    scanf(" %[^\n]%*c", nome);
    fprintf(file, "%s;", nome);
    printf("\nNumero de telemovel?\n");
    scanf(" %[^\n]%*c", numt);
    fprintf(file, "%s\n", numt);
    fclose(file);
    printf("\nRegisto do paciente criado.\n");
    return 0;
}

int nutricao(struct Lpac pac[],struct Lnut nut[], int qt[]){
    FILE *file; // Declare a file pointer
    char nump[max], ref[max], ali[max];
    int i=0, x=0, r, mes, dia, ano, cal;
    file = fopen("nutricao.txt", "a");
    
    do{
        printf("\nNumero de paciente?\n");
        scanf(" %[^\n]%*c", nump);
        for (i = 0; i < qt[0]; i++)
        {
            if (strcmp(pac[i].code,nump)==0)
            {
                x++;
            }else{
                printf("Codigo de paciente nao esta atribuido a nenhum paciente");
            }
        }
    }while(x==0);
    fprintf(file, "%s;", nump);
    data(&dia, &mes, &ano);
    fprintf(file, "%d-%d-%d;", dia, mes, ano);
    printf("\nTipo de refeicao:\n");
    scanf(" %[^\n]%*c", ref);
    fprintf(file, "%s;", ref);
    printf("\nAlimento:\n");
    scanf(" %[^\n]%*c", ali);
    fprintf(file, "%s;", ali);
    printf("\nCalorias:\n");
    scanf(" %d", &cal);
    fprintf(file, "%d cal\n", cal);
    fclose(file);
    return 0;
}

int plano(struct Lpac pac[],struct Lplan pl[], int qt[]){
    FILE *file; // Declare a file pointer
    char nump[max], ref[max], ali[max];
    int i=0, x=0, r, mes, dia, ano, min, maxc;
    file = fopen("plano.txt", "a");
    
    do{
        printf("\nNumero de paciente?\n");
        scanf(" %[^\n]%*c", nump);
        for (i = 0; i < qt[0]; i++)
        {
            if (strcmp(pac[i].code,nump)==0)
            {
                x++;
            }else{
                printf("Codigo de paciente nao esta atribuido a nenhum paciente");
            }
        }
    }while(x==0);
    fprintf(file, "%s;", nump);
    data(&dia, &mes, &ano);
    fprintf(file, "%d-%d-%d;", dia, mes, ano);
    printf("\nTipo de refeicao:\n");
    scanf(" %[^\n]%*c", ref);
    //scanf(" %s", &ref);
    fprintf(file, "%s;", ref);
    printf("\nCalorias:\n");
    printf("\nMinimo:\t");
    scanf(" %d", &min);
    printf("\nMaximo:\t");
    scanf(" %d", &maxc);
    fprintf(file, "%d cal, %d cal\n", min, maxc);
    fclose(file);
    return 0;
}

int leitura(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[], int qt[]){
    int i=0;
    char code[max];
    FILE *filep=fopen("paciente.txt", "r"); 
    FILE *filen=fopen("nutricao.txt", "r"); 
    FILE *filepl=fopen("plano.txt", "r");

    while (fscanf(filep, "%[^;];%[^;];%[^\n]\n", pac[i].code, pac[i].nome, pac[i].tele) == 3) {
        i++;
    }
    qt[0]=i;
    i=0;
    while (fscanf(filen, "%[^;];%d-%d-%d;%[^;];%[^;];%d%*[^\n]\n", nut[i].code, &nut[i].data.dia, &nut[i].data.mes, &nut[i].data.ano, nut[i].refeicao, nut[i].alimento, &nut[i].cal) == 7) {
        nut[i].data.full=nut[i].data.ano*10000+nut[i].data.mes*100+nut[i].data.dia;
        i++;
    }
    qt[1]=i;
    i=0;
    while (fscanf(filepl, "%[^;];%d-%d-%d;%[^;];%d%*[^,], %d%*[^\n]\n", pl[i].code, &pl[i].data.dia, &pl[i].data.mes, &pl[i].data.ano, pl[i].refeicao, &pl[i].calmin, &pl[i].calmax) == 7) {
        pl[i].data.full=pl[i].data.ano*10000+pl[i].data.mes*100+pl[i].data.dia;
        i++;
    }
    qt[2]=i;
    
    fclose(filep);
    fclose(filen);
    fclose(filepl);
    return 0;
}

int periodo(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[],int qt[]){
    int i, x, num=0, cal=0, caltotal=0, mincal=0, maxcal=0, calc=0, data0, data1, datan, datapl;
    char code[max];
    
    verifperiodo(&data0, &data1);
    system("pause");     
    for (i = 0; i < qt[0]; i++)
    {
        maxcal=0;
        mincal=0;
        caltotal=0;
        for (x = 0; x < qt[1]; x++)
        {
            if (strcmp(pac[i].code, nut[x].code) == 0) {
                if (data0<=nut[x].data.full && nut[x].data.full<=data1) {
                    caltotal += cal;
                }
            }
        }
        for (x = 0; x < qt[1]; x++)
        {
            if (strcmp(pac[i].code, pl[x].code) == 0) {
                if (data0<=pl[x].data.full && pl[x].data.full<=data1) {
                    maxcal+=pl[x].calmax;
                    mincal+=pl[x].calmin;
                }
            }
        }
        if (caltotal > maxcal || caltotal < mincal) {
                num++;
        }
    }
    if (num==0)
    {
        printf("\nTodos os pacientes cumpriram com o plano no periodo determinando.\n");
    }else{
        printf("\n%d pacientes nao cumpriram com o plano no periodo determinado\n", num);
    }
    system("pause");
    return 0;
}

int ListarPaciente(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[],int qt[]){
    int i=0, x, y, v=0,z=0, num=0, cal=0, caltotal=0, data0, data1, copyi;
    char code[max], copyc[max], refeicaon[max], refeicaop[max];
    struct Lista li[max];

    verifperiodo(&data0, &data1);
    system("cls");
    for (i = 0; i < qt[0]; i++)
    {
        v=0;
        for (x = 0; x < qt[1]; x++)
        {
            if (strcmp(pac[i].code, nut[x].code) == 0) {
                if (data0<=nut[x].data.full && nut[x].data.full<=data1) {
                    for (y = 0; y < qt[2]; y++)
                    {
                        if (strcmp(pac[i].code, pl[y].code)==0)
                        {
                            if (nut[x].data.full==pl[y].data.full)
                            {
                                if (strcmp(nut[x].refeicao, pl[y].refeicao) == 0)
                                {
                                    if (pl[y].calmin>nut[x].cal || nut[x].cal>pl[y].calmax)
                                    {                                  
                                        strcpy(li[z].codec,pac[i].code);
                                        strcpy(li[z].refeicao,pl[y].refeicao);
                                        li[z].codei = atoi(li[z].codec);
                                        z++;
                                        v++;
                                    }
                                } 
                            } 
                        }
                        if (v>0)
                        {
                            y=qt[2];
                        }
                    }
                }
            }
        }
        if (v>0)
        {
            x=qt[1];
        }
    }
    for (i = 0; i < x; i++)
    {
        if (i==0)
        {
        }else{
            x=i;
            while (li[x].codei<li[x-1].codei && x-1>=0)
            {
                copyi=li[x-1].codei;
                strcpy(copyc, li[x-1].codec);
                li[x-1].codei=li[x].codei;
                strcpy(li[x-1].codec, li[x].codec);
                li[x].codei=copyi;
                strcpy(li[x].codec, copyc);
                x--;
            }
        }
    }
    if (v==0)
    {
        printf("Nenhum pacientes realizou alguma refeição com quantidade de calorias fora do intervalo no periodo determinado\n");
    }else{    
        printf("Pacientes que realizaram alguma refeição com quantidade de calorias fora do intervalo no periodo determinado\n");
        for (x = 0; x < 2; x++)
        {
            printf("Refeicao:%s\nPaciente:%s\n\n",li[x].refeicao,li[x].codec);
        }
    }
    return 0;
}

int refeicao(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[],int qt[]){
    int i,x,v,data0,data1;
    char refeicao[max];
    system("cls");
    verifperiodo(&data0, &data1);
    printf("\nRefeicao?\nResp: ");
    scanf(" %[^\n]%*c", refeicao);
    for (i = 0; i < qt[0]; i++)
    {
        v=0;
        printf("\nPaciente: %s\n", pac[i].code);
        for (x = 0; x < qt[2]; x++)
        {
            if (strcmp(pac[i].code, pl[x].code) == 0)
            {
                if (data0<=pl[x].data.full && pl[x].data.full<=data1)
                {
                    if (strcmp(refeicao, pl[x].refeicao) == 0)
                    {
                        printf("Dia: %d-%d-%d\n", pl[x].data.dia, pl[x].data.mes, pl[x].data.ano);
                        printf("Calorias:\n");
                        printf("Minimas: %d\n",pl[x].calmin);
                        printf("Maximas: %d\n",pl[x].calmax);
                        v++;
                    }
                }
            }
        }
        if (v==0)
        {
            printf("O paciente %s nao tem nenhum plano para a refeicao %s no periodo que indicou.\n", pac[i].code, refeicao);
        }
    }
    system("pause");
    return 0;
}

int medRefeicao(struct Lpac pac[],struct Lnut nut[],int qt[]){
    int i=0, x, cont, data0, data1;
    float media, caltotal;

    verifperiodo(&data0, &data1);

    for (i = 0; i < qt[0]; i++)
    {
        caltotal=0;
        cont=0;
        for (x = 0; x < qt[1]; x++)
        {
            if (strcmp(pac[i].code, nut[x].code) == 0) {
                if (data0<=nut[x].data.full && nut[x].data.full<=data1)
                {
                    caltotal+=nut[x].cal;
                    cont++;
                }
            }
        }
        media=caltotal/cont;
        printf("\nPaciente: %s\n", pac[i].code);
        printf("Media de calorias por refeicao: %.1f\n", media);
    }
    system("pause");
    return 0;
}

int remover(struct Lpac pac[],struct Lnut nut[],struct Lplan pl[], int qt[], char apagado[], int v){
    int i, x, e=0, d=0;
    for (i = 0; i < v; i++)
    {
        for (x = 0; x < qt[0]; x++)
        {
            if (strcmp(apagado[i],pac[x].code)==0)
            {
                pac[x]=pac[qt[0]];
                qt[0]--;
                e++;
            }
        }
        if (e==0)
        {
            printf("Nenhum paciente com o codigo %s presente em 'paciente.txt'", apagado[i]);
        }else{
            for (x = 0; x < qt[1]; x++)
            {
                if (strcmp(apagado[i],nut[x].code)==0)
                {
                    nut[x]=nut[qt[1]];
                    qt[1]--;
                }
            }
            for (x = 0; x < qt[2]; x++)
            {
                if (strcmp(apagado[i],pl[x].code)==0)
                {
                    pl[x]=pl[qt[2]];
                    qt[2]--;
                }
            }
            d++;
        }
    }
    if (d==0)
    {
        return v;
    }else{
        return v+1;
    }
}

int data(int *dia, int *mes, int *ano){
    int x, i;
    do
    {
        x=0;
        system("CLS");
        printf("\nInsira a data no seguinte formato dd-mm-yyyy:\nData: ");
        scanf("%d-%d-%d", dia, mes, ano);
        if (*mes<1 || *mes > 12)
        {
            x++;
           printf("\n\nMes invalido.\n");
           system("pause");
        }
        if (*dia<1 || *dia > 31)
        {
            x++;
           printf("\n\nDia invalido.\n");
           system("pause");
        }
        switch (*mes)
        {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
            //meses com 31 dias
                break;
            case 2:
            //verificar 28/29
                if(*ano%4 == 0){
                    if (*dia>29)
                    {
                        if (i==0)
                        {
                            printf("\nData minima nao e valida, o mes %d contem apenas 29 dias, tente novamente\n", *mes);
                            x++;
                        }else{
                            printf("\nData maxima nao e valida, o mes %d contem apenas 29 dias, tente novamente\n", *mes);
                            x++;
                        }
                    }else{
                        if (*dia>28)
                        {
                            if (i==0)
                            {
                                printf("\nData minima nao e valida, o mes %d contem apenas 28 dias dias no ano %d.\n", *mes, *ano);
                                x++;
                            }else{
                                printf("\nData maxima nao e valida, o mes %d contem apenas 28 dias dias no ano %d.\n", *mes, *ano);
                                x++;
                            }
                        }
                    }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
            //verificar 30 dias
                if (*dia>30)
                    {
                        if (i==0)
                        {
                            printf("\nData minima nao e valida, o mes %d contem apenas 30 dias.\n", *mes);
                            x++;
                        }else{
                            printf("\nData maxima nao e valida, o mes %d contem apenas 30 dias.\n", *mes);
                            x++;
                        }
                    }
                break;
            default:
                break;
            }
        }
        if (x!=0)
        {
            printf("\nPor favor tente novamente.\n");
            
        }else{
            printf("\nPeriodo valido!\n");
        }
        system("pause");
    } while (x!=0);
    return 0;
}

int verifperiodo(int *data0, int *data1){
    int i, x, dia[2], mes[2],ano[2];
    char code[max];

    system("CLS");
    do
    {
        x=0;
        printf("\nInsira periodo no seguinte formato (De dd-mm-yyyy / Ate dd-mm-yyyy):\n");
        printf("De: ");
        scanf("%d-%d-%d", &dia[0], &mes[0], &ano[0]);
        printf("Ate: ");
        scanf("%d-%d-%d", &dia[1], &mes[1], &ano[1]);
        *data0=ano[0]*10000+mes[0]*100+dia[0];
        *data1=ano[1]*10000+mes[1]*100+dia[1];

        if (*data0>*data1)
        {
            x++;
            printf("\nData inicial maior que data final.\n");
        }
        
        if ((mes[0]<1 || mes[0] > 12) || (mes[1]<1 || mes[1] > 12))
        {
            x++;
           printf("\n\nMes invalido.\n");
        }
        if ((dia[0]<1 || dia[0] > 31) || (dia[1]<1 || dia[1] > 31))
        {
            x++;
           printf("\n\nDia invalido.\n");
        }
        
        for ( i = 0; i < 2; i++)
        {
            switch (mes[i])
            {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12:
                //meses com 31 dias
                    break;
                case 2:
                //verificar 28/29
                    if(ano[i]%4 == 0){
                        if (dia[i]>29)
                        {
                            if (i==0)
                            {
                                printf("\nData minima nao e valida, o mes %d contem apenas 29 dias no ano %d.\n", mes[i], ano[i]);
                                x++;
                            }else{
                                printf("\nData maxima nao e valida, o mes %d contem apenas 29 dias no ano %d.\n", mes[i], ano[i]);
                                x++;
                            }
                        }
                    }else{
                        if (dia[i]>28)
                        {
                            if (i==0)
                            {
                                printf("\nData minima nao e valida, o mes %d contem apenas 28 dias no ano %d.\n", mes[i], ano[i]);
                                x++;
                            }else{
                                printf("\nData maxima nao e valida, o mes %d contem apenas 28 dias no ano %d.\n", mes[i], ano[i]);
                                x++;
                            }
                        }
                    }
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                //verificar 30 dias
                    if (dia[i]>30)
                        {
                            if (i==0)
                            {
                                printf("\nData minima nao e valida, o mes %d contem apenas 30 dias.\n", mes[i]);
                                x++;
                            }else{
                                printf("\nData maxima nao e valida, o mes %d contem apenas 30 dias.\n", mes[i]);
                                x++;
                            }
                        }
                    break;
                default:
                    break;
            }
        }
        if (x!=0)
        {
            printf("\nPor favor tente novamente.\n");
            
        }else{
            printf("\nPeriodo valido!\n");
        }
        system("pause");
    } while (x!=0);
    return 0;
}