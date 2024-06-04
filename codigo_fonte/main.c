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

// Definição da estrutura de um jogador da NBA
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
void alterarJogador(const char *name); // Declaração da função

void main() {
    setlocale(LC_ALL, "Portuguese");
    
    int Opcao, indiceEnter;
    char playerName[100];
    
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

                jogador novo_jogador;

                printf("Digite o nome do jogador: ");
                fflush(stdin);
                fgets(novo_jogador.name, sizeof(novo_jogador.name), stdin);
                indiceEnter = strcspn(novo_jogador.name, "\n");
             	novo_jogador.name[indiceEnter] = '\0';
			

                printf("Digite o time do jogador: ");
                fflush(stdin);
                fgets(novo_jogador.team, sizeof(novo_jogador.team), stdin);
                indiceEnter = strcspn(novo_jogador.team, "\n");
                novo_jogador.team[indiceEnter] = '\0';

                printf("Digite os pontos do jogador: ");
                scanf("%d", &novo_jogador.points);

                printf("Digite as assistências do jogador: ");
                scanf("%d", &novo_jogador.assists);

                printf("Digite os rebotes do jogador: ");
                scanf("%d", &novo_jogador.rebounds);

                printf("Digite os roubos do jogador: ");
                scanf("%d", &novo_jogador.steals);

                printf("Digite os tocos do jogador: ");
                scanf("%d", &novo_jogador.blocks);

                printf("Digite as partidas jogadas pelo jogador: ");
                scanf("%d", &novo_jogador.GP);

                FILE *file = fopen(FILE_NAME, "a");
                
                if (file == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    exit(1);
                }

                fprintf(file, 
					FILE_WRITE_PATTERN, 
					novo_jogador.team, 
					novo_jogador.name, 
					novo_jogador.points, 
					novo_jogador.assists, 
					novo_jogador.rebounds, 
					novo_jogador.steals, 
					novo_jogador.blocks, 
					novo_jogador.GP);
					
                fclose(file);

                printf("Jogador incluído com sucesso!\n");
                printf("Digite algo para voltar ao menu\n\n");
                getche();
                system("cls");
            break;
            
            case 3:
            	
                printf("****Alterar um jogador****\n\n");
                exibirJogadores();
                printf("Digite o nome do jogador a ser alterado: ");
                fflush(stdin);
                fgets(playerName, sizeof(playerName), stdin);
                indiceEnter = strcspn(playerName, "\n");
                playerName[indiceEnter] = '\0';
                alterarJogador(playerName);
                printf("Digite algo para voltar ao menu\n\n");
                getche();
                system("cls");
            break;
            
            case 4:
                exibirJogadores();
                printf("\nQual jogador você deseja excluir: ");
                //String com o nome do jogador
                fflush(stdin);
                fgets(playerName, sizeof(playerName), stdin);
                
                indiceEnter = strcspn(playerName, "\n");
                
                playerName[indiceEnter] = '\0';
                
                excluirJogador(playerName);
                sleep(3);
                system("cls");
            break;
            
            case 5:
                Opcao = 5;
            break;
            
            default:
                printf("Opção inválida!\n");
                sleep(2);
                system("cls");
        }
    } while (Opcao!=5);
}

int menu(){
    int Opcao;
    
    printf("****Menu de opções****\n\n");
    printf("[1] Visualizar dados\n");
    printf("[2] Incluir dados\n");
    printf("[3] Alterar dados\n");
    printf("[4] Excluir dados\n");
    printf("[5] Sair\n");
    printf("\nSelecione a ação desejada: ");
    scanf("%d", &Opcao);
    system("cls");
    return Opcao;
}

// Função para imprimir todos os jogadores do arquivo CSV
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

// Função para excluir um jogador
void excluirJogador(const char *name){
    
    //Abre um arquivo csv temporário
    FILE *tempFile = fopen(TEMP_FILENAME, "w");
    //Caso a abertura falhar, exibe essa mensagem de erro
    if (tempFile == NULL) {
        printf("Erro ao abrir o arquivo temporário\n");
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
    
    //Ele realiza a leitura de cada jogador, onde caso for diferente do jogador informado na função, irá transcrever no arquivo csv temporário
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
        printf("Não existe o jogador %s", name);
        return;
    }
    
    //Remove o arquivo csv principal
    remove(FILE_NAME);
    //Renomeia o arquivo csv temporário com o nome do antigo principal
    rename(TEMP_FILENAME, FILE_NAME);
    
    
    printf("\nJogador excluído com sucesso!");
}

// Função para alterar um jogador
void alterarJogador(const char *name) {
    FILE *tempFile = fopen(TEMP_FILENAME, "w");
    if (tempFile == NULL) {
        printf("Erro ao abrir o arquivo temporário\n");
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
            printf("2. Nome\n");
            printf("3. Pontos\n");
            printf("4. Assistências\n");
            printf("5. Rebotes\n");
            printf("6. Roubos\n");
            printf("7. Tocos\n");
            printf("8. Partidas Jogadas\n");
            printf("Opção: ");
            scanf("%d", &option);
            getchar(); // Limpar o buffer do newline

            switch (option) {
                case 1:
                    printf("Digite o novo time: ");
                    fgets(player.team, sizeof(player.team), stdin);
                    player.team[strcspn(player.team, "\n")] = '\0';
                    break;
                case 2:
                    printf("Digite o novo nome: ");
                    fgets(player.name, sizeof(player.name), stdin);
                    player.name[strcspn(player.name, "\n")] = '\0';
                    break;
                case 3:
                    printf("Digite os novos pontos: ");
                    scanf("%d", &player.points);
                    break;
                case 4:
                    printf("Digite as novas assistências: ");
                    scanf("%d", &player.assists);
                    break;
                case 5:
                    printf("Digite os novos rebotes: ");
                    scanf("%d", &player.rebounds);
                    break;
                case 6:
                    printf("Digite os novos roubos: ");
                    scanf("%d", &player.steals);
                    break;
                case 7:
                    printf("Digite os novos tocos: ");
                    scanf("%d", &player.blocks);
                    break;
                case 8:
                    printf("Digite as novas partidas jogadas: ");
                    scanf("%d", &player.GP);
                    break;
                default:
                    printf("Opção inválida.\n");
                    break;
            }
        }
        fprintf(tempFile, FILE_WRITE_PATTERN, player.team, player.name, player.points, player.assists, player.rebounds, player.steals, player.blocks, player.GP);
    }

    fclose(file);
    fclose(tempFile);

    if (!found) {
        remove(TEMP_FILENAME);
        printf("Não existe o jogador %s\n", name);
        return;
    }

    remove(FILE_NAME);
    rename(TEMP_FILENAME, FILE_NAME);

    printf("\nJogador alterado com sucesso!\n");
}
