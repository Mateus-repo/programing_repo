package com.example.t82_ex2_activity3calculo

import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.t82_ex2_activity3calculo.databinding.ActivityNumero2Binding

class Activity_Numero2 : AppCompatActivity() {
    private val binding by lazy { ActivityNumero2Binding.inflate(layoutInflater) }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(binding.root)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        val numero1 = intent.getStringExtra("NUMERO1") ?: ""

        binding.buttonOK.setOnClickListener {
            val numero2 = binding.editTextNumero2.text.toString()
            if (numero2.isEmpty()) {
                Toast.makeText(this, "Por favor insira um número", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            val i = Intent(this, Activity_Resultado::class.java).apply {
                putExtra("NUMERO1", numero1)
                putExtra("NUMERO2", numero2)
            }
            startActivity(i)
        }
    }
}