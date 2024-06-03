#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>

#define MAX_NAME_LENGTH 100
#define FILE_NAME "codigo_fonte/projeto2.csv"
#define TEMP_FILENAME "codigo_fonte/temp.csv"
#define FILE_READ_PATTERN "%[^;];%[^;];%d;%d;%d;%d;%d;%d\n"
#define FILE_WRITE_PATTERN "%s;%s;%d;%d;%d;%d;%d;%d\n"

// Defini��o da estrutura de um jogador da NBA
typedef struct {
    char name[MAX_NAME_LENGTH];
    char team[MAX_NAME_LENGTH];
    int points;
    int assists;
    int rebounds;
    int steals;
    int blocks;
    int GP;
} jogador;

int menu();
void exibirJogadores();
void excluirJogador(const char *nome);
void alterarJogador(const char *name); // Declara��o da fun��o

void main() {
    setlocale(LC_ALL, "Portuguese");
    
    int Opcao, indiceEnter;
    char jogador[100];
    
    do {
        Opcao = menu();
    
        switch(Opcao)
        {
            case 1:
                printf("****Exibir todos os jogadores****\n\n");
                exibirJogadores();
                printf("Digite algo para voltar ao menu\n\n");
                getche();
                system("cls");
            break;
            
            case 2:
                printf("****Incluir um jogador****\n\n");
            break;
            
            case 3:
                printf("****Alterar um jogador****\n\n");
                printf("Digite o nome do jogador a ser alterado: ");
                fflush(stdin);
                fgets(jogador, sizeof(jogador), stdin);
                indiceEnter = strcspn(jogador, "\n");
                jogador[indiceEnter] = '\0';
                alterarJogador(jogador);
                printf("Digite algo para voltar ao menu\n\n");
                getche();
                system("cls");
            break;
            
            case 4:
                exibirJogadores();
                printf("\nQual jogador voc� deseja excluir: ");
                //String com o nome do jogador
                fflush(stdin);
                fgets(jogador, sizeof(jogador), stdin);
                
                indiceEnter = strcspn(jogador, "\n");
                
                jogador[indiceEnter] = '\0';
                
                excluirJogador(jogador);
                sleep(3);
                system("cls");
            break;
            
            case 5:
                Opcao = 5;
            break;
            
            default:
                printf("Op��o inv�lida!\n");
                sleep(2);
                system("cls");
        }
    } while (Opcao!=5);
}

int menu(){
    int Opcao;
    
    printf("****Menu de op��es****\n\n");
    printf("[1] Visualizar dados\n");
    printf("[2] Incluir dados\n");
    printf("[3] Alterar dados\n");
    printf("[4] Excluir dados\n");
    printf("[5] Sair\n");
    printf("\nSelecione a a��o desejada: ");
    scanf("%d", &Opcao);
    system("cls");
    return Opcao;
}

// Fun��o para imprimir todos os jogadores do arquivo CSV
void exibirJogadores() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    jogador player;
    int count = 1;
    printf(" Todos os jogadores:\n");
    printf("-------------------------------\n");
    while (fscanf(file, FILE_READ_PATTERN, player.team, player.name, &player.points, &player.assists, &player.rebounds, &player.steals, &player.blocks, &player.GP) != EOF) {
        printf("Jogador %d:\n", count);
        printf("  Nome: %s\n", player.name);
        printf("  Time: %s\n", player.team);
        printf("  Estatisticas:\n");
        printf("  Pontos: %d\n", player.points);
        printf("  Assistencias: %d\n", player.assists);
        printf("  Rebotes: %d\n", player.rebounds);
        printf("  Roubos: %d\n", player.steals);
        printf("  Tocos: %d\n", player.blocks);
        printf("  Partidas Jogadas: %d\n", player.GP);
        printf("\n");
        count++;
    }

    fclose(file);
}

// Fun��o para excluir um jogador
void excluirJogador(const char *name){
    
    //Abre um arquivo csv tempor�rio
    FILE *tempFile = fopen(TEMP_FILENAME, "w");
    //Caso a abertura falhar, exibe essa mensagem de erro
    if (tempFile == NULL) {
        printf("Erro ao abrir o arquivo tempor�rio\n");
        exit(1);
    }
    //Abre o arquivo csv principal
    FILE *file = fopen(FILE_NAME, "r");
    //Caso a abertura falhar, exibe essa mensagem de erro
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    
    jogador player;
    
    int count = 0, founded = 0;
    
    //Ele realiza a leitura de cada jogador, onde caso for diferente do jogador informado na fun��o, ir� transcrever no arquivo csv tempor�rio
    while ( fscanf(file,
         FILE_READ_PATTERN, 
         player.team,
         player.name,  
         &player.points, 
         &player.assists, 
         &player.rebounds, 
         &player.steals, 
         &player.blocks, 
         &player.GP) != EOF)
    {        
        if (strcmp(player.name, name) != 0) 
        {          
            fprintf(tempFile, 
                FILE_WRITE_PATTERN, 
                player.team, 
                player.name, 
                player.points, 
                player.assists, 
                player.rebounds, 
                player.steals, 
                player.blocks, 
                player.GP);
        }
        else
            founded = 1;
    }
    
    //Fecha os arquivos csv
    fclose(file);
    fclose(tempFile);
    
    if(!founded)
    {
        remove(TEMP_FILENAME);
        printf("N�o existe o jogador %s", name);
        return;
    }
    
    //Remove o arquivo csv principal
    remove(FILE_NAME);
    //Renomeia o arquivo csv tempor�rio com o nome do antigo principal
    rename(TEMP_FILENAME, FILE_NAME);
    
    
    printf("\nJogador exclu�do com sucesso!");
}

// Fun��o para alterar um jogador
void alterarJogador(const char *name) {
    FILE *tempFile = fopen(TEMP_FILENAME, "w");
    if (tempFile == NULL) {
        printf("Erro ao abrir o arquivo tempor�rio\n");
        exit(1);
    }

    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    jogador player;
    int found = 0;

    while (fscanf(file, FILE_READ_PATTERN, player.team, player.name, &player.points, &player.assists, &player.rebounds, &player.steals, &player.blocks, &player.GP) != EOF) {
        if (strcmp(player.name, name) == 0) {
            found = 1;
            int option;
            printf("Jogador encontrado. Escolha o campo a ser alterado:\n");
            printf("1. Time\n");
            printf("2. Pontos\n");
            printf("3. Assist�ncias\n");
            printf("4. Rebotes\n");
            printf("5. Roubos\n");
            printf("6. Tocos\n");
            printf("7. Partidas Jogadas\n");
            printf("Op��o: ");
            scanf("%d", &option);
            getchar(); // Limpar o buffer do newline

            switch (option) {
                case 1:
                    printf("Digite o novo time: ");
                    fgets(player.team, sizeof(player.team), stdin);
                    player.team[strcspn(player.team, "\n")] = '\0';
                    break;
                case 2:
                    printf("Digite os novos pontos: ");
                    scanf("%d", &player.points);
                    break;
                case 3:
                    printf("Digite as novas assist�ncias: ");
                    scanf("%d", &player.assists);
                    break;
                case 4:
                    printf("Digite os novos rebotes: ");
                    scanf("%d", &player.rebounds);
                    break;
                case 5:
                    printf("Digite os novos roubos: ");
                    scanf("%d", &player.steals);
                    break;
                case 6:
                    printf("Digite os novos tocos: ");
                    scanf("%d", &player.blocks);
                    break;
                case 7:
                    printf("Digite as novas partidas jogadas: ");
                    scanf("%d", &player.GP);
                    break;
                default:
                    printf("Op��o inv�lida.\n");
                    break;
            }
        }
        fprintf(tempFile, FILE_WRITE_PATTERN, player.team, player.name, player.points, player.assists, player.rebounds, player.steals, player.blocks, player.GP);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        remove(TEMP_FILENAME);
        printf("N�o existe o jogador %s\n", name);
        return;
    }

    remove(FILE_NAME);
    rename(TEMP_FILENAME, FILE_NAME);

    printf("\nJogador alterado com sucesso!\n");
}
