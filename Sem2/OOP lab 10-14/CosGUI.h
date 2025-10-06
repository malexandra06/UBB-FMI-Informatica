#pragma once
#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/qformlayout.h>
#include <qlistwidget.h>
#include "service.h"
#include <qpushbutton.h>
#include <QLineEdit> 
#include <qmessagebox.h>
#include "exception.h"
#include <QRadioButton>
class CosGUI : public QMainWindow, public Observer
{
	Q_OBJECT
public:
	CosGUI(ServiceProd& s, QWidget* parent = nullptr);
	~CosGUI() { service.unregister_observer(this); }

	void update() override {
		loadData();
		actualizeazaButoaneTipuri();
	}
private:
	ServiceProd& service;
	/*void adaugaCos(const string& nume);
    void golesteCos();
    void adaugaRandom(int dim);
    void exportaInCSV(const string& numeFisier);
    void exportaInHTML(const string& numeFisier);*/
	QListWidget* lst = new QListWidget;
	QPushButton* exit_button = new QPushButton;
	QPushButton* add_button = new QPushButton;
	QPushButton* empty_button = new QPushButton;
	QPushButton* random_button = new QPushButton;
	QPushButton* csv_button = new QPushButton;
	QPushButton* html_button = new QPushButton;
	QPushButton* sterge_button = new QPushButton;
	QHBoxLayout* layoutTipuri;
	QFormLayout* form_layout;

	QWidget* main_widget;
	QHBoxLayout* main_layout;
	QLineEdit* input_name = new QLineEdit;
	void loadData();
	void initGUI();
	void initConnect();
	void actualizeazaButoaneTipuri();
	void adaugaProduselst(vector<Produs> v);
};