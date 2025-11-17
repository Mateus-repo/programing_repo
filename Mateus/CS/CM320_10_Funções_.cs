/*
Agrupamento de Escolas Marinha Grande Nascente
Curso: Curso Profissional de Programador de Informática
Disciplina: Computação Móvel
Tarefa: CM320_Funções_

Número: 10
Nome: Mateus Almeida Feliciano
Links de pesquisa: https://www.w3schools.com/cs/index.php
*/

using System;
using System.Linq;

namespace MeuEspaco
{
    class Programa
    {
        public class Aluno
        {
            public string Nome;
            public double Notas;
            
            public Aluno(string? nome, double notas)
            {
                Nome = nome;
                Notas = notas;
            }
        }
        public static void Hold()
        {
            Console.WriteLine("\n(Prima \"Enter\" para continuar a execucao!)");
            Console.ReadKey(true);
            Console.Clear();       // Limpa o ecrã
        }
        public static void EndProgram()
        {
            Console.WriteLine("\n(Prima \"Enter\" para terminar a execucao!)");
            Console.ReadKey(true);
            Console.Clear();       // Limpa o ecrã
        }

        static int getSizeAluno(Aluno[] alunos)
        {
            int size = 0;
            foreach (var aluno in alunos)
            {
                size++;
            }
            return size;
        }
        static Aluno[] GetClassfications(Aluno[] alunos)
        {
            int size = getSizeAluno(alunos);
            Aluno[] alunosTemp = new Aluno[size];
            for (int i = 0; i < size; i++)
            {
                Console.Write($"Digite o nome do aluno nº{i + 1}: ");
                string nomeTemp = Console.ReadLine();

                double notaTemp;
                while (true)
                {
                    Console.Write($"Digite a nota do/a {nomeTemp}: ");
                    if (!double.TryParse(Console.ReadLine(), out notaTemp))
                    {
                        Console.WriteLine("Entrada inválida! Digite apenas números.");
                        Hold();
                    }
                    else
                    {
                        break;
                    }
                }

                alunosTemp[i] = new Aluno(nomeTemp, notaTemp);
                Console.Clear();
            }

            return alunosTemp;
        }
        static double GetTotalNotas(Aluno[] alunos)
        {
            double total = 0D;
            foreach (var aluno in alunos)
            {
                total += aluno.Notas;
            }
            return total;
        }
        
        static double GetMediaNotas(Aluno[] alunos)
        {
            double total = GetTotalNotas(alunos);
            return total / getSizeAluno(alunos);
        }

        static void GetMediaNotasPorEndereco(Aluno[] alunos, out double var_mediaTemp)
        {
            double total = GetTotalNotas(alunos);
            var_mediaTemp = total / getSizeAluno(alunos);
        }
        
        static int Main(string[] args)
        {
            long quantidade = 0;
            while (true)
            {
                Console.Write("Quantos alunos deseja inserir : ");
                if(!long.TryParse(Console.ReadLine(), out quantidade ))
                {
                    Console.WriteLine("Entrada inválida! Digite apenas números.");
                    Hold();
                }else{break;}
            }
            
            Aluno[] alunos  = new Aluno[quantidade];
            alunos = GetClassfications(alunos);
            double var_total = GetTotalNotas(alunos);
            double var_media = 0;
            // double var_media = GetMediaNotas(alunos);
            GetMediaNotasPorEndereco(alunos, out var_media);

            for (int i = 0; i < quantidade; i++)
            {
                Console.WriteLine($"Aluno nº {i + 1} - {alunos[i].Nome}: {alunos[i].Notas}");
            }
            Console.WriteLine($"\nTotal: {var_total}");
            Console.WriteLine($"Média: {var_media:F2}"); // apenas 2 caracteres decimais
            EndProgram();
            return 0;
        }
    }
};

