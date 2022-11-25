/* ETE Ginásio Pernambucano
   Desenvolvimento e Aplicação Desktop
   Professor: Emmanuel Barreto
   Alunos: Pollyane America
           Diego Melo */

 
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


typedef struct{
	
	int id;
	char nome[30];
	int idade;
	char genero[3];
	int g;
	float salario[10];
	char cargo[15];
	int m;
	char contato[15];
		
} REGISTRO;




FILE *pRegistro;


REGISTRO cadastro_aux, cadastro_nulo;


void linha(){
	
	int i;
	
	for(i=1; i <= 120; i++){
		
		printf("_");
	}
	printf("\n");
} 



void cabecalho(){
	
	system("cls");
	
	printf("CADASTRO DE FUNCIONÁRIOS - YES PERFUMES\n");
	
	linha();
}


void abre_arquivo(){
	
	pRegistro = fopen("cadastro.dat", "r+b");
	
	if(pRegistro == NULL)
	{
		pRegistro = fopen("cadastro.dat", "w+b");
	}
}



//procedimento para inserir
void inserir(){
	
	int resp;
	
	do{
		cabecalho();
		
		printf("\n\nCADASTRAR NOVO FUNCIONARIO\n\n");
		
		printf("\nNúmero ID (até 5 dígitos): ");
		scanf("%d", &cadastro_aux.id);
		
		printf("\nNome e sobrenome (ex ''Pollyane America''): ");
		fflush(stdin);
		gets(cadastro_aux.nome);
		
		printf("\nIdade: ");
		scanf("%d", &cadastro_aux.idade);
		
		printf("\nGênero <1-Masc 2-Fem>: ");
		scanf("%d", &cadastro_aux.g);
		
		printf("\nSalario: ");
		fflush(stdin);
		gets(cadastro_aux.salario);
		
		printf("\nCargo:\n");
		printf("1.  Gerente\n");
		printf("2.  Sub-Gerente\n");
		printf("3.  Vendedora\n");
		printf("4.  Aprendiz\n");
		scanf("%d", &cadastro_aux.m);
		
		printf("\nTelefone para contato(ex: 81997655428): ");
		fflush(stdin);
		gets(cadastro_aux.contato);
		
		//if-else para escrever o gênero
		if(cadastro_aux.g == 1)
		{
			strcpy(cadastro_aux.genero, "Mas");
			
		} else if(cadastro_aux.g == 2)
		  {
		  	strcpy(cadastro_aux.genero, "Fem");
		  	
		  } else
		    {
		    	strcpy(cadastro_aux.genero, "XXX");
			}
		
		//switch para escrever o cargo
		switch(cadastro_aux.m){
			
			 case 1: strcpy(cadastro_aux.cargo, "Gerente"); break;
			 case 2: strcpy(cadastro_aux.cargo, "Sub-Gerente"); break;
		     case 3: strcpy(cadastro_aux.cargo, "Vendedora"); break;
			 case 4: strcpy(cadastro_aux.cargo, "Aprendiz"); break;
			default: strcpy(cadastro_aux.cargo, "XXXXX"); break;
			
		}
		
		//comandos de exibição de cadastro
		system("cls");
		
		cabecalho();
		
		printf("\n\n");

        linha();
  
        printf(" ID             NOME          IDADE      GENERO     SALARIO          CARGO          CONTATO\n");
  
        linha();
  
        printf("%3d    %-30s    %3d    %3s    %10s    %15s    %15s\n", cadastro_aux.id, cadastro_aux.nome, cadastro_aux.idade, cadastro_aux.genero, cadastro_aux.salario, cadastro_aux.cargo, cadastro_aux.contato);
  
        linha(); 
        
        printf("\n\nPessoa cadastrada com sucesso!\n\n");
        
        //comando para posicionar o leitor do arquivo
        fseek(pRegistro, 0, SEEK_END);
        
        //comando para gravar o cadastro no arquivo
        fwrite(&cadastro_aux, sizeof(REGISTRO), 1, pRegistro);
        
        //comando para testar a condição do/while
        printf("\nDeseja fazer novo cadastro <1-Sim 2-Não>?: ");
        scanf("%d", &resp);	
		
	} while( resp == 1);
}




//função para procurar um cadastro no arquivo
int procurar(int idP){
	
	int p = 0;
	
	//comando para botar o leitor no inicio do arquivo
	rewind(pRegistro);
	
	//comando para ler o primeiro cadastro do arquivo(o registro do arquivo é atribuido ao "cadastro_aux")
	fread(&cadastro_aux, sizeof(REGISTRO), 1, pRegistro);
	
	//while para retornar a posição do cadastro no arquivo
	while(feof(pRegistro) == 0){
		
		if(cadastro_aux.id == idP){
			
			return p;
			
		} else{
			
			fread(&cadastro_aux, sizeof(REGISTRO), 1, pRegistro);
			
			p++;
		}
	}
	
	return -1;
}




//procedimento para mostrar o registro escrito no arquivo, em forma de tabela
void mostrar(int pos){
	
	//comando para por o leitor do arquivo no ponto certo da leitura do cadastro selecionado
	fseek(pRegistro, pos*sizeof(REGISTRO), SEEK_SET);
	
	//comando para ler o cadastro do arquivo(o registro do arquivo é atribuido ao "cadastro_aux")
	fread(&cadastro_aux, sizeof(REGISTRO), 1, pRegistro);
	
	printf("\n\n");
	
	//comando para exibir o cadastro na tela
	linha();
  
     printf(" ID             NOME          IDADE      GENERO     SALARIO          CARGO          CONTATO\n");
  
    linha();
  
    printf("%3d    %-30s    %3d    %3s    %10s    %15s    %15s\n", cadastro_aux.id, cadastro_aux.nome, cadastro_aux.idade, cadastro_aux.genero, cadastro_aux.salario, cadastro_aux.cargo, cadastro_aux.contato);
  
    linha(); 
	
	
}




//procedimento para consultar cadastro no arquivo
void consultar(){
	
	int resp, ipCon, posicao;
	
	do{
		cabecalho();
		
		printf("\n\nCONSULTAR CADASTRO\n\n\n");
		
		printf("ID: ");
		scanf("%d", &ipCon);
		
		posicao = procurar(ipCon);
		
		if(posicao == -1){
			
			printf("\n\nCadastro não encontrado!\n\n");
			
		} else{
			
			mostrar(posicao);
			
		}
		
		printf("\n\nDeseja consultar outro cadastro <1-Sim 2-Não>?:  ");
		scanf("%d", &resp);
			
	}while(resp == 1);
}




//procedimento para remover um cadastro do arquivo
void remover(){
	
	int idRem, conf, resp, posicao, campo;
	
	cadastro_nulo.idade = 0;
	cadastro_nulo.id = 0;
	
	do{
		cabecalho();
		
		printf("\n\nREMOVER CADASTRO\n\n\n");
		
		printf("ID: ");
		scanf("%d", &idRem);
		
		posicao = procurar(idRem);
		
		if(posicao == -1){
			
			printf("\n\nCadastro não encontrado!\a");
			
		}else{
			
			mostrar(posicao);
			
			printf("\n\nDeseja remover o cadastro <1-Sim 2-Não>?: ");
			scanf("%d", &conf);
			
			if(conf == 1){
				
				fseek(pRegistro, posicao*sizeof(REGISTRO), SEEK_SET);
				
				fwrite(&cadastro_nulo, sizeof(REGISTRO), 1, pRegistro);
				
				printf("\n\nCadastro removido com sucesso!");
				
			} else{
				
				printf("\n\n\nRemoção cancelada!");
			}
		}
		
		printf("\n\n\nDeseja remover outro cadastro <1-Sim 2-Não>?: ");
		scanf("%d", &resp);
		
	}while(resp == 1);
}
	


	
	//procedimento para alterar os campos do cadastro
	void alterar(){
		
		int idAlt, conf, resp, posicao, campo;
		
		do{
			cabecalho();
			
			printf("\n\nALTERAR CADASTRO\n\n\n");
			
			printf("Digite o ID do cadastro: ");
			scanf("%d", &idAlt);
			
			posicao = procurar(idAlt);
			
			if(posicao == -1){
				
				printf("\nCadastro não encontrado!\a");
				
			}else{
				
				mostrar(posicao);
				
				printf("\n\nQual campo deseja alterar?\n");
				printf("1.ID\n");
				printf("2.Nome\n");
				printf("3.Idade\n");
				printf("4.Gênero\n");
				printf("5.Salario\n");
				printf("6.Cargo\n");
				printf("7.Contato\n: ");
				
				scanf("%d", &campo);
				
				switch(campo){
					
					case 1:
					       printf("\n\nDigite o novo ID (até 5 dígitos): ");
						   scanf("%d", &cadastro_aux.id);
						   break;
						   
					case 2:
					       printf("\n\nDigite o novo nome e sobrenome (ex ''Pollyane America''): ");
						   fflush(stdin);
						   gets(cadastro_aux.nome);
						   break;
						   
					case 3:
						   printf("\n\nDigite a nova idade: ");
						   scanf("%d", &cadastro_aux.idade);
						   break;
						   
					case 4:
						   printf("\n\nEscolha o novo gênero <1-Mas 2-Fem>: ");
						   scanf("%d", &cadastro_aux.g);
						   
						   if(cadastro_aux.g == 1){
						   	
						   	     strcpy(cadastro_aux.genero, "Mas");
						   	     
						   } else if(cadastro_aux.g == 2){
						   	 
						   	     strcpy(cadastro_aux.genero, "Fem");
						   }
						   
						   break;
						   
					case 5:
						   printf("\n\nSalario: ");
						   fflush(stdin);
						   gets(cadastro_aux.salario);
						   break;
						   
					case 6:
						  printf("\n\nNovo cargo:\n");
						   printf("1.  Gerente\n");
	 	                   printf("2.  Sub-Gerente\n");
		                   printf("3.  Vendedora\n");
		                   printf("4.  Aprendiz\n");
		                   scanf("%d", &cadastro_aux.m);
		                   
		                   switch(cadastro_aux.m){
			
			                 case 1: strcpy(cadastro_aux.cargo, "Gerente"); break;
			                 case 2: strcpy(cadastro_aux.cargo, "Sub-Gerente"); break;
			                 case 3: strcpy(cadastro_aux.cargo, "Vendedora"); break;
			                 case 4: strcpy(cadastro_aux.cargo, "Aprendiz"); break;
			                 default: strcpy(cadastro_aux.cargo, "XXXXX"); break;		
	                     	} break;          
						   		
				}
	
			}
			
			printf("\n\nAlteração realizada com sucesso!\n");
			
			fseek(pRegistro, posicao*sizeof(REGISTRO), SEEK_SET);
			
			fwrite(&cadastro_aux, sizeof(REGISTRO), 1, pRegistro);
			
			mostrar(posicao);
			
			printf("\n\nDeseja alterar outro cadastro <1-Sim 2-Não>?: ");
			scanf("%d", &resp);
			
		}while(resp == 1);
		
	}
	
		
	
	//procedimento para listar todos os cadastros do arquivo
	void listagem(){
		
		cabecalho();
		
		printf("\n\nLISTAGEM GERAL\n\n\n");
		
		linha();
		
		printf(" ID             NOME          IDADE      GENERO     SALARIO          CARGO          CONTATO\n");
  
        linha();
        
        rewind(pRegistro);
        
        fread(&cadastro_aux, sizeof(REGISTRO), 1, pRegistro);
        
        while(feof(pRegistro) == 0){
        	
        	if(cadastro_aux.id != 0){
        		
        		printf("%3d    %-20s    %3d    %3s    %10s    %15s    %15s\n", cadastro_aux.id, cadastro_aux.nome, cadastro_aux.idade, cadastro_aux.genero, cadastro_aux.salario, cadastro_aux.cargo, cadastro_aux.contato);
			}
			
			fread(&cadastro_aux, sizeof(REGISTRO), 1, pRegistro);
		}
		
		linha();
		
		printf("Tecle enter para voltar ao Menu...");
		
		getche();		
		
	}

	



//módulo principal
main(){
	
	int op;
	
	//comando para escrever em português
    setlocale(LC_ALL, "Portuguese");
	
	abre_arquivo();
	
	do{
		cabecalho();
		
		printf("\n\nMENU\n\n\n");
		
		printf("    1- Cadastrar nova pessoa\n\n");
		printf("    2- Remover cadastro\n\n");
		printf("    3- Consultar cadastro\n\n");
		printf("    4- Alterar cadastro\n\n");
		printf("    5- Listagem geral\n\n");
		printf("    0- Sair\n\n");
		
		linha();
		
		printf("\nInforme a opção desejada: ");
		scanf("%d", &op);
		
		switch(op){
			
			case 1: inserir(); break;
			case 2: remover(); break;
			case 3: consultar(); break;
			case 4: alterar(); break;
			case 5: listagem(); break;
			case 0: fclose(pRegistro); break;
			default: printf("\n\nOpção inválida!"); break;
	
		}
		
	}while(op != 0);
	
}
