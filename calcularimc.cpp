#include "calcularimc.h"
#include <math.h>


float CalcularImc::peso() const
{
    return m_peso;
}

float CalcularImc::altura() const
{
    return m_altura;
}

float CalcularImc::imc() const
{
    return m_imc;
}

QString CalcularImc::fecha() const
{
    return m_fecha;
}

QString CalcularImc::estado() const
{
    return m_estado;
}

CalcularImc::CalcularImc(QObject *parent) : QObject(parent)
{

}

CalcularImc::CalcularImc(QString fecha, float peso, float altura)
{
    this->m_peso = peso;
    this->m_altura = altura;
    this->m_fecha = fecha;
}

void CalcularImc::calcular()
{
    m_imc = m_peso / (pow(m_altura,2));

    if(m_imc >= 0 && m_imc <18.5){
        m_estado = "Peso inferior al normal";
    }else if(m_imc >= 18.5 && m_imc <= 24.9){
        m_estado = "Normal";
    }else if(m_imc >= 25 && m_imc <= 29.9){
        m_estado = "Peso superior al normal";
    }else if(m_imc >= 30){
        m_estado = "Obesidad";
    }

}
