#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct Pessoa
{
  int codigo;
  char nome[40];
  char nif[20];
  char numero_bilhete[20];
  int telefone;
  int tipo_de_cliente;
};

struct Conta
{
  int numero_conta;
  double saldo;
  int codigo_cliente;
  int estado;
  int tipo_de_conta;

};

struct Pessoa clientes[1000];
struct Conta contas[1000];
int codigo_do_cliente = 0, num_de_clientes = 0, num_de_contas = 0;
char nome_do_arquivo[] = "backup_isaf.txt";


void criarAquivo() {
  FILE *arquivo;

  arquivo = fopen(nome_do_arquivo, "w");
  fclose(arquivo);
}

bool cadastro_de_cliente(struct Pessoa p) {
    int tamanho = num_de_clientes;
    p.codigo = ++codigo_do_cliente;
    clientes[tamanho] = p;
    num_de_clientes++;

    return true;
}

bool abertura_de_conta(struct Pessoa p, int tipo_de_conta) {
    int tamanho = num_de_contas;

    struct Conta conta;
    conta.codigo_cliente = p.codigo;
    conta.estado = 0;
    conta.saldo = 0;
    conta.tipo_de_conta = tipo_de_conta;
    conta.numero_conta = 5000 + p.codigo;

    contas[p.codigo - 1] = conta;
    num_de_contas++;

    printf("Conta numero: %d\n\n", conta.numero_conta);

    return true;
}

bool depositar_dinheiro(int num_da_conta, float valor) {

  if(valor <= 0) {
  	printf("O valor deve ser maior de 0");
    return false;
  }

  int i = 0;
  bool conta_foi_encontrada = false;
  int num_contas = num_de_clientes;

  for(i = 0; i < num_contas; i++)
  {
    if(contas[i].numero_conta == num_da_conta) {
			if(contas[i].estado == 1) {
      contas[i].saldo += valor;
      conta_foi_encontrada = true;
			} else {
				printf("Nao pode completar a operacao, sua conta esta desativada");
				return false;
			}
    }
  }

  if(conta_foi_encontrada) {
    printf("Deposito realizado com sucesso\n");
  } else {
    printf("Conta nao foi encontrada\n");
  }
  return true;
}

bool levantar_dinheiro(int num_da_conta, float valor) {

   if(valor <= 0) {
    printf("Valor deve ser positivo\n");
    return false;
  }

  int i = 0;
  bool conta_foi_encontrada = false;
  int num_contas = num_de_clientes;

  for(i = 0; i < num_contas; i++)
  {
    if(contas[i].numero_conta == num_da_conta) {
			if(contas[i].estado == 1) {
				if(contas[i].saldo >= valor) {
				contas[i].saldo -= valor;
				conta_foi_encontrada = true;
				} else {
					printf("Saldo insuficiente\n");
					return false;
				}
			} else {
				printf("Nao pode completar a operacao, sua conta esta desativada");
				return 0;
			}
    }
  }

  if(conta_foi_encontrada) {
    printf("Levantamento realizado com sucesso\n");
  } else {
    printf("Conta nao foi encontrada\n");
  }
  return true;
}

float consultar_saldo(int num_da_conta) {

  int i = 0;
  float saldo = 0;
  bool conta_foi_encontrada = false;
  int num_contas = num_de_clientes;

  for(i = 0; i < num_contas; i++)
  {
    if(contas[i].numero_conta == num_da_conta) {
			if(contas[i].estado == 1) {
      saldo = contas[i].saldo;
      conta_foi_encontrada = true;
			} else {
				printf("Nao pode completar a operacao, sua conta esta desativada");
				return 0;
			}
    }
  }

  if(!conta_foi_encontrada) {
    printf("Conta nao foi encontrada\n");
  }

  return saldo;
}

bool transferir_dinheiro(int num_da_conta, int num_da_conta_receber, float valor) {

  if(valor <= 0) {
    printf("Valor deve ser positivo\n");
    return false;
  }

  int i = 0, posicao_num_da_conta, posicao_num_da_conta_receber;
  bool conta_foi_encontrada = false, conta_receber_foi_encontrada = false;
  int num_contas = num_de_clientes;

  for(i = 0; i < num_contas; i++)
  {
    if(contas[i].numero_conta == num_da_conta) {
			if(contas[i].estado == 1) {
      posicao_num_da_conta = i;
      conta_foi_encontrada = true;
			} else {
				printf("Nao pode completar a operacao,conta de origem esta desativada");
				return false;
			}
    }

    if(contas[i].numero_conta == num_da_conta_receber) {
			if(contas[i].estado == 1) {
      posicao_num_da_conta_receber = i;
      conta_receber_foi_encontrada = true;
			} else {
				printf("Nao pode completar a operacao, conta de destino esta desativada");
				return false;
			}
    }
  }

  if(!conta_foi_encontrada) {
    printf("Conta nao foi encontrada\n");
    return false;
  }

  if(!conta_receber_foi_encontrada) {
    printf("Conta a receber nao foi encontrada\n");
    return false;
  }

  if(contas[posicao_num_da_conta].saldo >= valor) {
      contas[posicao_num_da_conta].saldo -= valor;
      contas[posicao_num_da_conta_receber].saldo += valor;
    printf("Transferencia realizada com sucesso\n");
  } else {
    printf("Saldo insuficiente\n");
  }
  return true;
}

bool actualizar_dados(struct Pessoa p, int codigo_cliente) {

  int i = 0;
  bool cliente_foi_encontrado = false;
  int num_clientes = num_de_clientes;

  for(i = 0; i < num_clientes; i++)
  {
    if(clientes[i].codigo == codigo_cliente) {
      clientes[i] = p;
       cliente_foi_encontrado= true;
    }
  }

  if(cliente_foi_encontrado) {
    printf("Dados actualizados com sucesso\n");
  } else {
    printf("Conta nao foi encontrada\n");
  }
  return true;
}

void listar_clientes() {

  int i = 0;
  int num_clientes = num_de_clientes;

  for(i = 0; i < num_clientes; i++)
  {
    printf("Nome: %s\n", clientes[i].nome);
    printf("Codigo: %d\n", clientes[i].codigo);

    if(clientes[i].tipo_de_cliente == 0) {
    printf("Numero de BI: %s\n", clientes[i].numero_bilhete);
    printf("Tipo de cliente: particular\n");
    } else {
    printf("NIF: %s\n", clientes[i].nif);
    printf("Tipo de cliente: empresa\n");
    }
    printf("Telefone: %d\n", clientes[i].telefone);

		if(contas[i].numero_conta > 0 && contas[i].codigo_cliente == clientes[i].codigo) {
    	printf("Conta\n");
    	printf("Numero de conta: %d\n", contas[i].numero_conta);
    	//printf("Saldo: %.2lf\n", contas[i].saldo);
    	printf("Codigo do cliente: %d\n", contas[i].codigo_cliente);
			if(contas[i].estado == 0) {
				printf("Estado: Desativada\n");
			} else if(contas[i].estado == 1) {
				printf("Estado: Activa\n");
			}
			if(contas[i].tipo_de_conta == 0) {
				printf("Tipo de conta: particular\n");
			} else if(contas[i].tipo_de_conta == 1) {
				printf("Tipo de conta: empresarial\n");
			}
		} else {
			printf("Sem conta\n");
		}
		printf("\n-----------------------------------\n");

  }
}

void copia_de_seguranca() {
  FILE *arquivo1;
  int i = 0;
  arquivo1 = fopen(nome_do_arquivo, "w");
  for(i = 0; i < num_de_clientes; i++) {
    fprintf(arquivo1, "%d,%s,%d,%s,%s,%d", clientes[i].codigo, clientes[i].nome, clientes[i].tipo_de_cliente, clientes[i].nif, clientes[i].numero_bilhete, clientes[i].telefone);
		if(contas[i].numero_conta > 0 && contas[i].codigo_cliente == clientes[i].codigo) {
			fprintf(arquivo1, "|%d,%f,%d,%d,%d\n", contas[i].numero_conta, contas[i].saldo, contas[i].codigo_cliente, contas[i].estado, contas[i].tipo_de_conta);
		}else {
    fprintf(arquivo1, "\n");
		}
  }
  // fclose(arquivo1);
  // free(arquivo1);
}

void restaurar_copia_de_seguranca() {
  FILE *arquivo;
  char linha[1000];
  int lendo_contas = 0;
  int lendo_clientes = 1;
	char separador;
  num_de_clientes = 0;
  num_de_contas = 0;
  codigo_do_cliente = 0;
	int resultado;

	int codigo, tipo_de_cliente, telefone, numero_conta, codigo_cliente, estado, tipo_de_conta;
	char nome[40], nif[20], numero_bilhete[20];
	double saldo;

  arquivo = fopen(nome_do_arquivo, "r");

  if(arquivo == NULL) {
    criarAquivo();
  }

  arquivo = fopen(nome_do_arquivo, "r");

  while (fgets(linha, sizeof linha, arquivo) != NULL) {
		resultado = sscanf(linha, "%d,%39[^,],%d,%19[^,],%19[^,],%d|%d,%lf,%d,%d,%d",
			&codigo, nome,
			&tipo_de_cliente, nif,
			numero_bilhete, &telefone,
			&numero_conta, &saldo,
			&codigo_cliente, &estado,
			&tipo_de_conta);

		if (resultado == 11) {
			clientes[num_de_clientes].codigo = codigo;
			strcpy(clientes[num_de_clientes].nome, nome);
			clientes[num_de_clientes].tipo_de_cliente = tipo_de_cliente;
		 	strcpy(clientes[num_de_clientes].nif, nif);
			strcpy(clientes[num_de_clientes].numero_bilhete, numero_bilhete);
		 	clientes[num_de_clientes].telefone = telefone;

			contas[num_de_clientes].numero_conta = numero_conta;
			contas[num_de_clientes].saldo = saldo;
			contas[num_de_clientes].codigo_cliente = codigo_cliente;
			contas[num_de_clientes].estado = estado;
			contas[num_de_clientes].tipo_de_conta = tipo_de_conta;

			++num_de_clientes;
			++codigo_do_cliente;
		} else if(resultado == 6) {
			clientes[num_de_clientes].codigo = codigo;
			strcpy(clientes[num_de_clientes].nome, nome);
			clientes[num_de_clientes].tipo_de_cliente = tipo_de_cliente;
		 	strcpy(clientes[num_de_clientes].nif, nif);
			strcpy(clientes[num_de_clientes].numero_bilhete, numero_bilhete);
		 	clientes[num_de_clientes].telefone = telefone;
			++num_de_clientes;
			++codigo_do_cliente;
		}
  }
}

void cabecalho (){
	system("cls");
	printf("========================================================================================================\n");
	printf("                                         SISTEMA DE GESTAO BANCARIA / BAI                               \n");
	printf("========================================================================================================\n\n");

}
char cont [10];
void continuar (){
	printf("Digite qualquer tecla para continuar!\n:");
	scanf("%s", cont);
}


int main()
{
  restaurar_copia_de_seguranca();

  struct Pessoa cliente;
  struct Conta conta;
  int i =0, opcao = 0, opcao2, opc, opc2;
  int codigo, deseja_continuar, numero_de_conta, numero_de_conta_destino;
  float valor = 0;


  do{
  		cabecalho();
  	   printf("\t1-Cadastrar Cliente\n\t2-Listar Clientes\n\t3-Abertura de Conta\n\t4-Depositar dinheiro\n\t5-Levantar dinheiro\n\t6-Consultar Saldo\n\t7-Transferir Dinheiro\n\t8-Actualizar dados do Cliente\n\t9-Sair\n\n");
  	  printf("Selecione uma opcao\nEscolha:");
	  scanf("%d", &opcao);

  	switch(opcao) {
  		case 1:
  			cabecalho();
  			fflush(stdin);
  			printf("\n**************** CADASTRO DO CLIENTE *********************\n\n");
  			printf("Digite o nome: ");
  			scanf("%[^\n]",cliente.nome);
  			system("cls");
  			printf("Digite o tipo de cliente\n\t[0]- para particular\n\t[1]- para empresa\n");
  			scanf("%d", &cliente.tipo_de_cliente);
  			if(cliente.tipo_de_cliente == 0) {
                    system("cls");
  				printf("Digite o numero do BI: ");
  				scanf("%s", cliente.numero_bilhete);
          strcpy(cliente.nif, "0");
          system("cls");
			} else {
			    system("cls");
				printf("Digite o NIF: ");
        scanf("%s", cliente.nif);
        strcpy(cliente.numero_bilhete, "0");
        system("cls");
			}

			while(true){
				printf("Digite o numero de telefone: ");
			    scanf("%d", &cliente.telefone);
			    if(((cliente.telefone>910000000) && (cliente.telefone<959999999)) || ((cliente.telefone>990000000)&&(cliente.telefone<999999999))){
				break;
			}else{

				printf("Numero invalido!\n");
				system("cls");
			}
			}





			cadastro_de_cliente(cliente);
  			break;

  		case 2:
  		    cabecalho();
  		    printf("\n**************** LISTA DE CLIENTES *********************\n\n");
  			listar_clientes();
  			continuar ();
  			break;

  		case 3:

  			cabecalho();

  			printf("\n**************** ABERTURA DE CONTA *********************\n\n");

  			printf("\t[1]-Abrir Conta\n\t[2]-Activar/Desactivar Conta\n\t[3]-Voltar \n");
  			printf("Escolha \n:");
  			scanf("%d", &opc);

  			switch (opc){
  				case 1:
  				    cabecalho();

                    printf("\n**************** ABERTURA DE CONTA *********************\n\n");

  					system("cls");
  					while(true) {
			  		printf("\nDigite o codigo do cliente: ");
	  				scanf("%d", &codigo);

	  				if(codigo <= codigo_do_cliente) {
	  					if(clientes[codigo - 1].codigo == codigo){

	  						cliente = clientes[codigo - 1];
	  					abertura_de_conta(cliente, cliente.tipo_de_cliente);
	  					sleep(5);
	  					continuar();
					  	break;
						}
					}else{
                    sleep(5);
				  	printf("\nCliente nao foi encontrado");
				  	printf("\nDeseja tentar novamente?\nSim (1)\nNao (0)\n");
				  	scanf("%d", &deseja_continuar);
				  	if(deseja_continuar == 0) {
				  		break;
					}
				}
			}
  			break;
  				case 2:
  				    cabecalho();

                    printf("\n**************** ESTADO DA CONTA *********************\n\n");

                    while(true) {
                            printf("\nDigite o numero de conta: ");
                            scanf("%d", &numero_de_conta);

                            if(numero_de_conta > 5000 && numero_de_conta <= 5000 + num_de_clientes) {
                            if(contas[numero_de_conta - 5000 - 1].numero_conta == numero_de_conta){
                            if(contas[numero_de_conta - 5000 - 1].estado == 0){
                                printf("Deseja Activar a Conta?:\n\t[1]-Sim \n\t[2]-Nao\n:");
                                scanf("%d",&opc2);
                                switch (opc2){
                                case 1:
                                    contas[numero_de_conta - 5000 - 1].estado=1;
                                    Sleep(2);
                                    printf("Conta Activada com Sucesso!");
                                    continuar();
                                    break;
                                case 2:
                                    break;
                        }

                            }else{
                                printf("Deseja Desactivar a Conta?:\n\t[1]-Sim \n\t[2]-Nao\n:");
                                scanf("%d",&opc2);
                                switch (opc2){
                                case 1:
                                    contas[numero_de_conta - 5000 - 1].estado=0;
                                    Sleep(20);
                                    printf("Conta Desactivada com Sucesso!");
                                    continuar();
                                    break;
                                case 2:
                                break;

                                }
                            }
                            }

                            }

                        break;
                    }





  					break;
				case 3:
					break;
			  }


            break;
  		case 4:
  			cabecalho();

  			printf("\n**************** DEPOSITAR DINHEIRO  *********************\n\n");

  			while(true) {
			  	printf("\nDigite o numero de conta: ");
	  			scanf("%d", &numero_de_conta);

	  			if(numero_de_conta > 5000 && numero_de_conta <= 5000 + num_de_clientes) {
	  				if(contas[numero_de_conta - 5000 - 1].numero_conta == numero_de_conta){
	  				printf("\nDigite o valor: ");
	  				scanf("%f", &valor);
	  				if(valor > 0){
	  					depositar_dinheiro(numero_de_conta, valor);
	  					continuar();
						break;
					}else {
						printf("\nValor de ser  maior que 0");
						printf("\nDeseja tentar novamente?\nSim (1)\nNao (0)\n");
				  		scanf("%d", &deseja_continuar);
				  		if(deseja_continuar == 0) {
				  		break;
					}
					}
					}
				}else {
				  	printf("\nConta nao foi encontrada");
				  	printf("\nDeseja tentar novamente?\nSim (1)\nNao (0)\n");
				  	scanf("%d", &deseja_continuar);
				  	if(deseja_continuar == 0) {
				  		break;
					}
				}
			}
			break;

		case 5:
			cabecalho();

  			printf("\n**************** LEVANTAR DINHEIRO *********************\n\n");

			while(true) {
			  	printf("\nDigite o numero de conta: ");
	  			scanf("%d", &numero_de_conta);

	  			if(numero_de_conta > 5000 && numero_de_conta <= 5000 + num_de_clientes) {
	  				if(contas[numero_de_conta - 5000 - 1].numero_conta == numero_de_conta){
	  				printf("\nDigite o valor: ");
	  				scanf("%f", &valor);
	  				if(valor > 0 && contas[numero_de_conta - 5000 - 1].saldo - valor >= 0){
	  					levantar_dinheiro(numero_de_conta, valor);
	  					continuar();
						break;
					}else {
						printf("\nValor de ser  maior que 0, ou o saldo e insuficiente");
						printf("\nDeseja tentar novamente?\nSim (1)\nNao (0)\n");
				  		scanf("%d", &deseja_continuar);
				  		if(deseja_continuar == 0) {
				  		break;
					}
					}
					}
				}else {
				  	printf("\nConta nao foi encontrada");
				  	printf("\nDeseja tentar novamente?\nSim (1)\nNao (0)\n");
				  	scanf("%d", &deseja_continuar);
				  	if(deseja_continuar == 0) {
				  		break;
					}
				}
			}
			break;

		case 6:
			cabecalho();

  			printf("\n**************** CONSULTAR SALDO *********************\n\n");

  			while(true) {
			  	printf("\nDigite o numero de conta: ");
	  			scanf("%d", &numero_de_conta);

	  			if(numero_de_conta > 5000 && numero_de_conta <= 5000 + num_de_clientes) {
	  				if(contas[numero_de_conta - 5000 - 1].numero_conta == numero_de_conta){
	  					printf("\nSaldo: %.2f", consultar_saldo(numero_de_conta));
	  					printf("\nCliente: %s\n", clientes[numero_de_conta - 5000 - 1].nome);
	  					continuar();
	  					break;
					}else {
						printf("\nDeseja tentar novamente?\nSim (1)\nNao (0)\n");
				  		scanf("%d", &deseja_continuar);
				  		if(deseja_continuar == 0) {
				  		break;
					}
					}
				}else {
				  	printf("\nConta nao foi encontrada");
				  	printf("\nDeseja tentar novamente?\nSim (1)\nNao (0)\n");
				  	scanf("%d", &deseja_continuar);
				  	if(deseja_continuar == 0) {
				  		break;
					}
				}
			}
			break;

		case 7:
			cabecalho();

  			printf("\n**************** TRANSFERIR DINHEIRO *********************\n\n");

  			while(true) {
			  	printf("\nDigite o numero de conta: ");
	  			scanf("%d", &numero_de_conta);



	  			if(numero_de_conta > 5000 && numero_de_conta <= 5000 + num_de_clientes) {
	  				if(contas[numero_de_conta - 5000 - 1].numero_conta != numero_de_conta) {
						printf("\nConta nao foi encontrada");
						printf("\nDeseja tentar novamente?\nSim (1)\nNao (0)\n");
				  		scanf("%d", &deseja_continuar);
				  		if(deseja_continuar == 0) {
				  		break;
						}
					}
				}else {
				  	printf("\nConta nao foi encontrada");
				  	printf("\nDeseja tentar novamente?\nSim (1)\nNao (0)\n");
				  	scanf("%d", &deseja_continuar);
				  	if(deseja_continuar == 0) {
				  		break;
					}
				}

				printf("\nDigite o numero de conta a receber: ");
	  			scanf("%d", &numero_de_conta_destino);
				if(numero_de_conta_destino > 5000 && numero_de_conta_destino <= 5000 + numero_de_conta_destino) {
	  				if(contas[numero_de_conta_destino - 5000 - 1].numero_conta != numero_de_conta_destino) {
						printf("\nConta nao foi encontrada");
						printf("\nDeseja tentar novamente?\nSim (1)\nNao (0)\n");
				  		scanf("%d", &deseja_continuar);
				  		if(deseja_continuar == 0) {
				  		break;
						}
					}
				}else {
				  	printf("\nConta nao foi encontrada");
				  	printf("\nDeseja tentar novamente?\nSim (1)\nNao (0)\n");
				  	scanf("%d", &deseja_continuar);
				  	if(deseja_continuar == 0) {
				  		break;
					}
				}

				printf("\nDigite o valor: ");
	  			scanf("%f", &valor);
				if(contas[numero_de_conta - 5000 - 1].saldo >= valor) {
					transferir_dinheiro(numero_de_conta, numero_de_conta_destino, valor);
					continuar();
					break;
				}else {
					printf("\nSaldo insuficiente");
					printf("\nDeseja tentar novamente?\nSim (1)\nNao (0)\n");
			  		scanf("%d", &deseja_continuar);
			  		if(deseja_continuar == 0) {
			  		break;
			  		}
				}
			}
			break;

		case 8:
			cabecalho();

  			printf("\n**************** ACTUALIZACAO DE DADOS *********************\n\n");

			while(true) {
			  	printf("\nDigite o codigo do cliente: ");
	  			scanf("%d", &codigo);

	  			if(codigo <= codigo_do_cliente) {
	  				if(clientes[codigo - 1].codigo == codigo){
	  					cliente = clientes[codigo - 1];
	  					printf("\nSelecione uma opcao\n");
	  					printf("\t1-Actualizar o nome\n\t2-Actualizar o contacto\n\t3-Actualizar BI/NIF\n\t4-Actualizar tudo\n\t\n");
	  					scanf("%d", &opcao2);
	  					switch(opcao2) {
	  						case 1:
	  							printf("Digite o nome: ");
  								scanf("%s", cliente.nome);
  								break;
  							case 2:
  								printf("Digite o numero de telefone: ");
  								scanf("%s", cliente.telefone);
  								break;
  							case 3:
  								if(cliente.tipo_de_cliente == 0) {
  									printf("Digite o numero de BI: ");
  									scanf("%s", cliente.numero_bilhete);
								  } else {
								  	printf("Digite o NIF: ");
  									scanf("%s", cliente.nif);
								  }
  								break;
  							case 4:
  								printf("Digite o nome: ");
  								scanf("%s", cliente.nome);

  								printf("Digite o numero de telefone: ");
  								scanf("%s", cliente.telefone);

  								if(cliente.tipo_de_cliente == 0) {
  									printf("Digite o numero de BI: ");
  									scanf("%s", cliente.numero_bilhete);
								} else {
								  	printf("Digite o NIF: ");
  									scanf("%s", cliente.nif);
								}
								break;
						  }
					  	actualizar_dados(cliente, codigo);
					  break;
					}
				}else {
				  	printf("\nCliente nao foi encontrado");
				  	printf("\nDeseja tentar novamente?\nSim (1)\nNao (0)\n");
				  	scanf("%d", &deseja_continuar);
				  	if(deseja_continuar == 0) {
				  		break;
					}
				}
			}
			break;
    case 9:
      copia_de_seguranca();
      break;
	  }
  }while (opcao != 9);
  return 0;
}
