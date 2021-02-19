#ifndef IMC_H
#define IMC_H

#include <QMainWindow>
#include "calcularimc.h"
#include <QtCharts>
#include <QBarSet>
#include <QHorizontalPercentBarSeries>

QT_BEGIN_NAMESPACE
namespace Ui { class IMC; }
QT_END_NAMESPACE

class IMC : public QMainWindow
{
    Q_OBJECT
public:
    IMC(QWidget *parent = nullptr);
    ~IMC();
    void guardar();
    void inicializar();
    void abrir();

private slots:

    void on_btnCalcular_clicked();

private:
    Ui::IMC *ui;
    CalcularImc *persona[50];
    int total=0;

    QBarSet *set0;
    QBarSet *set1;
    QBarSet *set2;
    QBarSet *set3;

    QHorizontalPercentBarSeries *series;
    QChart *chart;
    QBarCategoryAxis *categoryAxis;
    QValueAxis *valueAxis;
    QChartView *chartView;
};
#endif // IMC_H
