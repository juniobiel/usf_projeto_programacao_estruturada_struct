#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define MAX_NAME_LENGTH 100
#define FILENAME "projeto2.csv"

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

void main() {
	setlocale(LC_ALL, "Portuguese");
	
	int Opcao;
	char jog[100];
	
	do {
		Opcao = menu();
	
		switch(Opcao)
		{
			case 1:
				printf("****Exibir todos os jogadores****\n\n");
			break;
			
			case 2:
				printf("****Incluir um jogador****\n\n");
			break;
			
			case 3:
				printf("****Alterar um jogador****\n\n");
			break;
			
			case 4:
				exibirJogadores();
				printf("\nQual jogador voc� deseja excluir: ");
				scanf("%99s", jog);
				excluirJogador(jog);
				printf("\nJogador exclu�do com sucesso!");
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
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    jogador player;
    int count = 1;
    printf(" Todos os jogadores:\n");
    printf("-------------------------------\n");
    while (fscanf(file, "%[^;];%[^;];%d;%d;%d;%d;%d;%d\n", player.team, player.name, &player.points, &player.assists, &player.rebounds, &player.steals, &player.blocks, &player.GP) != EOF) {
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

//Fun��o para excluir um jogador
void excluirJogador(const char *name){
	//Abre um arquivo csv tempor�rio
	FILE *tempFile = fopen("temp.csv", "w");
	//Caso a abertura falhar, exibe essa mensagem de erro
	if (tempFile == NULL) {
        printf("Erro ao abrir o arquivo tempor�rio\n");
        exit(1);
    }
    //Abre o arquivo csv principal
    FILE *file = fopen(FILENAME, "r");
	//Caso a abertura falhar, exibe essa mensagem de erro
	if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    
    jogador player;
    //Ele realiza a leitura de cada jogador, onde caso for diferente do jogador informado na fun��o, ir� transcrever no arquivo csv tempor�rio
    while (fscanf(file, "%[^;];%[^;],%d,%d,%d,%d,%d,%d\n", player.name, player.team, &player.points, &player.assists, &player.rebounds, &player.steals, &player.blocks, &player.GP) != EOF) {

        if (strcmp(player.name, name) != 0) {
			            
			fprintf(tempFile, "%[^;];%[^;],%d,%d,%d,%d,%d,%d\n", player.name, player.team, player.points, player.assists, player.rebounds, player.steals, player.blocks, player.GP);
		}
    }
    //Fecha os arquivos csv
    fclose(file);
    fclose(tempFile);
	//Remove o arquivo csv principal�
    remove(FILENAME);
	//Renovameia o arquivo csv tempor�rio com o nome do antigo principal
	rename("temp.csv", FILENAME);
}
