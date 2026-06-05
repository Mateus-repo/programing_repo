package com.example.t82_ex2_activity3calculo

import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.t82_ex2_activity3calculo.databinding.ActivityMainBinding

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

        binding.buttonOK.setOnClickListener {
            val numero1 = binding.editTextNumero1.text.toString()
            if (numero1.isEmpty()) {
                Toast.makeText(this, "Por favor insira um número", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }
            val i = Intent(this, Activity_Numero2::class.java).apply {
                putExtra("NUMERO1", numero1)
            }
            startActivity(i)
        }
    }
}