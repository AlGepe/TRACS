#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>

#include <TH2D.h>

#include "qcustomplot.h"

#include "SMSDetector.h"
#include "Carrier.h"
#include "CarrierCollection.h"

#include "utilities.h"

#include "ui_mainWindow.h"

#include <fstream>
#include <iterator>

extern TH1D *H1DConvolution( TH1D *htct, Double_t Cend=0. ) ; 

namespace Ui {
class MainWindow
;
}

class MainWindow : public QMainWindow
{

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//  extern double Textern;

private slots:

    // potentials tab
    void solve_fem();
    void show_weighting_potential_2d();
    void show_weighting_potential_3d();
    void show_electric_potential_2d();
    void show_electric_potential_3d();
	void plot_custom_neff();

    // fields tab
    void show_w_field_mod_map();
    void show_e_field_mod_map();
    void show_w_field_x_map();
    void show_e_field_x_map();
    void show_w_field_y_map();
    void show_e_field_y_map();
    void show_w_field_mod_3d();
    void show_e_field_mod_3d();
    void show_w_field_x_3d();
    void show_e_field_x_3d();
    void show_w_field_y_3d();
    void show_e_field_y_3d();
    void show_w_field_vert_cut();
    void show_w_field_hor_cut();
    void show_e_field_vert_cut();
    void show_e_field_hor_cut();

    // currents tab
    void drift_single_carrier();
    void drift_line_carrier();
    void show_carrier_map_qcp();
    void show_carrier_map_line();
    void carrier_from_click(QMouseEvent *  event);
//	double capacit_curr;

    // carriers tab
    void set_carrier_filename();
    void load_carrier_collection();
    void drift_carrier_collection();
    void show_gen_carrier_map_qcp();
//	double capacit_carriers;

    // other
    void save_results_raw();



private:
    Ui::MainWindow *ui;
    SMSDetector * detector;
    CarrierCollection * carrier_collection;
    QVector<QVector<double>> raw_results;
    void init_weighting_potential_plot();
    void init_electric_potential_plot();

    void init_simple_currents_plot();
    void init_carrier_map_qcp();

    void init_weighting_field_map_qcp();
    void init_electric_field_map_qcp();
    void init_weighting_field_cut_qcp();
    void init_electric_field_cut_qcp();

    void init_gen_carrier_map_qcp();
    void init_gen_carrier_curr_qcp();

};

#endif // MAINWINDOW_H
