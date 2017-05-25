#include <stdlib.h>
#include <stdio.h>
#include <string.h>

 main (){
			
	/*Variaveis*/
	char nome[20],cidad[20],Novonome[20],Novacidad[20];
	int contaC,contato,NovacontaC,Novocontato,de,para,op,verif;
	float grana,debito,credito;
	FILE *file,*filetemp;
	

	
	/*As contas começam a ser criadas nesse padrão*/
	NovacontaC = 201700;
	
	/* ir para o case 9*/
    op=9;

	/*Inicio do loop*/
	while (op != 0){
		
	
	 /*Inicia o switch*/
	 switch(op)
	 {
	 	
	 	/*Case 1 - Cadastro de novos cliente e conta*/
	 	case 1:	
	    system("color 80");
	  	system("cls");	
	    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n");
     	printf("------------------------------------------------ KHALIFAS' BANK!---------------------------------------------------- \n");
	    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n\n "); 
	    printf("                                              CADASTRO DE CLIENTE                   \n\n");
	 	printf("                           Digite o nome do Cliente: \n");
	 	printf("                           ");
	 	scanf("%s",&Novonome);
	 	printf("                           Digite sua cidade: \n");
	 	printf("                           ");	 	
	 	scanf("%s",&Novacidad);
	 	printf("                           Digite seu numero: \n");
	 	printf("                           ");	 	
	 	scanf("%d",&Novocontato);
	 	
	 	
	 	/*Definindo qual arquivo ele abrirá e o fazer, nesse caso, read (ler)*/
	 	file = fopen("banco.txt","r");

	 	/*Vai ler o arquivo file até o final*/ 
	 	while( (fscanf(file,"%s %s %d %d %f ", &nome, &cidad,&contato,&contaC,&grana))!=EOF ){
	
	        /*verificará qual conta está disponivel para o cliente*/
		    if(NovacontaC == contaC){
	 	 	NovacontaC = NovacontaC + 1;
            }
		    
	    }
	    
	    /* Exibirá qual conta corrente foi Usada*/
	    printf("                           ");
		printf("Numero de sua conta corrente: %d", NovacontaC);
		
		/* Registrará o cliente no banco de dados -*/
		file = fopen("banco.txt","a");
	    fprintf(file,"\n%s %s %d %d %f", Novonome, Novacidad,Novocontato,NovacontaC," 0");
	    fclose(file); 
	    
	    getchar();
        getchar();
		op=9;   
	 	break;
	 	
		/*Case 2 -> Transferencia entre contas*/ 
		case 2: 
     	verif=0;
     	system("cls");	
     	system("color 80");
     	printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n");
     	printf("------------------------------------------------ KHALIFAS' BANK!---------------------------------------------------- \n");
	    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n\n"); 
		printf("                       Transferencia entre contas,  valor da transferencia: \n");
		printf("                       U$:");
		scanf("%f",&debito);
		printf("\n                    Transferencia entre contas, digite o numero da conta a debitar (ex: 2017XX): \n");
		printf("                      DE:");
	 	scanf("%d",&de);
	 	printf("\n                    Transferencia entre contas, digite o numero da conta a creditar (ex: 2017XX): \n");
		printf("                      PARA:");
	 	scanf("%d",&para);


	 	/*Definindo 2 banco de dados, 1 fixo e outro temporário. Necessario pois, é impossivel editar uma linha especifica TXT.*/
	 	file = fopen("banco.txt","r");
	 	filetemp = fopen("banco_temp.txt","w");
	 	while( (fscanf(file,"%s %s %d %d %f ", &nome, &cidad,&contato,&contaC,&grana))!=EOF ){
           
		   /* Verifica se a conta existe*/
           if (de==contaC)
            {  
				 /*Verifica se tem dinheiro na conta de quem está enviando, se sim, escreverá no db temp e será acrescentado +1
				 na variavel verif , senão, verif vai ser igual a 3*/
                 if (grana>=debito){	
         	            grana=grana-debito;
         	            fprintf(filetemp,"\n%s %s %d %d %f", nome, cidad,contato,contaC,grana);
         	            verif++;
                        }else{
                        verif=3; 
		       	        }
	        }else{          
				            /*Verifica se a conta que está recebendo existe, se existir, sera acrescentado +1 na var verif e
							sera escrito no db temp*/
				            if (para==contaC){
             	            grana=grana+debito;
         	                fprintf(filetemp,"\n%s %s %d %d %f", nome, cidad,contato,contaC,grana);
	        	            verif++;
		                    }else{

							/* Copiará as outras contas para o arquivo a db temp*/		   	
	        	            fprintf(filetemp,"\n%s %s %d %d %f", nome, cidad,contato,contaC,grana);
		                    }
    	         }
		
		} 
		
		/*Vai fechar o arquivo temporário*/
	    fclose(filetemp); 

	    /* Caso o verif for igual a 2 ou seja, ambas as contas existirem e tiver dinheiro na conta debitante, as alterações
		serão feitas no db temp serão transferidas para o banco de dados funcional*/
	    if (verif == 2){
	          file = fopen("banco.txt","w");
	          filetemp = fopen("banco_temp.txt","r");
	 	      while( (fscanf(filetemp,"%s %s %d %d %f ", &nome, &cidad,&contato,&contaC,&grana))!=EOF ){
	 	      fprintf(file,"\n%s %s %d %d %f", nome, cidad,contato,contaC,grana);
    	      }
    	      fclose(file); 
    	      fclose(filetemp);
              system("color 72");
		      printf("                      SITUACAO: Transferencia Realizade com Sucesso  ");
		      }else{
		   	          
					  /*Caso, o verif for maior ou igual à 3, a conta debitante está sem saldo*/
					  if (verif>=3){
		   	 	      system("color 76");
                      printf("                      SITUACAO: Saldo indisponivel  ");
		   	          }else{
			          system("color 74");
				      printf("                      SITUACAO: Uma das contas estao incorretas  ");	
		              }
		    }
        getchar();
        getchar();
		op=9;   
	    break;
	
	    /* Case 3 -> Debito*/   
	    case 3:
	    system("color 71");
		system("cls");
		printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n");
     	printf("------------------------------------------------ KHALIFAS' BANK!---------------------------------------------------- \n");
	    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n\n "); 
	    printf("                                                   DEBITO                   \n\n");
	    verif=0;
	    printf ("                        Digite o numero da conta: \n");
	    printf("                        ");
	    scanf("%d",&de);
	    printf("\n");
	    printf("                        Digite o valor do debito: \n");
	    printf("                        ");
	    scanf("%f",&debito);
	    file = fopen("banco.txt","r");
	 	filetemp = fopen("banco_temp.txt","w");
	 	while( (fscanf(file,"%s %s %d %d %f ", &nome, &cidad,&contato,&contaC,&grana))!=EOF ){
	 		
	 		if(de==contaC){
	 			grana=grana-debito;
	 			fprintf(filetemp,"\n%s %s %d %d %f", nome, cidad,contato,contaC,grana);
	 			verif++;
			    }else{
			    fprintf(filetemp,"\n%s %s %d %d %f", nome, cidad,contato,contaC,grana);	
			}
	 		
	 		
		}
	    fclose(file);
	    fclose(filetemp);
	   
	    if (verif==1){
	         file = fopen("banco.txt","w");
	         filetemp = fopen("banco_temp.txt","r");
	 	     while( (fscanf(filetemp,"%s %s %d %d %f ", &nome, &cidad,&contato,&contaC,&grana))!=EOF ){
	 	     fprintf(file,"\n%s %s %d %d %f", nome, cidad,contato,contaC,grana);
    	     }
    	
		     fclose(file);
	         fclose(filetemp);
	         system("color 72");
		     printf("\n                        ");
		     printf("Debitado");
	         }else{
	   	     system("color 74");
		     printf("\n                        ");
	   	     printf("Conta inexistente");
	   }
	   getchar();
	   getchar(); 
	   op=9;
	   break;
	    
	    
		/*Case 4 -> Creditar*/
	    case 4:
	    system("cls");
	    system("color 71");
		printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n");
     	printf("------------------------------------------------ KHALIFAS' BANK!---------------------------------------------------- \n");
	    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n\n "); 
	    printf("                                                   CREDITAR                   \n\n");
	    verif=0;
	    printf("\n                          Digite o numero da conta: ");
	    printf("\n                          ");
	    scanf("%d",&de);
	    printf("\n                          Digite o valor a creditar: ");
	    printf("\n                          ");
	    scanf("%f",&credito);
	    	
	    	
	    file=fopen("banco.txt","r");
	    filetemp=fopen("banco_temp.txt","w");
	    while( (fscanf(file,"%s %s %d %d %f ", &nome, &cidad,&contato,&contaC,&grana))!=EOF ){
	    		
	     if(de==contaC){
	    		grana=grana+credito;
	    		fprintf(filetemp,"\n%s %s %d %d %f", nome, cidad,contato,contaC,grana);
	    		verif++;
		        }else{	
		         fprintf(filetemp,"\n%s %s %d %d %f", nome, cidad,contato,contaC,grana);		
		 }
		}
		fclose(filetemp);
		fclose(file);
	    if (verif==1){
			 file = fopen("banco.txt","w");
	         filetemp = fopen("banco_temp.txt","r");
	         while( (fscanf(filetemp,"%s %s %d %d %f ", &nome, &cidad,&contato,&contaC,&grana))!=EOF ){
	     	 fprintf(file,"\n%s %s %d %d %f", nome, cidad,contato,contaC,grana);
    	     }
    	     fclose(file);
	         fclose(filetemp);
	         system("color 72");
		     printf("\n                          ");
	   	     printf("Creditado");
	         }else{
	         system("color 74");
	   	     printf("\n                          ");
	   	     printf("Conta inexistente");
	     }
		 getchar();
		 getchar();
		 op=9;
		 break;
		
		/* Case 5-> Ver saldo */
		case 5:
		system("cls");
		system("color 71");
		printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n");
     	printf("------------------------------------------------ KHALIFAS' BANK!---------------------------------------------------- \n");
	    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n\n "); 
	    printf("                                                   SALDO                   \n\n");
		verif=0;
		printf("                            Informe o numero da conta:");
		printf("\n                            ");
		scanf("%d",&de);
		file=fopen("banco.txt","r");
	    while( (fscanf(file,"%s %s %d %d %f ", &nome, &cidad,&contato,&contaC,&grana))!=EOF ){
	    		
	    if(de==contaC){	
				system("color 80");
				verif++;	
                printf("\n                                         -------------------------------\n");
                printf("                                          Nome: %s                 \n",nome);
                printf("                                         -------------------------------\n");
                printf("                                          Cidade: %s \n",cidad);
                printf("                                          Telefone: %d \n",contato);
                printf("                                          N da conta: %d \n",contaC);
                printf("                                          Saldo U$: %2.f \n",grana);
                printf("                                         -------------------------------\n");
				}else{
					
				}
		  }	
			
		  if(verif==1){
				}else{
				printf("\n                          ");	
				printf("Essa conta nao existe!");
				}	

		getchar();
		getchar();
		op=9;	
	    break;

	    /* Case 9 -> Menu principal */
	    case 9:
	    system("cls");	
		system("color 80");
	    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n");
     	printf("------------------------------------------------ KHALIFAS' BANK!---------------------------------------------------- \n");
	    printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ \n"); 
	    printf("\n                                   Bem vindo ao - KHALIFAS' BANK!, selecione uma opcao:                              \n\n "); 
                    
	    printf("             1 - Cadastrar Clientes                                                                                  \n");
	    printf("              2 - Transferencia entre contas                                                                          \n");
	    printf("              3 - Debitar                                                                                               ");
	    printf("              4 - Creditar                                                                                               ");
	    printf("             5 - Ver Saldo                                                                                           \n\n\n\n");
	    printf("              0 - Sair                                                                                                \n");
        printf("\n              ");
	    scanf("%d",&op);
	    break;
			
        default:  
        printf("\n Opcao Invalida");
        getchar();
        getchar();
		op=9;   
	 	break;
	}
	
  }
		
}
