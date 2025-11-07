package com.example.t62_3activity

import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.t62_3activity.databinding.ActivityMainBinding

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
        binding.buttonEntrar.setOnClickListener{
            val username = binding.editUser.text.toString()
            val password = binding.editPass.text.toString()
            if((username == "") || (password == "")){
                Toast.makeText(
                    applicationContext,
                    "User e pass têm que ser preenchidos!",
                    Toast.LENGTH_SHORT
                ).show()
            }else{
                if((username == "user") && (password == "pass")){
                    Toast.makeText(
                        applicationContext,
                        "Login Válido",
                        Toast.LENGTH_SHORT).show()
                }else{
                    Toast.makeText(
                        applicationContext,
                        "Login Inválido",
                        Toast.LENGTH_SHORT).show()
                }
            }
        }
    }
}