package com.example.t85_appfoodfinal

import android.content.Intent
import android.os.Bundle
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.t85_appfoodfinal.databinding.ActivityPedidoBinding

class Activity_Pedido : AppCompatActivity() {
    private val binding by lazy { ActivityPedidoBinding.inflate(layoutInflater) }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(binding.root)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val pedido = intent.getStringExtra("PEDIDO") ?: ""
        val total  = intent.getDoubleExtra("TOTAL", 0.0)

        binding.textViewPedido.text = pedido
        binding.textViewTotal.text  = "Total: ${"%.2f".format(total)} €"

        binding.buttonVoltar.setOnClickListener {
            val i = Intent(this, MainActivity::class.java)
            i.flags = Intent.FLAG_ACTIVITY_CLEAR_TOP
            startActivity(i)
        }
    }
}