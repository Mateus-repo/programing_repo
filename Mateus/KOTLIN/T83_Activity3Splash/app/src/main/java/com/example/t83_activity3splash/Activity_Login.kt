package com.example.t83_activity3splash

import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.t83_activity3splash.databinding.ActivityLoginBinding

class Activity_Login : AppCompatActivity() {
    private val binding by lazy { ActivityLoginBinding.inflate(layoutInflater) }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        setContentView(binding.root)
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main)) { v, insets ->
            val systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars())
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom)
            insets
        }

        binding.buttonLogin.setOnClickListener {
            val username = binding.editTextUsername.text.toString()
            val password = binding.editTextPassword.text.toString()

            val prefs = getSharedPreferences("credenciais", MODE_PRIVATE)
            val userGuardado = prefs.getString("username", "")
            val passGuardada = prefs.getString("password", "")

            if (username == userGuardado && password == passGuardada) {
                startActivity(Intent(this, Activity_Sobre::class.java))
                finish()
            } else {
                Toast.makeText(this, "Username ou password incorretos!", Toast.LENGTH_SHORT).show()
                binding.editTextUsername.text.clear()
                binding.editTextPassword.text.clear()
            }
        }
    }
}