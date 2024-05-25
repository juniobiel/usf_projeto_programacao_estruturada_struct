#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int menu();

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void main() {
	setlocale(LC_ALL, "Portuguese");
	
	int Opcao;
	
	do {
		Opcao = menu();
	
		switch(Opcao)
		{
			case 1:
				printf("****Dados do banco de dados****\n\n");
			break;
			
			case 2:
				printf("****Inclusão de dados****\n\n");
				printf("preciso incluir os dados de um jogador");
			
			break;
			
			case 3:
				printf("****Alteração de dados****\n\n");
			break;
			
			case 4:
				printf("****Exclusão de dados****\n\n");
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
