package com.example.t84_appfood

import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.t84_appfood.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    private val binding by lazy { ActivityMainBinding.inflate(layoutInflater) }

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
            val pedido = mutableListOf<String>()

            if (binding.checkBoxCafe.isChecked)      pedido.add("1 café")
            if (binding.checkBoxSumo.isChecked)      pedido.add("1 sumo")
            if (binding.checkBoxPicanha.isChecked) pedido.add("1 picanha")
            if (binding.checkBoxGelado.isChecked)    pedido.add("1 gelado")
            if (binding.checkBoxSopa.isChecked)      pedido.add("1 sopa")

            if (pedido.isEmpty()) {
                Toast.makeText(this, "Selecione pelo menos um produto!", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            val i = Intent(this, Activity_Splash::class.java).apply {
                putExtra("PEDIDO", pedido.joinToString(", "))
            }
            startActivity(i)
        }
    }
}