package com.example.a43_linearlayoutconverterall

import android.os.Bundle
import android.widget.Toast
import androidx.activity.enableEdgeToEdge
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.ViewCompat
import androidx.core.view.WindowInsetsCompat
import kotlin.getValue
import com.example.a43_linearlayoutconverterall.databinding.ActivityMainBinding
import kotlin.text.clear
import kotlin.toString


class MainActivity : AppCompatActivity() {

    fun showCal(amountEuro: Double, name: String) : Double{
        if(amountEuro==null){
            return -1.0
        }
        return when (name) {
            "Dolar" -> amountEuro * 1.16
            "Real" -> amountEuro * 6.22
            "Peso" -> amountEuro * 21.45
            else -> -1.0
        }
    }
    fun erroInputNum(){
        binding.textResultado.text = ""
        Toast.makeText(
            applicationContext,
            "Erro!!, não inseriu um número válido!",
            Toast.LENGTH_SHORT
        ).show()
    }
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
        binding.buttonConverterDolar.setOnClickListener {
            binding.textResultado.text = ""

            val number = binding.editEuro.text.toString().toDoubleOrNull()
            if (number != null) {
                binding.textResultado.text = "${String.format("%.2f", number)} euros é igual a aproximadamente ${String.format("%.2f", showCal(number, "Dolar"))} dolares."
            } else {
                erroInputNum();
            }
        }
        binding.buttonConverterReal.setOnClickListener {
            binding.textResultado.text = ""

            val number = binding.editEuro.text.toString().toDoubleOrNull()
            if (number != null) {
                binding.textResultado.text = "${String.format("%.2f", number)} euros é igual a aproximadamente ${String.format("%.2f", showCal(number, "Real"))} reais."
            } else {
                erroInputNum();
            }
        }
        binding.buttonConverterPeso.setOnClickListener {
            binding.textResultado.text = ""

            val number = binding.editEuro.text.toString().toDoubleOrNull()
            if (number != null) {
                binding.textResultado.text = "${String.format("%.2f", number)} euros é igual a aproximadamente ${String.format("%.2f", showCal(number, "Peso"))} pesos."
            } else {
                erroInputNum();
            }
        }
        binding.buttonDelete.setOnClickListener {
            binding.editEuro.text.clear()
            binding.textResultado.text = ""
            Toast.makeText(
                applicationContext,
                "Limpo!",
                Toast.LENGTH_SHORT
            ).show()
        }
    }
}