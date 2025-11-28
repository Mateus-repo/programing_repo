package com.example.t81_ex1_dadospessoais

import android.os.Bundle
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.t81_ex1_dadospessoais.databinding.ActivityShowDataBinding

class Activity_ShowData : AppCompatActivity() {
    private val binding by lazy { ActivityShowDataBinding.inflate(layoutInflater) }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(binding.root)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }
        val nome = intent.getStringExtra("NOME") ?: ""
        val morada = intent.getStringExtra("MORADA") ?: ""
        val telefone = intent.getStringExtra("TELEFONE") ?: ""
        val email = intent.getStringExtra("EMAIL") ?: ""
        val genero = intent.getStringExtra("GENERO") ?: ""
        val artigo = if (genero == "Masculino") "O" else "A"
        binding.textViewResultado.text = artigo + " " + nome + " mora na " + morada + ", tem o numero " + telefone + " e o email " + email
        binding.buttonVoltar.setOnClickListener {
            finish()
        }
    }
}