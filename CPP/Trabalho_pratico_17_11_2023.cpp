#include <stdio.h>
#include <conio.h>

main(){
	int op, repetir, rep, repm, b, s, d;
	float custo=0, euro2, euro1, euro05, euro02, euro01, euro005;
	//custo+=1.5 LEMBRAR
	//printf("%.2f", custo);
	do{
		printf("--------MENU--------\n1-Bebidas\n2-Sandes\n3-Doces\n");
		scanf("%d", &op);
		if(op<1||op>3){
			printf("Erro!!\nOpcao nao existente, tente de novo\n");
		}else{
			if(op==1){
				printf("\n--------Bebidas--------\n1-Cafe com leite (frio)\n2-Cha Frio (Ice Tea)\n3-Coca-Cola\n4-7up\n5-Sumol\n6-Monster\n7-Fanta\n8-Guarana Antartica\n");
				scanf("%d", &op);
				if(op<1||op>8){
					printf("Erro!!\nOpcao nao existente, tente de novo\n");
				}else{
					if(op==1){
						printf("Cafe com leite 1.20 Euros\n");
						custo+=1.20;
					}else{
						if(op==2){
							printf("--------Ice Tea--------\n1-Limao\n2-Pessego\n3-Manga\n4-Frutos Vermelhos\n5-Lima\n6-Maracuja e Pessego\n");
							scanf("%d", &op);
							if(op<1||op>6){
								printf("Erro!!\nOpcao nao existente, tente de novo\n");
							}else{
								if(op==1){
									printf("Ice Tea de Limao 1.50 Euros\n");
									custo+=1.50;
								}else{
									if(op==2){
										printf("Ice Tea de Pessego 1.50 Euros\n");
										custo+=1.50;
									}else{
										if(op==3){
											printf("Ice Tea de Manga 1.50 Euros\n");
											custo+=1.50;
										}else{
											if(op==4){
												printf("Ice Tea de Frutos Vermelhos 1.50 Euros\n");
												custo+=1.50;
											}else{
												if(op==5){
													printf("Ice Tea de Lima 1.50 Euros\n");
													custo+=1.50;
												}else{
													printf("Ice Tea de Maracuja e Pessego 1.75 Euros\n");
													custo+=1.75;
												}
											}
										}
									}
								}
							}
						}else{
							if(op==3){
								printf("--------Coca-Cola--------\n1-Coca-Cola Normal\n2-Coca-Cola Light\n3-Coca-Cola Zero\n4-Coca-Cola Zero Cafeina\n5-Coca-Cola de Canela (Por Tempo Limitado)\n6-Coca-Cola de Limao\n7-Coca-Cola de Baunilha\n8-Coca-Cola de Cereja\n9-Coca-Cola de Lima\n10-Coca-Cola de Laranja Sanguinea (Por Tempo Limitado)\n11-Coca-Cola de Limao e Lima (Por Tempo Limitado)\n12-Coca-Cola de Laranja (Tempo Limitado)\n13-Coca-Cola de Cha Verde\n");
								scanf("%d", &op);
								if(op<1||op>6){
									printf("Erro!!\nOpcao nao existente, tente de novo\n");
								}else{
									if(op==1){
										printf("Coca-Cola Normal 1.50 Euros\n");
										custo+=1.50;
									}else{
										if(op==2){
											printf("Coca-Cola Light 1.40 Euros\n");
											custo+=1.40;
										}else{
											if(op==3){
												printf("Coca-Cola Zero 1.45 Euros\n");
												custo+=1.45;
											}else{
												if(op==4){
													printf("Coca-Cola Zero Cafeina 1.35 Euros\n");
													custo+=1.35;
												}else{
													if(op==5){
														printf("Coca-Cola de Canela 1.60 Euros\n");
														custo+=1.60;
													}else{
														if(op==6){
															printf("Coca-Cola de Limao 1.60 Euros\n");
															custo+=1.60;
														}else{
															if(op==7){
																printf("Coca-Cola de Baunilha 1.60 Euros\n");
																custo+=1.60;
															}else{
																if(op==8){
																	printf("Coca-Cola de Cereja 1.60 Euros\n");
																	custo+=1.60;
																}else{
																	if(op==9){
																		printf("Coca-Cola de Lima 1.50 Euros\n");
																		custo+=1.50;
																	}else{
																		if(op==10){
																			printf("Coca-Cola de Laranja Sanguinea 1.45 Euros\n");
																			custo+=1.45;
																		}else{
																			if(op==11){
																				printf("Coca-Cola de Limao e Lima 1.55 Euros\n");
																				custo+=1.55;
																			}else{
																				if(op==12){
																					printf("Coca-Cola de Laranja 1.60 Euros\n");
																					custo+=1.60;
																				}else{
																					printf("Coca-Cola de Cha Verde 1.50 Eruos\n");
																					custo+=1.50;
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
							}else{
								if(op==4){
									printf("7up 1.70 Euros\n");
									custo+=1.70;
								}else{
									if(op==5){
										printf("--------Sumol--------\n1-Sumol de Ananas\n2-Sumol de Laranja\n3-Sumol de Limao\n4-Sumol de Maracuja\n");
										scanf("%d", &op);
										if(op<1||op>3){
											printf("Erro!!\nOpcao nao existente, tente de novo\n");
										}else{
											if(op==1){
												printf("Sumol de Ananas 1.50 Euros\n");
												custo+=1.50;
											}else{
												if(op==2){
													printf("Sumol de Laranja 1.50 Euros\n");
													custo+=1.50;
												}else{
													if(op==3){
														printf("Sumol de Limao 1.50 Euros\n");
														custo+=1.50;
													}else{
														printf("Sumol de Maracuja 1.50 Euros\n");
														custo+=1.50;
													}
												}
											}
										}
									}else{
										if(op==6){
											printf("--------Monster--------\n1-Monster Energy\n2-Monster Energy Zero Acucar\n3-Monster Energy Assualt\n4-Monster Energy Mule\n5-Monster Energy Zero Acucar Lewis Hamilton (Por Tempo Limitado)\n6-Monster Energy Ananas Branco\n7-Monster Energy Melancia\n8-Monster Energy Ultra Melanica\n9-Monster Energy Ultra Festa de Manga\n10-Monster Energy Ultra Zero Acucar\n11-Monster Energy Ultra Paraiso de Kiwi e Lima\n12-Juiced Monster Energy Laranja\n13-Juiced Monster Energy Pessego e Nectarina\n14-Juiced Monster Energy Manga Sumarenta\n15-Juiced Monster Energy Sumos Tropicais\n16-Juiced Monster Energy Tropical\n17-Juiced Monster Energy Frutas\n18-Rehab Monster Energy Cha e Limonada\n");
											scanf("%d", &op);
											if(op<1||op>18){
												printf("Erro!!\nOpcao nao existente, tente de novo\n");
											}else{
												if(op==1){
													printf("Monster Energy 1.80 Euros\n");
													custo+=1.80;
												}else{
													if(op==2){
														printf("Monster Energy Zero Acucar 1.75 Euros\n");
														custo+=1.75;
													}else{
														if(op==3){
															printf("Monster Energy Assualt 1.90 Euros\n");
															custo+=1.90;
														}else{
															if(op==4){
																printf("Monster Energy Mule 1.85 Euros\n");
																custo+=1.85;
															}else{
																if(op==5){
																	printf("Monster Energy Zero Acucar Lewis Hamilton 2.50 Euros\n");
																	custo+=2.50;
																}else{
																	if(op==6){
																		printf("Monster Energy Ananas Branco 1.80 Euros\n");
																		custo+=1.80;
																	}else{
																		if(op==7){
																			printf("Monster Energy Melancia 1.65 Euros\n");
																			custo+=1.65;
																		}else{
																			if(op==8){
																				printf("Monster Energy Ultra Melanica 1.90 Euros\n");
																				custo+=1.90;
																			}else{
																				if(op==9){
																					printf("Monster Energy Ultra Festa de Manga 1.85 Euros\n");
																					custo+=1.85;
																				}else{
																					if(op==10){
																						printf("Monster Energy Ultra Zero Acucar 1.80 Euros\n");
																						custo+=1.80;
																					}else{
																						if(op==11){
																							printf("Monster Energy Ultra Paraiso de Kiwi e Lima 1.90 Euros\n");
																							custo+=1.90;
																						}else{
																							if(op==12){
																								printf("Juiced Monster Energy Laranja 1.80 Euros\n");
																								custo+=1.80;
																							}else{
																								if(op==13){
																									printf("Juiced Monster Energy Pessego e Nectarina 2.00 Euros\n");
																									custo+=2.00;
																								}else{
																									if(op==14){
																										printf("Juiced Monster Energy Manga Sumarenta 1.90 Euros\n");
																										custo+=1.90;
																									}else{
																										if(op==15){
																											printf("Juiced Monster Energy Sumos Tropicais 1.85 Euros\n");
																											custo+=1.85;
																										}else{
																											if(op==16){
																												printf("Juiced Monster Energy Tropical 1.75 Euros\n");
																												custo+=1.75;
																											}else{
																												if(op==17){
																													printf("Juiced Monster Energy Frutas 1.85 Euros\n");
																													custo+=1.85;
																												}else{
																													printf("Rehab Monster Energy Cha e Limonada 2.00 Euros\n");
																													custo+=2.00;
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
															}
														}
													}
												}
											}
										}else{
											if(op==7){
												printf("--------Fanta--------\n1-Fanta Laranja\n2-Fanta Laranja Zero Acucar\n3-Fanta Ananas\n4-Fanta Ananas Zero Acucar\n5-Fanta Maracuja\n6-Fanta Maracuja Zero Acucar\n7-Fanta Uva\n8--Fanta Uva Zero Acucar\n9-Fanta Guarana\n10-Fanta Guarana Zero Acucar\n11-Fanta Morango (Por Tempo Limitado)\n12-Fanta Limao (Por Tempo Limitado)\n13-Fanta Pessego (Por Tempo Limitado)\n14-Fanta Sabor Mistério Rosa (Por Tempo Limitado)\n15-Fanta Sabor Mistério Azul(Por Tempo Limitado)\n16-Fanta Sabor Mistério Verde(Por Tempo Limitado)\n");
												scanf("%d", &op);
												if(op<1||op>16){
													printf("Erro!!\nOpcao nao existente, tente de novo\n");
												}else{
													if(op==1){
														printf("Fanta Laranja 1.50 Euros\n");
														custo+=1.50;
													}else{
														if(op==2){
															printf("Fanta Laranja Zero Acucar 1.40 Euros\n");
															custo+=1.40;
														}else{
															if(op==3){
																printf("Fanta Ananas 1.55 Euros\n");
																custo+=1.55;
															}else{
																if(op==4){
																	printf("Fanta Ananas Zero Acucar 1.45 Euros\n");
																	custo+=1.45;
																}else{
																	if(op==5){
																		printf("Fanta Maracuja 1.60 Euros\n");
																		custo+=1.60;		
																	}else{
																		if(op==6){
																			printf("Fanta Maracuja Zero Acucar 1.55 Euros\n");
																			custo+=1.55;
																		}else{
																			if(op==7){
																				printf("Fanta Uva 1.60 Euros\n");
																				custo+=1.60;
																			}else{
																				if(op==8){
																					printf("Fanta Uva Zero Acucar 1.50 Euros\n");
																					custo+=1.50;
																				}else{
																					if(op==9){
																						printf("Fanta Guarana 1.75 Euros\n");
																						custo+=1.75;
																					}else{
																						if(op==10){
																							printf("Fanta Guarana Zero Acucar 1.70 Euros\n");
																							custo+=1.70;
																						}else{
																							if(op==11){
																								printf("Fanta Morango 1.70 Euros\n");
																								custo+=1.70;
																							}else{
																								if(op==12){
																									printf("Fanta Limao 1.70 Euros\n");
																									custo+=1.70;
																								}else{
																									if(op==13){
																										printf("Fanta Pessego 1.70 Euros\n");
																										custo+=1.70;
																									}else{
																										if(op==14){
																											printf("Fanta Sabor Mistério Rosa 1.80 Euros\n");
																											custo+=1.80;
																										}else{
																											if(op==15){
																												printf("Fanta Sabor Mistério Azul 1.80 Euros\n");
																												custo+=1.80;
																											}else{
																												printf("Fanta Sabor Mistério Verde 1.80 Euros\n");
																												custo+=1.80;
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
														}
													}
												}
											}else{
												printf("Guarana Antartica 1.75 Euros\n");
												custo+=1.75;
											}
										}
									}
								}
							}
						}
					}
				}
			}else{
				if(op==2){
					printf("--------Sandes--------\n1-Sandes com Atum\n2-Sandes com Quiejo e Fiambre\n3-Sandes com Chouriço\n4-Sandes de Mortandela\n5-Sandes de Frango\n6-Sandes Vegetariana\n");
					scanf("%d", &op);
					if(op<1||op>6){
						printf("Erro!!\nOpcao nao existente, tente de novo\n");
					}else{
						if(op==1){
							printf("Sandes com Atum 2.5O Euros\n");
							custo+=2.50;
						}else{
							if(op==2){
								printf("Sandes com Queijo e Fiambre 2.20 Euros\n");
								custo+=2.20;
							}else{
								if(op==3){
									printf("Sandes com Chourico 2.60 Euros\n");
									custo+=2.60;
								}else{
									if(op==4){
										printf("Sandes de Mortandela 2.50 Euros\n");
										custo+=2.50;
									}else{
										if(op==5){
											printf("Sandes de Frango 2.30 Euros\n");
											custo+=2.30;
										}else{
											printf("Sandes Vegetariana 2.10 Euros\n");
											custo+=2.10;
										}
									}
								}
							}
						}
					}
				}else{
					printf("--------Doces--------\n1-Arroz Doce\n2-Panquecas com Mel\n3-Biscoitos com Pepitas de Chocolate\n4-Gelatina\n5-Pudim\n6-Kinder Chocolate (8 porcoes)\n7-Kinder Bueno (2 porcoes)\n8-Bolo de Arroz\n9-Gomas\n10-Pastel de Nata\n");
					scanf("%d", &op);
					if(op<1||op>10){
						printf("Erro!!\nOpcao nao existente, tente de novo\n");
					}else{
						if(op==1){
							printf("--------Arroz Doce--------\n1-Arroz Doce com Canela\n2-Arroz Doce sem Canela\n");
							scanf("%d", &op);
							if(op<1||op>2){
								printf("Erro!!\nOpcao nao existente, tente de novo\n");
							}else{
								if(op==1){
									printf("Arroz Doce com Canela 1.35 Euros\n");
									custo+=1.35;
								}else{
									printf("Arroz Doce sem Canela 1.30 Euros\n");
									custo+=1.30;
								}
							}
						}else{
							if(op==2){
								printf("--------Panquecas com Mel--------\n1-Panquecas com Mel (6 unidades)\n2-Panquecas com Mel (8 unidades)\n3-Panquecas com Mel (12 unidades\n");
								scanf("%d", &op);
								if(op<1||op>3){
									printf("Erro!!\nOpcao nao existente, tente de novo\n");
								}else{
									if(op==1){
										printf("Panquecas com Mel (6 unidades) 2.40 Euros\n");
										custo+=2.40;
									}else{
										if(op==2){
											printf("Panquecas com Mel (8 unidades) 3.20 Euros\n");
											custo+=3.20;
										}else{
											printf("Panquecas com Mel (12 unidades) 4.00 Euros\n");
											custo+=4.00;
										}
									}
								}
							}else{
								if(op==3){
									printf("--------Biscoitos com Pepitas de Chocolate--------\n1-Biscoitos com Pepitas de Chocolate (6 unidades)\n2-Biscoitos com Pepitas de Chocolate (8 unidades)\n3-Biscoitos com Pepitas de Chocolate (12 Unidades)\n");
									scanf("%d", &op);
									if(op<1||op>3){
										printf("Erro!!\nOpcao nao existente, tente de novo\n");
									}else{
										if(op==1){
											printf("Biscoitos com Pepitas de Chocolate (6 unidades) 2.10 Euros\n");
											custo+=2.10;
										}else{
											if(op==2){
												printf("Biscoitos com Pepitas de Chocolate (8 unidades) 2.80 Euros\n");
												custo+=2.80;
											}else{
												printf("Biscoitos com Pepitas de Chocolate (12 unidades) 4.20 Euros\n");
												custo+=4.20;
											}
										}
									}
								}else{
									if(op==4){
										printf("--------Gelatina--------\n1-Gelatina de Morango\n2-Gelatina de Limao\n3-Gelatina de Tutti-Frutti\n");
										scanf("%d", &op);
										if(op<1||op>3){
											printf("Erro!!\nOpcao nao existente, tente de novo\n");
										}else{
											if(op){
												printf("Gelatina de Morango 1.20 Euros\n");
												custo+=1.20;
											}else{
												if(op==2){
													printf("Gelatina de Limao 1.20 Euros\n");
													custo+=1.20;
												}else{
													printf("Gelatina de Tutti-Frutti 1.20 Euros\n");
													custo+=1.20;
												}
											}
										}
									}else{
										if(op==5){
											printf("Pudim 1.40 Euros");
											custo+=1.40;
										}else{
											if(op==6){
												printf("Kinder Chocolate (8 porcoes) 1.60 Euros\n");
												custo+=1.60;
											}else{
												if(op==7){
													printf("Kinder Bueno (2 porcoes) 1.70 Euros\n");
													custo+=1.70;
												}else{
													if(op==8){
														printf("Bolo de Arroz 1.50 Euros\n");
														custo+=1.50;
													}else{
														if(op==9){
															printf("Gomas 1.60 Euros\n");
															custo+=1.60;
														}else{
															printf("Pastel de Nata 1.20 Euros\n");
															custo+=1.20;
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
		printf("Gostaria de pedir mais alguma coisa?\n1-Sim\n0-Nao\n");
		scanf("%d", &repetir);
		if(repetir<0||repetir>1){
			printf("Erro!!\nOpcao nao existente, tente de novo\n");
		}else{
			if(repetir==0){
				++rep;
			}
		}
	}while(rep<=0);
	do{
		if(custo>0){
			printf("Total a pagar: %.2f Euros\n", custo);
			printf("Quantas moedas de 2 Euros quer inserir?\n");
			scanf("%f", &euro2);
			custo=custo - euro2 * 2;
			if(custo==0){
				printf("Obrigado pela Preferencia e Bom dia");
				return 0;
			}else{
				if(custo<0){
					printf("O seu troco e: %.2f Euros\n", -custo);
					printf("Obrigado pela Preferencia e Bom dia");	
					return 0;
				}else{
					printf("Total a pagar: %.2f Euros\n", custo);
					printf("Quantas moedas de 1 Euro quer inserir?\n");
					scanf("%f", &euro1);
					custo=custo - euro1;
					if(custo==0){
						printf("Obrigado pela Preferencia e Bom dia");
						return 0;
					}else{
						if(custo<0){
							printf("O seu troco e: %.2f Euros\n", -custo);
							printf("Obrigado pela Preferencia e Bom dia");
							return 0;
						}else{
							printf("Total a pagar: %.2f Euros\n", custo);
							printf("Quantas moedas de 50 Centimos quer inserir?\n");
							scanf("%f", &euro05);
							custo=custo - euro05 / 2;
							if(custo==0){
								printf("Obrigado pela Preferencia e Bom dia");
								return 0;
							}else{
								if(custo<0){
									printf("O seu troco e: %.2f Euros\n", -custo);
									printf("Obrigado pela Preferencia e Bom dia");			
									return 0;
								}else{
									printf("Total a pagar: %.2f Euros\n", custo);
									printf("Quantas moedas de 20 Centimos quer inserir?\n");
									scanf("%f", &euro02);
									custo=custo - euro02 / 5;	
									if(custo==0){
										printf("Obrigado pela Preferencia e Bom dia");
										return 0;
									}else{
										if(custo<0){
											printf("O seu troco e: %.2f Euros\n", -custo);
											printf("Obrigado pela Preferencia e Bom dia");
											return 0;
										}else{
											printf("Total a pagar: %.2f Euros\n", custo);
											printf("Quantas moedas de 10 Centimos quer inserir?\n");
											scanf("%f", &euro01);
											custo=custo - euro01 / 10;
											if(custo==0){
												printf("Obrigado pela Preferencia e Bom dia");
												return 0;
											}else{
												if(custo<0){
													printf("O seu troco e: %.2f Euros\n", -custo);
													printf("Obrigado pela Preferencia e Bom dia");
													return 0;
												}else{
													printf("Total a pagar: %.2f Euros\n", custo);
													printf("Quantas moedas de 5 Centimos quer inserir?\n");
													scanf("%f", &euro005);
													custo=custo - euro005 / 20;
													if(custo==0){
														printf("Obrigado pela Preferencia e Bom dia");
														return 0;
													}else{
														if(custo<0){
															printf("O seu troco e: %.2f Euros\n", -custo);
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
	}while(repm<1);
}
