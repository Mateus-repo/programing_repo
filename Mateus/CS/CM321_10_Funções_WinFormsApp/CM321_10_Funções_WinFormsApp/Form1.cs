/*
Agrupamento de Escolas Marinha Grande Nascente
Curso: Curso Profissional de Programador de Informática
Disciplina: Computação Móvel
Tarefa: CM321_Funções_

Número: 10
Nome: Mateus Almeida Feliciano
Links de pesquisa: https://www.w3schools.com/cs/index.php 
https://www.educative.io/answers/what-is-listview-in-c-sharp
https://raisanenmarkus.github.io/csharp/part3/1/
https://naikrahul.wordpress.com/2017/08/26/c-how-to-add-click-event-for-dynamically-created-buttons/
*/

namespace CM321_10_Funções_WinFormsApp;

public partial class Form1 : Form
{
    List<string> nomes = new List<string>();
    List<double> notas = new List<double>();
    
    public Form1()
    {
        InitializeComponent();
        ConfigurarListas();
        ConfigurarButoes();
    }

    private void ConfigurarListas()
    {
        listView_Dados.View = View.Details;
        listView_Dados.Columns.Clear();
        listView_Dados.Columns.Add("Nome", 150);
        listView_Dados.Columns.Add("Nota", 100);
        
        listView_Total_Media.View = View.Details;
        listView_Total_Media.Columns.Clear();
        listView_Total_Media.Columns.Add("Total", 100);
        listView_Total_Media.Columns.Add("Média", 100);
    }
    
    private void ConfigurarButoes()
    {
        btn_Inserir.Click += BtnInserir_Click; // acionar função ao butao, em vez de igualar o butao á função, ou seja, o butao pode ter mais de uma função associada usando += em vez de =
        btn_Calcular.Click += BtnCalcular_Click;
        btn_Limpar.Click += BtnLimpar_Click;
    }   
    
    private void BtnInserir_Click(object sender, EventArgs e)
    {
        string nome = txtBox_Nome.Text;
        double nota;
        
        if (string.IsNullOrWhiteSpace(nome))
        {
            MessageBox.Show("Insira um nome válido.");
            return;
        }

        if (!double.TryParse(txtBox_Nota.Text, out nota))
        {
            MessageBox.Show("Insira uma nota válida.");
            return;
        }
        
        if (nota < 0 || nota > 20)
        {
            MessageBox.Show("A nota deve estar entre 0 e 20.", "Erro", 
                MessageBoxButtons.OK, MessageBoxIcon.Warning);
            txtBox_Nota.Focus();
            return;
        }
        
        nomes.Add(nome);
        notas.Add(nota);
        
        AtualizarDados();
        
        txtBox_Nota.Clear();
        txtBox_Nome.Clear();
        txtBox_Nome.Focus();
    }

    private double GetTotal(List<double> notasTemp)
    {
        double total = notasTemp.Sum();
        total = Math.Round(total, 2);
        return total;
    }

    private void GetMediaEndereco(List<double> notasTemp, out double var_media)
    {
        var_media = notasTemp.Average();
        var_media = Math.Round(var_media, 2);
    }
    private void BtnCalcular_Click(object sender, EventArgs e)
    {
        if (notas.Count == 0)
        {
            MessageBox.Show("Não há dados para calcular. Insira pelo menos um aluno.", 
                "Aviso", MessageBoxButtons.OK, MessageBoxIcon.Information);
            return;
        }

        double var_total = GetTotal(notas);
        double var_media = 0;
        GetMediaEndereco(notas, out var_media);
        
        listView_Total_Media.Items.Clear();
        ListViewItem itens = new ListViewItem(var_total.ToString("F2"));
        itens.SubItems.Add(var_media.ToString("F2"));
        listView_Total_Media.Items.Add(itens);
    }
    
    private void BtnLimpar_Click(object sender, EventArgs e)
    {
        listView_Dados.Items.Clear();
        listView_Total_Media.Items.Clear();
        txtBox_Nota.ResetText();
        txtBox_Nome.ResetText(); // é igual a txtBox_nome = string.Empty; (eu acho, ou devia)
        nomes.Clear();
        notas.Clear();
    }
    private void AtualizarDados()
    {
        listView_Dados.Items.Clear();
        for (int i = 0; i < nomes.Count; i++)
        {
            ListViewItem item = new ListViewItem(nomes[i]);
            item.SubItems.Add(notas[i].ToString("F2"));
            listView_Dados.Items.Add(item);
        }
    }
}