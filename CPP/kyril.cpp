#include <stdio.h>
#include <conio.h>
int m1,m2,m3,m4;
float b1,b2,b3,s1,s2,s3,d1,d2,d3,total, euro;
int i;
 
void menu1(){
    printf("1-Bebidas\n");
    printf("2-Sandes\n");
    printf("3-Doces\n");
    printf("4-Acabar\n");
    scanf("%d",&m1);
    fflush(stdin);
}
void menu2(){
	printf("1-Coca Cola 2?\n");
	printf("2-Cha 1?\n");
	printf("3-Cafe 1.5?\n");
	printf("4-Nao quero\n");
	scanf("%d",&m2);
	fflush(stdin);	
}              
void menu3(){
	printf("1-Sandes mistu 2.5?\n");
	printf("2-Sandes de queijo 2?\n");
	printf("3-Sandes com atum 1.5?\n");
	printf("4-Nao quero\n");
	scanf("%d",&m3);
	fflush(stdin);	
}
void menu4(){
	printf("1-Muce de chocolate 1?\n");
	printf("2-Baba de camelo 1.5?\n");
	printf("3-Bolo de bolacha 2?\n");
	printf("4-Nao quero\n");
	scanf("%d",&m4);
	fflush(stdin);	
}
void calcular_total(){
	total = b1*2 + b2*1 + b3*1.5 + s1*2.5 + s2*2 + s3*1.5 + d1*1 + d2*1.5 + d3*2;
	printf("O total do seu pedido e: %.2f\n", total);
}
main(){
	menu1();
	do{
		switch(m1){
  			case 1:
    			menu2();
    			switch(m2){
	  				case 1:
	   					b1++;
	   					break;
	  				case 2:
		   				b2++;
		   				break;
		    		case 3:
		    			b3++;
		    			break;
		    		case 4:	
			   			m1=0;
			    		menu1();
			    		break;
			  		default:
			  			printf("ERRO");
				}
    			break;
  			case 2:
    			menu3();
    			switch(m3){
	  				case 1:
	    				s1++;
	    				break;
	  				case 2:
		    			s2++;
		    			break;
			   		case 3:
			   			s3++;
			   			break;
			   		case 4:
			   			m1=0;
			   			menu1();
			   			break;
			  		default:
			  			printf("ERRO");
				}
    			break;
    		case 3:
    			menu4();
    			switch(m4){
	  				case 1:
	    				d1++;
	    				break;
	  				case 2:
		    			d2++;
		    			break;
			    	case 3:
			    		d3++;
			    		break;
			    	case 4:
			    		m1=0;
			    		menu1();
			    		break;
			  		default:
			  			printf("ERRO");
			  	}
    			break;
    		case 4:
    			calcular_total();
    			++m1;
	    		break;
  			default:
  				printf("ERRO");
		}		
	}while(m1!=5);   	
    do{
		if(total>0){
			printf("Total a pagar: %.2f Euros\n", total);
			printf("Quantas moedas de 2 Euros quer inserir?\n");
			scanf("%f", &euro);
			total=total - euro * 2;
			if(total==0){
				printf("Obrigado pela Preferencia e Bom dia");
				return 0;
			}else{
				if(total<0){
					printf("O seu troco e: %.2f Euros\n", -total);
					printf("Obrigado pela Preferencia e Bom dia");	
					return 0;
				}else{
					printf("Total a pagar: %.2f Euros\n", total);
					printf("Quantas moedas de 1 Euro quer inserir?\n");
					scanf("%f", &euro);
					total=total - euro;
					if(total==0){
						printf("Obrigado pela Preferencia e Bom dia");
						return 0;
					}else{
						if(total<0){
							printf("O seu troco e: %.2f Euros\n", -total);
							printf("Obrigado pela Preferencia e Bom dia");
							return 0;
						}else{
							printf("Total a pagar: %.2f Euros\n", total);
							printf("Quantas moedas de 50 Centimos quer inserir?\n");
							scanf("%f", &euro);
							total=total - euro / 2;
							if(total==0){
								printf("Obrigado pela Preferencia e Bom dia");
								return 0;
							}else{
								if(total<0){
									printf("O seu troco e: %.2f Euros\n", -total);
									printf("Obrigado pela Preferencia e Bom dia");			
									return 0;
								}else{
									printf("Total a pagar: %.2f Euros\n", total);
									printf("Quantas moedas de 20 Centimos quer inserir?\n");
									scanf("%f", &euro);
									total=total - euro / 5;	
									if(total==0){
										printf("Obrigado pela Preferencia e Bom dia");
										return 0;
									}else{
										if(total<0){
											printf("O seu troco e: %.2f Euros\n", -total);
											printf("Obrigado pela Preferencia e Bom dia");
											return 0;
										}else{
											printf("Total a pagar: %.2f Euros\n", total);
											printf("Quantas moedas de 10 Centimos quer inserir?\n");
											scanf("%f", &euro);
											total=total - euro / 10;
											if(total==0){
												printf("Obrigado pela Preferencia e Bom dia");
												return 0;
											}else{
												if(total<0){
													printf("O seu troco e: %.2f Euros\n", -total);
													printf("Obrigado pela Preferencia e Bom dia");
													return 0;
												}else{
													printf("Total a pagar: %.2f Euros\n", total);
													printf("Quantas moedas de 5 Centimos quer inserir?\n");
													scanf("%f", &euro);
													total=total - euro / 20;
													if(total==0){
														printf("Obrigado pela Preferencia e Bom dia");
														return 0;
													}else{
														if(total<0){
															printf("O seu troco e: %.2f Euros\n", -total);
															printf("Obrigado pela Preferencia e Bom dia");
															return 0;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}while(total>0);
}
