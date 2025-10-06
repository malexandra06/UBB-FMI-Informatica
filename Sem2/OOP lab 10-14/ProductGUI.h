#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/qformlayout.h>
#include <qtablewidget.h>
#include <qlistwidget.h>
#include "service.h"
#include <qpushbutton.h>
#include <QLineEdit> 
#include <qmessagebox.h>
#include "exception.h"
#include <QRadioButton>
#include "CosGUI.h"
#include "cosReadOnly.h"
#include "list.h"
class ProductGUI : public QMainWindow
{
	Q_OBJECT
public:
	ProductGUI(ServiceProd& s, QWidget* parent = nullptr);
	~ProductGUI()=default;
private:
	ServiceProd& service;
	CosGUI* cos;
	CosReadOnlyGUI* cos_rd;
	//QListWidget* lst = new QListWidget;
	QListView* listView = new QListView;
	Lista* listModel = new Lista;

	QPushButton* exit_button = new QPushButton;
	QPushButton* add_button = new QPushButton;
	QPushButton* remove_button = new QPushButton;
	QPushButton* update_button = new QPushButton;
	QPushButton* search_button = new QPushButton;
	QPushButton* filter_button = new QPushButton;
	QPushButton* sorted_button = new QPushButton;
	QPushButton* cos_button = new QPushButton;
	QPushButton* cos2_button = new QPushButton;
	QPushButton* undo_button = new QPushButton;
	QFormLayout* form_layout;
	QHBoxLayout* layoutTipuri = nullptr;  // layout pentru butoane de tipuri

	QWidget* main_widget;
	QHBoxLayout* main_layout;
	QLineEdit* input_name= new QLineEdit;
	QLineEdit* input_type= new QLineEdit;
	QLineEdit* input_producer= new QLineEdit;
	QLineEdit* input_price= new QLineEdit;
	void loadData();
	void initGUI();
	void initConnect();
	void adaugaProduselst(vector<Produs> v);
	void actualizeazaButoaneTipuri();
};