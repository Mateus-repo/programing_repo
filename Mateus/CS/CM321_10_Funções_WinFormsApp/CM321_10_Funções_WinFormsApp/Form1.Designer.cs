namespace CM321_10_Funções_WinFormsApp;

partial class Form1
{
    /// <summary>
    ///  Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    ///  Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null))
        {
            components.Dispose();
        }

        base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
        btn_Inserir = new System.Windows.Forms.Button();
        txt_Nome = new System.Windows.Forms.Label();
        btn_Calcular = new System.Windows.Forms.Button();
        txtBox_Nome = new System.Windows.Forms.TextBox();
        txtBox_Nota = new System.Windows.Forms.TextBox();
        txt_Nota = new System.Windows.Forms.Label();
        listView_Dados = new System.Windows.Forms.ListView();
        txt_Output = new System.Windows.Forms.Label();
        txt_Copyright = new System.Windows.Forms.Label();
        listView_Total_Media = new System.Windows.Forms.ListView();
        txt_Total_Media = new System.Windows.Forms.Label();
        btn_Limpar = new System.Windows.Forms.Button();
        SuspendLayout();
        // 
        // btn_Inserir
        // 
        btn_Inserir.Location = new System.Drawing.Point(39, 158);
        btn_Inserir.Name = "btn_Inserir";
        btn_Inserir.Size = new System.Drawing.Size(107, 47);
        btn_Inserir.TabIndex = 0;
        btn_Inserir.Text = "Inserir dados";
        btn_Inserir.UseVisualStyleBackColor = true;
        // 
        // txt_Nome
        // 
        txt_Nome.Font = new System.Drawing.Font("Segoe UI", 12F);
        txt_Nome.Location = new System.Drawing.Point(39, 29);
        txt_Nome.Name = "txt_Nome";
        txt_Nome.Size = new System.Drawing.Size(220, 22);
        txt_Nome.TabIndex = 1;
        txt_Nome.Text = "Inserir Nome do Aluno";
        // 
        // btn_Calcular
        // 
        btn_Calcular.Location = new System.Drawing.Point(152, 158);
        btn_Calcular.Name = "btn_Calcular";
        btn_Calcular.Size = new System.Drawing.Size(107, 47);
        btn_Calcular.TabIndex = 2;
        btn_Calcular.Text = "Calcular";
        btn_Calcular.UseVisualStyleBackColor = true;
        // 
        // txtBox_Nome
        // 
        txtBox_Nome.Location = new System.Drawing.Point(39, 54);
        txtBox_Nome.Name = "txtBox_Nome";
        txtBox_Nome.Size = new System.Drawing.Size(220, 23);
        txtBox_Nome.TabIndex = 3;
        // 
        // txtBox_Nota
        // 
        txtBox_Nota.Location = new System.Drawing.Point(39, 117);
        txtBox_Nota.Name = "txtBox_Nota";
        txtBox_Nota.Size = new System.Drawing.Size(220, 23);
        txtBox_Nota.TabIndex = 4;
        // 
        // txt_Nota
        // 
        txt_Nota.Font = new System.Drawing.Font("Segoe UI", 12F);
        txt_Nota.Location = new System.Drawing.Point(39, 92);
        txt_Nota.Name = "txt_Nota";
        txt_Nota.Size = new System.Drawing.Size(220, 22);
        txt_Nota.TabIndex = 5;
        txt_Nota.Text = "Inserir Nota do Aluno";
        // 
        // listView_Dados
        // 
        listView_Dados.Anchor = ((System.Windows.Forms.AnchorStyles)(System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right));
        listView_Dados.Location = new System.Drawing.Point(329, 54);
        listView_Dados.Name = "listView_Dados";
        listView_Dados.Size = new System.Drawing.Size(447, 258);
        listView_Dados.TabIndex = 6;
        listView_Dados.UseCompatibleStateImageBehavior = false;
        // 
        // txt_Output
        // 
        txt_Output.Anchor = ((System.Windows.Forms.AnchorStyles)(System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right));
        txt_Output.Font = new System.Drawing.Font("Segoe UI", 12F);
        txt_Output.Location = new System.Drawing.Point(329, 29);
        txt_Output.Name = "txt_Output";
        txt_Output.Size = new System.Drawing.Size(437, 22);
        txt_Output.TabIndex = 7;
        txt_Output.Text = "Dados";
        // 
        // txt_Copyright
        // 
        txt_Copyright.Anchor = ((System.Windows.Forms.AnchorStyles)(System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left));
        txt_Copyright.Location = new System.Drawing.Point(12, 419);
        txt_Copyright.Name = "txt_Copyright";
        txt_Copyright.Size = new System.Drawing.Size(247, 22);
        txt_Copyright.TabIndex = 8;
        txt_Copyright.Text = "@Copyright Feito Por Mateus (Kyryl Copiou)";
        // 
        // listView_Total_Media
        // 
        listView_Total_Media.Anchor = ((System.Windows.Forms.AnchorStyles)(System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right));
        listView_Total_Media.Location = new System.Drawing.Point(329, 355);
        listView_Total_Media.Name = "listView_Total_Media";
        listView_Total_Media.Size = new System.Drawing.Size(447, 86);
        listView_Total_Media.TabIndex = 9;
        listView_Total_Media.UseCompatibleStateImageBehavior = false;
        // 
        // txt_Total_Media
        // 
        txt_Total_Media.Anchor = ((System.Windows.Forms.AnchorStyles)(System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right));
        txt_Total_Media.Font = new System.Drawing.Font("Segoe UI", 12F);
        txt_Total_Media.Location = new System.Drawing.Point(329, 330);
        txt_Total_Media.Name = "txt_Total_Media";
        txt_Total_Media.Size = new System.Drawing.Size(437, 22);
        txt_Total_Media.TabIndex = 10;
        txt_Total_Media.Text = "Total e Média";
        // 
        // btn_Limpar
        // 
        btn_Limpar.Location = new System.Drawing.Point(39, 211);
        btn_Limpar.Name = "btn_Limpar";
        btn_Limpar.Size = new System.Drawing.Size(220, 47);
        btn_Limpar.TabIndex = 11;
        btn_Limpar.Text = "Limpar dados";
        btn_Limpar.UseVisualStyleBackColor = true;
        // 
        // Form1
        // 
        AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
        AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
        ClientSize = new System.Drawing.Size(800, 456);
        Controls.Add(btn_Limpar);
        Controls.Add(txt_Total_Media);
        Controls.Add(listView_Total_Media);
        Controls.Add(txt_Copyright);
        Controls.Add(txt_Output);
        Controls.Add(listView_Dados);
        Controls.Add(txt_Nota);
        Controls.Add(txtBox_Nota);
        Controls.Add(txtBox_Nome);
        Controls.Add(btn_Calcular);
        Controls.Add(txt_Nome);
        Controls.Add(btn_Inserir);
        Text = "Form1";
        ResumeLayout(false);
        PerformLayout();
    }

    private System.Windows.Forms.Button btn_Limpar;

    private System.Windows.Forms.ListView listView_Total_Media;
    private System.Windows.Forms.Label txt_Total_Media;

    private System.Windows.Forms.Label txt_Copyright;

    private System.Windows.Forms.Label txt_Output;

    private System.Windows.Forms.Button btn_Inserir;
    private System.Windows.Forms.Label txt_Nome;
    private System.Windows.Forms.Button btn_Calcular;
    private System.Windows.Forms.TextBox txtBox_Nome;
    private System.Windows.Forms.TextBox txtBox_Nota;
    private System.Windows.Forms.Label txt_Nota;
    private System.Windows.Forms.ListView listView_Dados;

    #endregion
}