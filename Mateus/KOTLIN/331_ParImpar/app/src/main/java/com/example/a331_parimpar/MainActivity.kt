package com.example.a331_parimpar

import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import com.example.a331_parimpar.databinding.ActivityMainBinding

fun isPrime(number: Int): Boolean {
    if (number <= 1) return false
    if (number == 2) return true
    if (number % 2 == 0) return false

    for (i in 3..Math.sqrt(number.toDouble()).toInt() step 2) {
        if (number % i == 0) return false
    }
    return true
}
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
        binding.buttonSubmeter.setOnClickListener {
            val number = binding.editTextNumber.text.toString().toIntOrNull()
            if (number != null) {
                if (number%2==0) {
                    binding.textViewPar.text = "O número " + number + " é par"
                }else{
                    binding.textViewPar.text = "O número " + number + " é impar"
                }
                if(isPrime(number)){
                    binding.textViewPrimo.text = "O número " + number + " é primo"
                }else{
                    binding.textViewPrimo.text = "O número " + number + " não é primo"
                }
            } else {
                binding.textViewPar.text = ""
                binding.textViewPrimo.text = ""
                Toast.makeText(
                    applicationContext,
                    "Erro!!, não inseriu um número inteiro valido!",
                    Toast.LENGTH_SHORT
                ).show()
            }
        }
    }
}