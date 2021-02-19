#include "imc.h"
#include "ui_imc.h"
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QMessageBox>

IMC::IMC(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IMC)
{
    ui->setupUi(this);
    inicializar();
    abrir();
}

IMC::~IMC()
{
    delete ui;
}

void IMC::guardar()
{
    QString fecha;
    float peso[50];
    float altura[50];
    float imc[50];

    QDate date;
    fecha = date.currentDate().toString("dd/MM/yyyy");

    for(int i=0; i<total; i++){
        peso[i] = persona[i]->peso();
        altura[i] = persona[i]->altura();
        persona[i]->calcular();
        imc[i] = persona[i]->imc();
    }
    QString pes[50];
    QString alt[50];
    QString im[50];
    for(int i=0; i<total; i++){
        pes[i] = QString::number(persona[i]->peso(), 'f', 2);
        alt[i] = QString::number(persona[i]->altura(), 'f', 2);
        persona[i]->calcular();
        im[i] = QString::number(persona[i]->imc(), 'f', 2);
    }
    QString file = QDir::currentPath() + "/michael.csv";
    QFile archivo(file);
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        //Crear el objeto QTextStream
        for(int i=0; i<total; i++){
            QTextStream out(&archivo);
            //Escribiendo datos en el archico
            out << fecha << ";" << peso[i] << ";" << altura[i] << ";" << imc[i] << "\n";

        }
        qDebug() << "Archivo almacenado en:" << QDir::currentPath();
        //Cerrar archico
        archivo.close();
    }
}

void IMC::inicializar()
{
    QStringList cabecera = {"Fecha", "Peso", "Altura", "IMC"};
    ui->outRegistro->setColumnCount(4);
    ui->outRegistro->setHorizontalHeaderLabels(cabecera);
}

void IMC::abrir()
{
    QString nombre = QDir::currentPath() + "/michael.csv";

    QFile file(nombre);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QStringList datos;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString linea = in.readLine();
        datos << linea;
    }
    QStringList partes[50];
    for(int i=0; i<datos.size(); i++){
        partes[i]= datos[i].split(";");
    }
    for(int i=0; i<datos.size(); i++){

        ui->outRegistro->insertRow(i);

        ui->outRegistro->setItem(i,0, new QTableWidgetItem(partes[i][0]));
        ui->outRegistro->setItem(i,1, new QTableWidgetItem(partes[i][1]));
        ui->outRegistro->setItem(i,2, new QTableWidgetItem(partes[i][2]));
        ui->outRegistro->setItem(i,3, new QTableWidgetItem(partes[i][3]));

        int indice = total;
        persona[indice] = new CalcularImc(partes[i][0],partes[i][1].toFloat(),partes[i][2].toFloat());
        this->total++;

    }

    file.close();

}


void IMC::on_btnCalcular_clicked()
{
    float peso = ui->inPeso->value();
    float altura = ui->inAltura->value();
    float imc;
    float mayor = 0;
    float menor;
    QString estado;

    QDate fecha;
    QString date = fecha.currentDate().toString("dd/MM/yyyy");

    int indice = total;
    persona[indice] = new CalcularImc(date, peso, altura);
    this->total++;
    persona[indice]->calcular();
    imc = persona[indice]->imc();
    estado = persona[indice]->estado();
    QString actual = QString::number(peso,'f',2);
    QString ind = QString::number(imc,'f',2);
    ui->outPactual->setText(actual + " Kg");
    ui->outIndice->setText(ind);
    ui->outEstado->setText(estado);

    for(int i=0; i<total; i++){
        menor = persona[0]->peso();
        float pes = persona[i]->peso();
        if(pes > mayor){
            mayor = pes;
        }
    }
    for(int i=0; i<total; i++){
        menor = persona[0]->peso();
        float men = persona[i]->peso();
        if(menor > men){
            menor = men;
        }
    }
    QString max = QString::number(mayor, 'f', 2);
    ui->outPmax->setText(max + " Kg");
    QString min = QString::number(menor, 'f', 2);
    ui->outPmin->setText(min + " Kg");

     ui->outRegistro->setRowCount(0);
    for(int i=0; i<total; i++){
        persona[i]->calcular();
        int posicion = ui->outRegistro->rowCount();
        ui->outRegistro->insertRow(posicion);
        ui->outRegistro->setItem(posicion,0,new QTableWidgetItem(date));
        ui->outRegistro->setItem(posicion,1,new QTableWidgetItem(QString::number(persona[i]->peso())));
        ui->outRegistro->setItem(posicion,2,new QTableWidgetItem(QString::number(persona[i]->altura())));
        ui->outRegistro->setItem(posicion,3,new QTableWidgetItem(QString::number(persona[i]->imc())));
    }

    //Grafico
    series = new QHorizontalPercentBarSeries();
    set0 = new QBarSet("Peso inferior al normal");
    set1 = new QBarSet("Normal");
    set2 = new QBarSet("Peso superior al normal");
    set3 = new QBarSet("Obesidad");

    *set0 << 18.5;
    *set1 << 6.4;
    *set2 << 4.9;
    *set3 << 70;

    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);

    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Rango del Indice de Masa Corporal");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categorias;
    categorias << "Rango";
    categoryAxis = new QBarCategoryAxis;
    categoryAxis->append(categorias);

    chart->createDefaultAxes();
    chart->setAxisY(categoryAxis,series);

    chart->addAxis(categoryAxis, Qt::AlignLeft);
    series->attachAxis(categoryAxis);
    valueAxis = new QValueAxis();
    chart->addAxis(valueAxis, Qt::AlignBottom);
    series->attachAxis(valueAxis);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setParent(ui->horizontalFrame);

    guardar();

    qDebug() << mayor;
}
