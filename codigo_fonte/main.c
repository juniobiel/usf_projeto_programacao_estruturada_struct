#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int menu();
<<<<<<< Updated upstream

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
=======
void exibirJogadores();
void excluirJogador(const char *nome);
>>>>>>> Stashed changes

void main() {
	setlocale(LC_ALL, "Portuguese");
	
<<<<<<< Updated upstream
<<<<<<< Updated upstream
	int Opcao;
=======
	int Opcao, indiceEnter;
	char jogador_nome[100];
>>>>>>> Stashed changes
=======
	int Opcao, indiceEnter;
	char jogador_nome[100];
>>>>>>> Stashed changes
	
	do {
		Opcao = menu();
	
		switch(Opcao)
		{
			case 1:
<<<<<<< Updated upstream
				printf("****Dados do banco de dados****\n\n");
			break;
			
			case 2:
<<<<<<< Updated upstream
				printf("****Inclusão de dados****\n\n");
				printf("preciso incluir os dados de um jogador");
			
			break;
=======
=======
				printf("****Exibir todos os jogadores****\n\n");
				exibirJogadores();
				printf("Digite algo para voltar ao menu\n\n");
				getche();
				system("cls");
			break;
			
			case 2:
>>>>>>> Stashed changes
                          {            
	 printf("****Incluir um jogador****\n\n");

                jogador novo_jogador;

                printf("Digite o nome do jogador: ");
                	fflush(stdin);
                  scanf("%s", &novo_jogador.name);

                printf("Digite o time do jogador: ");
                	fflush(stdin);
                scanf("%s", &novo_jogador.team);

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

                fprintf(file, FILE_WRITE_PATTERN, novo_jogador.team, novo_jogador.name, novo_jogador.points, novo_jogador.assists, novo_jogador.rebounds, novo_jogador.steals, novo_jogador.blocks, novo_jogador.GP);
                fclose(file);

                printf("Jogador incluído com sucesso!\n");
                printf("Digite algo para voltar ao menu\n\n");
                getche();
                system("cls");
<<<<<<< Updated upstream
                }
                break;
            
=======
                  break;
                }
                
>>>>>>> Stashed changes
             
                 
                     

				
				
		
<<<<<<< Updated upstream
>>>>>>> Stashed changes
			
			case 3:
				printf("****Alteração de dados****\n\n");
			break;
			
			case 4:
<<<<<<< Updated upstream
				printf("****Exclusão de dados****\n\n");
=======
=======
			
			case 3:
				printf("****Alterar um jogador****\n\n");
			break;
			
			case 4:
>>>>>>> Stashed changes
				exibirJogadores();
				printf("\nQual jogador você deseja excluir: ");
				//String com o nome do jogador
				fflush(stdin);
				fgets(jogador_nome, sizeof(jogador_nome), stdin);
				
				indiceEnter = strcspn(jogador_nome, "\n");
				
				jogador_nome[indiceEnter] = '\0';
				
				excluirJogador(jogador_nome);
				sleep(3);
				system("cls");
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
			break;
			
			case 5:
				Opcao = 5;
			break;
			
			default:
				printf("Opção inválida!\n");
<<<<<<< Updated upstream
				sleep(3);
=======
				sleep(2);
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======
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

//Função para excluir um jogador
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
	//Renovameia o arquivo csv temporário com o nome do antigo principal
	rename(TEMP_FILENAME, FILE_NAME);
	
	
	printf("\nJogador excluído com sucesso!");
>>>>>>> Stashed changes
}
