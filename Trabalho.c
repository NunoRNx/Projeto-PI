#define max 100
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>

int verificarFile();
int paciente();
int nutricao();
int plano();
int periodo();

struct Maximo {
    int ano;
    int mes;
    int dia;
};
struct Minimo {
    int ano;
    int mes;
    int dia;
};
struct Plano {
    char code[max];
    int ano;
    int mes;
    int dia;
    int calmin;
    int calmax;
};
struct Nutri {
    char code[max];
    int ano;
    int mes;
    int dia;
};

int main() {
    FILE *file; // Declare a file pointer
    char filename[3][max];
    int resp=0, resp2=0, i;
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
    system("pause");
    do
    {
        system("CLS");
        printf("1-Criar novo resgistro de paciente\n");
        printf("2-Criar novo registro de alimentacao\n");
        printf("3-Criar novo plano de nutricao\n");
        //printf("4-Eliminar ficheiros\n");
        printf("4-Numero de pacientes que ultrapassaram determinada quantidade de calorias, num determinado periodo\n");
        printf("5-Sair\n");
        printf("Resp:\t");
        scanf("%d", &resp);
        switch (resp)
        {
        case 1:
            paciente();
            break;
        case 2:
            nutricao();
            break;
        case 3:
            plano();
            break;
        case 4:
            periodo();
            system("pause");
            break;
        case 5:
            break;
        default:
            printf("Por favor insira um dos valores indicados");
            break;
        }
    } while (resp!=5);
    
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

int paciente(){
    FILE *file; // Declare a file pointer
    char nump[max], numt[max], nome[max];
    int i=0, x=0;
    file = fopen("paciente.txt", "a");

    printf("\nNumero de paciente?\n");
    scanf(" %[^\n]%*c", nump);
    //scanf(" %s", &nump);
    fprintf(file, "%s;", nump);
    printf("\nNome do paciente?\n");
    scanf(" %[^\n]%*c", nome);
    //scanf(" %s", nome);
    fprintf(file, "%s;", nome);
    printf("\nNumero de telemovel?\n");
    scanf(" %[^\n]%*c", numt);
    //scanf(" %s", &numt);
    fprintf(file, "%s\n", numt);
    fclose(file);

    return 0;
}

int nutricao(){
    FILE *file; // Declare a file pointer
    char nump[max], ref[max], ali[max];
    int i=0, x=0, r, mes, dia, ano, cal;
    file = fopen("nutricao.txt", "a");
    
    printf("\nNumero de paciente?\n");
    scanf(" %[^\n]%*c", nump);
    //scanf(" %s", &nump);
    fprintf(file, "%s;", nump);
    
    do
    {
        printf("\nData:\n");
        printf("\nAno:\t");
        scanf("%d", &ano);
        if (ano>2023)
        {
            printf("Ano invalido tente novamente\n");
        }
    } while (ano>2023);
    do
    {
        printf("\nMes (1-12):\t");
        scanf(" %d", &mes);
        if (mes<1 || mes > 12)
        {
           printf("\n\nMes invalido tente novamente\n");
           system("pause");
        }
    } while (mes<1 || mes > 12);
    switch (mes)
    {
        case 1:
            
        case 3:
            
        case 5:
            
        case 7:
            
        case 8:
            
        case 10:
            
        case 12:
        //verificar 31
            do
            {
                printf("\nDia:\t");
                scanf("%d", &dia);
                if (dia>31 || dia<1)
                {
                    printf("\nDia invalido tente novamente\n");
                }
                
            } while (dia>31 || dia<1);
            break;
        case 2:
        //verificar 28/29
            if(ano%4 == 0){
                do
                {
                    printf("\nDia:\t");
                    scanf("%d", &dia);
                    if (dia>29 || dia<1)
                    {
                        printf("\nDia invalido tente novamente\n");
                    }
                    
                }while (dia>29 || dia<1);
            }else{
                do
                {
                    printf("\nDia:\t");
                    scanf("%d", &dia);
                    if (dia>28 || dia<1)
                    {
                        printf("\nDia invalido tente novamente\n");
                    }
                    
                }while (dia>28 || dia<1);
            }
            break;
        case 4:
        case 6:
            
        case 9:
        case 11:
        //verificar 30 dias
            do
            {
                printf("\nDia:\t");
                scanf("%d", &dia);
                if (dia>30 || dia<1)
                {
                    printf("\nDia invalido tente novamente\n");
                }
                
            } while (dia>30 || dia<1);
            break;
        
        default:
            break;
    }
    fprintf(file, "%d-%d-%d;", dia, mes, ano);
    printf("\nTipo de refeicao:\n");
    scanf(" %[^\n]%*c", ref);
    //scanf(" %s", &ref);
    fprintf(file, "%s;", ref);
    printf("\nAlimento:\n");
    scanf(" %[^\n]%*c", ali);
    //scanf(" %s", &ali);
    fprintf(file, "%s;", ali);
    printf("\nCalorias:\n");
    scanf(" %d", &cal);
    fprintf(file, "%d cal", cal);
    fprintf(file, "\n");
    fclose(file);

    return 0;
}


int plano(){
    FILE *file; // Declare a file pointer
    char nump[max], ref[max], ali[max];
    int i=0, x=0, r, mes, dia, ano, min, maxc;
    file = fopen("plano.txt", "a");
    
    printf("\nNumero de paciente?\n");
    scanf(" %[^\n]%*c", nump);
    //scanf(" %s", &nump);
    fprintf(file, "%s;", nump);
    
    do
    {
        printf("\nData:\n");
        printf("\nAno:\t");
        scanf("%d", &ano);
        if (ano>2023)
        {
            printf("Ano invalido tente novamente\n");
        }
    } while (ano>2023);
    do
    {
        printf("\nMes (1-12):\t");
        scanf(" %d", &mes);
        if (mes<1 || mes > 12)
        {
           printf("\n\nMes invalido tente novamente\n");
           system("pause");
        }
    } while (mes<1 || mes > 12);
    switch (mes)
    {
        case 1:
            
        case 3:
            
        case 5:
            
        case 7:
            
        case 8:
            
        case 10:
            
        case 12:
        //verificar 31
            do
            {
                printf("\nDia:\t");
                scanf("%d", &dia);
                if (dia>31 || dia<1)
                {
                    printf("\nDia invalido tente novamente\n");
                }
                
            } while (dia>31 || dia<1);
            break;
        case 2:
        //verificar 28/29
            if(ano%4 == 0){
                do
                {
                    printf("\nDia:\t");
                    scanf("%d", &dia);
                    if (dia>29 || dia<1)
                    {
                        printf("\nDia invalido tente novamente\n");
                    }
                    
                }while (dia>29 || dia<1);
            }else{
                do
                {
                    printf("\nDia:\t");
                    scanf("%d", &dia);
                    if (dia>28 || dia<1)
                    {
                        printf("\nDia invalido tente novamente\n");
                    }
                    
                }while (dia>28 || dia<1);
            }
            break;
        case 4:
        case 6:
            
        case 9:
        case 11:
        //verificar 30 dias
            do
            {
                printf("\nDia:\t");
                scanf("%d", &dia);
                if (dia>30 || dia<1)
                {
                    printf("\nDia invalido tente novamente\n");
                }
                
            } while (dia>30 || dia<1);
            break;
        
        default:
            break;
    }
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

int periodo(){
    struct Maximo maxi;
    struct Minimo min;
    struct Nutri nut;
    struct Plano plan;
    int ano[2], mes[2], dia[2], i, x, num=0, cal=0, caltotal=0, mincal=0, maxcal=0, calc=0;
    char code[max];

    FILE *filep=fopen("paciente.txt", "r"); 
    FILE *filen=fopen("nutricao.txt", "r"); 
    FILE *filepl=fopen("plano.txt", "r");

    do
    {
        x=0;
        system("CLS");
        printf("\nInsira periodo no seguinte formato (De dd/mm/yyyy - Ate dd/mm/yyyy):\n");
        printf("De: ");
        scanf("%d-%d-%d", &min.dia, &min.mes, &min.ano);
        printf("Ate: ");
        scanf("%d-%d-%d", &maxi.dia, &maxi.mes, &maxi.ano);
        if (min.ano==maxi.ano)
        {
            if (min.mes==maxi.mes)
            {
                if (min.dia>maxi.dia)
                {
                    x++;
                    printf("\nA data de inicio do periodo tem de ser menor que a data final.\n");
                }
            }
            if (min.mes>maxi.mes)
            {
                x++;
                printf("\nA data de inicio do periodo tem de ser menor que a data final.\n");
            }
        }
        if (min.ano>maxi.ano)
        {
            x++;
            printf("\nA data de inicio do periodo tem de ser menor que a data final.\n");
        }
        
        
        if ((min.mes<1 || min.mes > 12) && (maxi.mes<1 || maxi.mes > 12))
        {
            x++;
           printf("\n\nMes invalido tente novamente\n");
           system("pause");
        }
        if ((min.dia<1 || min.dia > 31) && (maxi.dia<1 || maxi.dia > 31))
        {
            x++;
           printf("\n\nDia invalido tente novamente\n");
           system("pause");
        }
        dia[0]=min.dia;
        mes[0]=min.mes;
        ano[0]=min.ano;
        dia[1]=maxi.dia;
        mes[1]=maxi.mes;
        ano[1]=maxi.ano;
        
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
                                printf("\nData minima nao e valida, o mes %d contem apenas 29 dias, tente novamente\n", mes[i]);
                                x++;
                            }else{
                                printf("\nData maxima nao e valida, o mes %d contem apenas 29 dias, tente novamente\n", mes[i]);
                                x++;
                            }
                        }
                    }else{
                        if (dia[i]>28)
                        {
                            if (i==0)
                            {
                                printf("\nData minima nao e valida, o mes %d contem apenas 28 dias, tente novamente\n", mes[i]);
                                x++;
                            }else{
                                printf("\nData maxima nao e valida, o mes %d contem apenas 28 dias, tente novamente\n", mes[i]);
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
                                printf("\nData minima nao e valida, o mes %d contem apenas 30 dias, tente novamente\n", mes[i]);
                                x++;
                            }else{
                                printf("\nData maxima nao e valida, o mes %d contem apenas 30 dias, tente novamente\n", mes[i]);
                                x++;
                            }
                        }
                    break;
                default:
                    break;
            }
        }
        system("pause");
    } while (x!=0);
    
    
    //
    
    while (fscanf(filep, "%[^;];%*[^\n]\n", code) == 1) {
        maxcal=0;
        mincal=0;
        caltotal=0;
        while (fscanf(filen, "%[^;];%d-%d-%d;%*[^;];%*[^;];%d cal\n", nut.code, &nut.dia, &nut.mes, &nut.ano, &cal) == 5) {
            if (strcmp(code, nut.code) == 0) {
                if (nut.ano > min.ano && nut.ano < maxi.ano) {
                    caltotal += cal;
                }else if (nut.ano == min.ano || nut.ano == maxi.ano) {
                    if ((nut.ano == maxi.ano && nut.mes < maxi.mes) || (nut.ano == min.ano && nut.mes > min.mes)) {
                        caltotal += cal;
                    }else if ((nut.ano == maxi.ano && nut.mes == maxi.mes && nut.dia <= maxi.dia) ||
                        (nut.ano == min.ano && nut.mes == min.mes && nut.dia >= min.dia)) {
                        caltotal += cal;
                    }
                }
            }
        }

        while (fscanf(filepl, "%[^;];%d-%d-%d;%*[^;];%d cal, %d%*[^\n]\n", plan.code, &plan.dia, &plan.mes, &plan.ano, &plan.calmin, &plan.calmax) == 6) {
            if (strcmp(code, plan.code) == 0) {
                if (plan.ano > min.ano && plan.ano < maxi.ano) {
                    maxcal+=plan.calmax;
                    mincal+=plan.calmin;
                }else if (plan.ano == min.ano || plan.ano == maxi.ano) {
                    if ((plan.ano == maxi.ano && plan.mes < maxi.mes) || (plan.ano == min.ano && plan.mes > min.mes)) {
                        maxcal+=plan.calmax;
                        mincal+=plan.calmin;
                    }else if ((plan.ano == maxi.ano && plan.mes == maxi.mes && plan.dia <= maxi.dia) ||
                        (plan.ano == min.ano && plan.mes == min.mes && plan.dia >= min.dia)) {
                        maxcal+=plan.calmax;
                        mincal+=plan.calmin;
                    }
                }
            }
        }
    
        if (caltotal > maxcal || caltotal < mincal) {
                num++;
        }
    }
    //debug: printf("\ncal %d, caltotal %d, maxcal %d, mincal %d\n", cal, caltotal, maxcal, mincal);
    printf("\n%d pacientes nao cumpriram com o plano\n", num);
}