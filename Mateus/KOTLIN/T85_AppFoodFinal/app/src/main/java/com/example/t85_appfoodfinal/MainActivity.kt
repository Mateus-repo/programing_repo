package com.example.t85_appfoodfinal

import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.t85_appfoodfinal.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    private val binding by lazy { ActivityMainBinding.inflate(layoutInflater) }

    // Preços unitários
    private val precoCafe     = 0.80
    private val precoSumo     = 1.50
    private val precoPicanha  = 12.50
    private val precoGelado   = 1.20
    private val precoSopa     = 1.00

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(binding.root)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        binding.buttonEfetuarPedido.setOnClickListener {
            val qtdCafe     = binding.editQtdCafe.text.toString().toIntOrNull() ?: 0
            val qtdSumo     = binding.editQtdSumo.text.toString().toIntOrNull() ?: 0
            val qtdPicanha  = binding.editQtdPicanha.text.toString().toIntOrNull() ?: 0
            val qtdGelado   = binding.editQtdGelado.text.toString().toIntOrNull() ?: 0
            val qtdSopa     = binding.editQtdSopa.text.toString().toIntOrNull() ?: 0

            if (qtdCafe + qtdSumo + qtdPicanha + qtdGelado + qtdSopa == 0) {
                Toast.makeText(this, "Selecione pelo menos um produto!", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            val pedidoLinhas = mutableListOf<String>()
            if (qtdCafe > 0)    pedidoLinhas.add("$qtdCafe café - ${"%.2f".format(qtdCafe * precoCafe)} €")
            if (qtdSumo > 0)    pedidoLinhas.add("$qtdSumo sumo - ${"%.2f".format(qtdSumo * precoSumo)} €")
            if (qtdPicanha > 0) pedidoLinhas.add("$qtdPicanha picanha - ${"%.2f".format(qtdPicanha * precoPicanha)} €")
            if (qtdGelado > 0)  pedidoLinhas.add("$qtdGelado gelado - ${"%.2f".format(qtdGelado * precoGelado)} €")
            if (qtdSopa > 0)    pedidoLinhas.add("$qtdSopa sopa - ${"%.2f".format(qtdSopa * precoSopa)} €")

            val total = qtdCafe * precoCafe + qtdSumo * precoSumo +
                    qtdPicanha * precoPicanha + qtdGelado * precoGelado +
                    qtdSopa * precoSopa

            val i = Intent(this, Activity_Splash::class.java).apply {
                putExtra("PEDIDO", pedidoLinhas.joinToString("\n"))
                putExtra("TOTAL", total)
            }
            startActivity(i)
        }
    }
}