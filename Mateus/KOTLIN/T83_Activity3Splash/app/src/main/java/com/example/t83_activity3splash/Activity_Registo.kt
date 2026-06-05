package com.example.t83_activity3splash

import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.t83_activity3splash.databinding.ActivityRegistoBinding

class Activity_Registo : AppCompatActivity() {
    private val binding by lazy { ActivityRegistoBinding.inflate(layoutInflater) }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(binding.root)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        binding.buttonGuardar.setOnClickListener {
            val username = binding.editTextUsername.text.toString()
            val password = binding.editTextPassword.text.toString()

            if (username.isEmpty() || password.isEmpty()) {
                Toast.makeText(this, "Preencha todos os campos", Toast.LENGTH_SHORT).show()
                return@setOnClickListener
            }

            // Guarda as credenciais em SharedPreferences
            val prefs = getSharedPreferences("credenciais", MODE_PRIVATE)
            prefs.edit()
                .putString("username", username)
                .putString("password", password)
                .apply()

            Toast.makeText(this, "Registo efetuado com sucesso!", Toast.LENGTH_SHORT).show()
            finish()
        }
    }
}