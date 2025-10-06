#include "ProductGUI.h"
ProductGUI::ProductGUI(ServiceProd& s, QWidget* parent) : QMainWindow(parent), service{ s }
{
	initGUI();
	loadData();
	initConnect();
}
void ProductGUI::loadData()
{
    listModel->setList(service.getAll());
}


void ProductGUI::adaugaProduselst(vector<Produs> v)
{
    listModel->setList(v);
}
void ProductGUI::initConnect()
{
    QObject::connect(exit_button, &QPushButton::clicked, []() {
        qApp->quit();
        });
    QObject::connect(add_button, &QPushButton::clicked, [this]() {
        try {
            service.adauga(input_name->text().toStdString(), input_type->text().toStdString(),
                input_producer->text().toStdString(), input_price->text().toInt());

            QMessageBox::information(this, "Succes", "Elementul a fost adaugat!");
        }
        catch (const std::exception& error) {
            QMessageBox::warning(this, "Error", error.what());
        }
        loadData();
        actualizeazaButoaneTipuri();
        });

    QObject::connect(remove_button, &QPushButton::clicked, [this]()
        {
            auto nume = input_name->text().toStdString();
            if (nume.empty()) {
                QMessageBox::information(this, "Ceva nu a mers bine!", "Introduceti numele produsului pe care doriti sa il stergeti!");
                return;
            }

            try {
                this->service.sterge(nume);
                QMessageBox::information(this, "Succes", "Elementul a fost sters!");
            }
            catch (const RepoProduseException& e) {
                QMessageBox::warning(this, "Error", e.what());
            }
            loadData();
            actualizeazaButoaneTipuri();
        });
    QObject::connect(update_button, &QPushButton::clicked, [this]() {
        try {
            service.modifica(input_type->text().toStdString(),
                input_producer->text().toStdString(), input_price->text().toInt(), input_name->text().toStdString());
            QMessageBox::information(this, "Succes", "Elementul a fost modificat!");
        }
        catch (const std::exception& error) {
            QMessageBox::warning(this, "Error", error.what());
        }
        loadData();
        actualizeazaButoaneTipuri();
        });

    QObject::connect(search_button, &QPushButton::clicked, [this]() {
        try {
            int p = service.find(input_name->text().toStdString());
            Produs pr = service.getAll()[p];

            std::vector<Produs> rezultat{ pr };
            listModel->setList(rezultat);
        }
        catch (ServiceException& exceptie) {
            QMessageBox::warning(this, "Atentie!", QString::fromStdString(exceptie.what()));
        }
        });



    QObject::connect(cos_button, &QPushButton::clicked, [this]() {
        cos = new CosGUI(service);
        cos->show();
        });

    QObject::connect(cos2_button, &QPushButton::clicked, [this]() {
        cos_rd = new CosReadOnlyGUI(service);
        cos_rd->show();
        });



    QObject::connect(sorted_button, &QPushButton::clicked, [this]() {
        QDialog* dialogSortare = new QDialog(this);
        QVBoxLayout* layoutDialog = new QVBoxLayout(dialogSortare);
        QPushButton* dialogButton = new QPushButton{ "Sorteaza" };
        QRadioButton* option1 = new QRadioButton{ "Nume" };
        QRadioButton* option2 = new QRadioButton{ "Pret" };
        QRadioButton* option3 = new QRadioButton{ "Nume+Tip" };
        layoutDialog->addWidget(option1);
        layoutDialog->addWidget(option2);
        layoutDialog->addWidget(option3);
        layoutDialog->addWidget(dialogButton);
        QObject::connect(dialogButton, &QPushButton::clicked, [this, option1, option2, option3, dialogSortare]() {
            if (option1->isChecked())
            {
                adaugaProduselst(service.sortare(CriteriuSortare::NUME_S));
                dialogSortare->accept();
            }
            else if (option2->isChecked())
            {
                adaugaProduselst(service.sortare(CriteriuSortare::PRET));
                dialogSortare->accept();
            }
            else if (option3->isChecked())
            {
                adaugaProduselst(service.sortare(CriteriuSortare::NUME_TIP));
                dialogSortare->accept();
            }
            else {
                QMessageBox::warning(nullptr, "Date insuficiente", "Nu ati bifat o optiune de sortare!");
            }
            });
        dialogSortare->show();
        });
    QObject::connect(filter_button, &QPushButton::clicked, [this]() {
        QDialog* dialogFiltrare = new QDialog(this);
        QVBoxLayout* layoutDialog = new QVBoxLayout(dialogFiltrare);
        QPushButton* dialogButton = new QPushButton{ "&Filtreaza" };
        QRadioButton* option1 = new QRadioButton{ "&Nume" };
        QLineEdit* name = new QLineEdit;
        QRadioButton* option2 = new QRadioButton{ "&Tip" };
        QLineEdit* tip = new QLineEdit;
        QRadioButton* option3 = new QRadioButton{ "&Producator" };
        QLineEdit* producator = new QLineEdit;
        QRadioButton* option4 = new QRadioButton{ "&Pret" };
        QLineEdit* pret = new QLineEdit;

        QHBoxLayout* nameLayout = new QHBoxLayout();
        nameLayout->addWidget(option1);
        nameLayout->addWidget(name);
        QHBoxLayout* typeLayout = new QHBoxLayout();
        nameLayout->addWidget(option2);
        nameLayout->addWidget(tip);

        QHBoxLayout* producerLayout = new QHBoxLayout();
        nameLayout->addWidget(option3);
        nameLayout->addWidget(producator);

        QHBoxLayout* priceLayout = new QHBoxLayout();
        nameLayout->addWidget(option4);
        nameLayout->addWidget(pret);

        layoutDialog->addLayout(nameLayout);
        layoutDialog->addLayout(typeLayout);
        layoutDialog->addLayout(producerLayout);
        layoutDialog->addLayout(priceLayout);
        layoutDialog->addWidget(dialogButton);

        QObject::connect(dialogButton, &QPushButton::clicked, [this, option1, option2, option3, option4,
            name, tip, producator, pret, dialogFiltrare]() {
                if (option1->isChecked())
                {
                    if (!name->text().isEmpty())
                    {
                        adaugaProduselst(service.filtrare(Criteriu::NUME, name->text().toStdString()));
                        dialogFiltrare->accept();
                    }
                    else
                        QMessageBox::warning(this, "Atentie!", "Introduceti un nume!");
                }
                else if (option2->isChecked())
                {
                    if (!tip->text().isEmpty())
                    {
                        adaugaProduselst(service.filtrare(Criteriu::TIP, tip->text().toStdString()));
                        dialogFiltrare->accept();
                    }
                    else
                        QMessageBox::warning(this, "Atentie!", "Introduceti un tip!");
                }
                else if (option3->isChecked())
                {
                    if (!producator->text().isEmpty())
                    {
                        adaugaProduselst(service.filtrare(Criteriu::PRODUCATOR, producator->text().toStdString()));
                        dialogFiltrare->accept();
                    }
                    else
                        QMessageBox::warning(this, "Atentie!", "Introduceti un producator!");
                }
                else if (option4->isChecked()) {
                    bool ok;
                    int pretInt = pret->text().toInt(&ok);
                    if (ok) {
                        adaugaProduselst(service.filtrarePret(pretInt));
                        dialogFiltrare->accept();
                    }
                    else {
                        QMessageBox::warning(this, "Atentie!", "Introduceti un pret valid!");
                    }
                }
                else {
                    QMessageBox::warning(this, "Atentie!", "Nu ati selectat un criteriu de filtrare!");
                }
            });
        dialogFiltrare->show();
        });
    QObject::connect(undo_button, &QPushButton::clicked, [this]() {
        try {
            service.undo();
        }
        catch (const std::exception& error) {
            QMessageBox::warning(this, "Error", error.what());
        }
        loadData();
        actualizeazaButoaneTipuri();
        });
}

void ProductGUI::actualizeazaButoaneTipuri()
{
    if (layoutTipuri) {
        QLayoutItem* item;
        while ((item = layoutTipuri->takeAt(0)) != nullptr) {
            delete item->widget();  
            delete item;
        }
    }
    else {
        layoutTipuri = new QHBoxLayout;
    }

    map<string, int> tipuri = service.raportTipProduse();

    for (const auto& p : tipuri)
    {
        QString tipText = QString::fromStdString(p.first);
        QString info = QString::number(p.second);
        QString btnText = "Tip: " + tipText;
        QPushButton* btn = new QPushButton(btnText);
        layoutTipuri->addWidget(btn);

        QObject::connect(btn, &QPushButton::clicked, [btnText, info]() {
            QMessageBox::information(nullptr, btnText, "Numar produse: " + info);
            });
    }
}

void ProductGUI::initGUI()
{
    main_widget = new QWidget(this);
    main_layout = new QHBoxLayout(main_widget);
    form_layout = new QFormLayout;
    



    form_layout->addRow(new QLabel("Nume:"), input_name);
    form_layout->addRow(new QLabel("Tip:"), input_type);
    form_layout->addRow(new QLabel("Producator:"), input_producer);
    form_layout->addRow(new QLabel("Pret:"), input_price);
    
    // Layout pentru partea stanga (lista + formular)

    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addWidget(new QLabel("Produse:"));
    listView->setModel(listModel);

    leftLayout->addWidget(listView);

   // leftLayout->addLayout(form_layout); // Adauga formularul

    // Layout pentru partea dreapta (butoane)
    QHBoxLayout* buttonsLayout1 = new QHBoxLayout();
    QHBoxLayout* buttonsLayout2 = new QHBoxLayout();
    buttonsLayout1->addWidget(add_button);
    buttonsLayout1->addWidget(remove_button);
    buttonsLayout1->addWidget(update_button);
    buttonsLayout1->addWidget(undo_button);
    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->addLayout(form_layout);
    rightLayout->addLayout(buttonsLayout1);
    buttonsLayout2->addWidget(filter_button);
    buttonsLayout2->addWidget(sorted_button);
    buttonsLayout2->addWidget(search_button);
    rightLayout->addLayout(buttonsLayout2);
    rightLayout->addWidget(cos_button);
    rightLayout->addWidget(cos2_button);
    actualizeazaButoaneTipuri();

    rightLayout->addLayout(layoutTipuri);
    rightLayout->addStretch();
    rightLayout->addWidget(exit_button);
    main_layout->addLayout(leftLayout);
    main_layout->addLayout(rightLayout);
    // Seteaza widget-ul principal
    main_widget->setLayout(main_layout);
    setCentralWidget(main_widget);

    add_button->setText("Adauga");
    remove_button->setText("Sterge");
    update_button->setText("Actualizeaza");
    search_button->setText("Cauta");
    filter_button->setText("Filtreaza");
    sorted_button->setText("Sorteaza");
    cos_button->setText("Afiseaza Cos");
    cos2_button->setText("Cos Read Only");
    undo_button->setText("Undo");
    exit_button->setText("Iesire");
}