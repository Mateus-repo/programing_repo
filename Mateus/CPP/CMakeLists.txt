cmake_minimum_required(VERSION 4.0)
project(CPP)

set(CMAKE_CXX_STANDARD 14)

include_directories(GS1_WIN)

add_executable(CPP
        GS1_WIN/config.h
        GS1_WIN/config_dpmm.h
        GS1_WIN/gs1_Win_Pallet.cpp
        GS1_WIN/gs1_Win_Products.cpp
        "1.1).cpp"
        "1.10).cpp"
        "1.10)_2.cpp"
        "1.11).cpp"
        "1.12).cpp"
        "1.13).cpp"
        "1.2).cpp"
        "1.3).cpp"
        "1.4).cpp"
        "1.5).cpp"
        "1.6).cpp"
        "1.7).cpp"
        "1.8).cpp"
        "1.9).cpp"
        10_11_23.cpp
        14_11_23.cpp
        15_11_23.cpp
        4_11_23.cpp
        7_11_23.cpp
        agenda_base.cpp
        agendaTrabalho2.cpp
        "agendaTrabalho_MateusFeliciano (1).cpp"
        agendaTrabalho_MateusFeliciano.cpp
        "agendaTrabalho_MateusFeliciano_Kyryl - Cópia.cpp"
        agendaTrabalho_MateusFeliciano_Kyryl.cpp
        aleatorio.cpp
        aula_16_02_2024.cpp
        aula_16_02_2024_2.cpp
        CM303_10_Hello-world.cpp
        "CM304_10_Nome e idade.cpp"
        "CM305_10_Calculadora-simples 1.cpp"
        CM306_10_Calcular-média.cpp
        CM307_10_Constante-PI.cpp
        CM308_10_Variável-temporária.cpp
        "CM309_10_Operadores lógicos.cpp"
        CM310_10_if_else-if_else.cpp
        CM311_10_switch_case_break_default.cpp
        CM312_10_for_.cpp
        CM313_10_while_.cpp
        CM314_10_do-while_switch_break_.cpp
        "CM315_10_Funções_ v4.cpp"
        CM315_10_Funções_.cpp
        CM316_10_Arrays-Strings_.cpp
        CM316_10_Arrays-Strings_v2.cpp
        CM317_10Classes-POO_Exercício2.cpp
        CM318_10_Classes-POO_Exercício2A_.cpp
        completo.cpp
        ex01.cpp
        ex02.cpp
        ex03.cpp
        exemploPonteiro.cpp
        exemploSizeof.cpp
        funcaoTroca.cpp
        jogodogalo1.cpp
        jogodogalo2.cpp
        kyril.cpp
        lista_01.cpp
        listaLigada_basico.cpp
        numeroescondido_basic.cpp
        numeroescondido_basic_mateus_feliciano_n10_t_10_d_e.cpp
        numeroescondido_expert.cpp
        numeroescondido_expert_mateus_feliciano_n10_t_10_d_e.cpp
        prob1.cpp
        programaBase.cpp
        testes.cpp
        "TP rodrigo.cpp"
        "Trabalho_pratico_17_11_2023 - Cópia.cpp"
        Trabalho_pratico_17_11_2023.cpp
        Trabalho_pratico_17_11_2023_2.cpp
        Trabalho_pratico_17_11_2023_3.cpp
        Untitled1.cpp
        Untitled2.cpp
        Untitled3.cpp
        voides_ex.cpp
        voids.cpp)
