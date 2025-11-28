package com.example.t81_ex1_dadospessoais

import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.t81_ex1_dadospessoais.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    private val binding by lazy { ActivityMainBinding.inflate(layoutInflater)}

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(binding.root)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        binding.buttonEnviar.setOnClickListener {
            enviarDados()
        }
    }

    private fun enviarDados() {
        val nome = binding.editTextNome.text.toString()
        val morada = binding.editTextMorada.text.toString()
        val telefone = binding.editTextTelefone.text.toString()
        val email = binding.editTextEmail.text.toString()
        val nome2 = "Hello";
        val genero = when (binding.radioGroupGenero.checkedRadioButtonId) {
            R.id.radioMasculino -> "Masculino"
            R.id.radioFeminino -> "Feminino"
            else -> ""
        }
        if (nome.isEmpty() || morada.isEmpty() || telefone.isEmpty() ||
            email.isEmpty() || genero.isEmpty()) {
            Toast.makeText(this, "Por favor, preencha todos os campos", Toast.LENGTH_SHORT).show()
            return
        }
        val i = Intent(this, Activity_ShowData::class.java).apply {
            putExtra("NOME", nome2)
            putExtra("MORADA", morada)
            putExtra("TELEFONE", telefone)
            putExtra("EMAIL", email)
            putExtra("GENERO", genero)
        }
        startActivity(i)
    }
}