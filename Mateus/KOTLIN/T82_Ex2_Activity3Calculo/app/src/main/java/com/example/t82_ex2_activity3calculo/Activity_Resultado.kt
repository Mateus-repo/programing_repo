package com.example.t82_ex2_activity3calculo

import android.os.Bundle
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.t82_ex2_activity3calculo.databinding.ActivityResultadoBinding
import kotlin.text.*

class Activity_Resultado : AppCompatActivity() {
    private val binding by lazy { ActivityResultadoBinding.inflate(layoutInflater) }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(binding.root)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val n1 = intent.getStringExtra("NUMERO1")?.replace(",", ".")?.toDouble() ?: 0.0
        val n2 = intent.getStringExtra("NUMERO2")?.replace(",", ".")?.toDouble() ?: 0.0

        val n1Int = n1.toInt()
        val n2Int = n2.toInt()

        binding.textViewSoma.text      = "$n1Int+$n2Int=${n1Int + n2Int}"
        binding.textViewDiferenca.text = "$n1Int-$n2Int=${n1Int - n2Int}"
        binding.textViewProduto.text   = "$n1Int*$n2Int=${n1Int * n2Int}"
        binding.textViewDivisao.text   = if (n2Int != 0)
            "$n1Int/$n2Int=${"%.2f".format(n1.div(n2))}"
        else
            "$n1Int/$n2Int=Erro (divisão por zero)"

        binding.buttonVoltar.setOnClickListener {
            finish()
        }
    }
}