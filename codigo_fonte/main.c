#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int menu();

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void main() {
	setlocale(LC_ALL, "Portuguese");
	
<<<<<<< Updated upstream
	int Opcao;
=======
	int Opcao, indiceEnter;
	char jogador_nome[100];
>>>>>>> Stashed changes
	
	do {
		Opcao = menu();
	
		switch(Opcao)
		{
			case 1:
				printf("****Dados do banco de dados****\n\n");
			break;
			
			case 2:
<<<<<<< Updated upstream
				printf("****Inclusão de dados****\n\n");
				printf("preciso incluir os dados de um jogador");
			
			break;
=======
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
                }
                break;
            
             
                 
                     

				
				
		
>>>>>>> Stashed changes
			
			case 3:
				printf("****Alteração de dados****\n\n");
			break;
			
			case 4:
<<<<<<< Updated upstream
				printf("****Exclusão de dados****\n\n");
=======
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
>>>>>>> Stashed changes
			break;
			
			case 5:
				Opcao = 5;
			break;
			
			default:
				printf("Opção inválida!\n");
				sleep(3);
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
