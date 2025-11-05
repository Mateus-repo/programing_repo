#include <stdio.h>
#include <conio.h>

main(){
	int c, c1, c2, cc2, c3;
	printf(" 1-Sopas\n 2-Segundo\n 3-Sobremesas\n 4-Sair\n\n");
	scanf("%d", &c);
	if(c<1||c1>4){
		printf("\n Erro, nao existe essa opcao, tente de novo.\n\n");
	}else{
		if(c==1){
			printf("\n 1-Caldo Verde\n 2-Canja de Galinha\n 3-Sopa da Pedra\n\n");
			scanf("%d", &c1);
			if(c1==1){
				printf("\n 1.35 euros\n\n");
			}else{
				if(c1==2){
					printf("\n 1.55 euros\n\n");
				}else{
					if(c1==3){
						printf("\n 2.15 euros\n\n");
					}else{
						if(c1<1||c1>4){
							printf("\n Erro, nao existe essa opcao, tente de novo.\n\n");
						}
					}
				}
			}
		}else{
			if(c==2){
				printf("\n 1-Picanha\n 2-Sushi\n 3-Frango Frito\n\n");
				scanf("%d", &c2);
				if(c2<1||3<c2){
					printf("\n Erro, nao existe essa opcao, tente de novo.\n\n");
				}else{
					if(c2==1){
						printf("\n 1-Mal Passada\n 2-Media\n 3-Bem Passada\n\n");
						scanf("%d", &cc2);
						if(cc2<1||3<cc2){
							printf("\n Erro, nao existe essa opcao, tente de novo.\n\n");
						}else{
							if(cc2==1){
								printf("\n 16.55 euros\n\n");
							}else{
								if(cc2==2){
									printf("\n 16.65 euros\n\n");
								}else{
									printf("\n 16.70 euros\n\n");
								}
							}
						}
					}else{
						if(c2==2){
							printf("\n 23.55 euros\n\n");
						}else{
							printf("\n 14.25 euros\n\n");
						}
					}
				}	
			}else{
				if(c==3){
					printf("\n 1-Arroz Doce\n 2-Crespes Simples\n 3-Crespes com Chocolate\n\n");
					scanf("%d", &c3);
					if(c3<1||c3>3){
						printf("\n Erro, nao existe essa opcao, tente de novo.\n\n");
					}else{
						if(c3==1){
							printf("\n 1.60 euros\n\n");
						}else{
							if(c3==2){
								printf("\n 1.50 euros\n\n");
							}else{
								printf("\n 2.00 euros\n\n");
							}
						}
					}
				}else{
					if(c==4){
						printf("\n Pressione Enter para sair\n\n");
					}
				}
			}
		}
	}
	if(c<1||c>4){
		
	}else{
		if(c==1){
			if(c1==1){
				printf(" Caldo Verde.");
			}else{
				if(c1==2){
					printf(" Canja de Galinha.");
				}else{
					printf(" Sopa da Pedra.");
				}
			}
		}
	}
	if(c<1||c>4){
		
	}else{
		if(c2<1||c2>3){
			printf("");
		}else{
			if(c==2){
				if(c2==1){
					if(cc2<1||cc2>3){
						printf("");
					}else{
						if(cc2==1){
							printf(" Picanha Mal Passada.");
						}else{
							if(cc2==2){
								printf(" Picanha Media.");
							}else{
								printf(" Picanha Bem Passada.");
							}
						}
					}
				}else{
					if(c2==2){
						printf("\n Sushi.");
					}else{
						printf("\n Frango Frito.");
					}
				}
			}
		}
	}
	if(c<1||c>4){
		
	}else{
		if(c3<1||c3>3){
			printf("");
		}else{
			if(c==3){
				if(c3==1){
					printf(" Arroz Doce.");
				}else{
					if(c3==2){
						printf(" Crepes Simples.");
					}else{
						printf(" Crepes com Chocolate. ");
					}
				}
			}
		}
	}
					
}
