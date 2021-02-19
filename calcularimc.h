#ifndef CALCULARIMC_H
#define CALCULARIMC_H

#include <QObject>

class CalcularImc : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float peso READ peso)
    Q_PROPERTY(float altura READ altura)
    Q_PROPERTY(float imc READ imc)
private:
    float m_peso;
    float m_altura;
    float m_imc;
    QString m_fecha;
    QString m_estado;
public:
    explicit CalcularImc(QObject *parent = nullptr);
    CalcularImc(QString fecha, float peso, float altura);
    void calcular();


    float peso() const;
    float altura() const;
    float imc() const;
    QString fecha() const;

    QString estado() const;

signals:

};

#endif // CALCULARIMC_H
