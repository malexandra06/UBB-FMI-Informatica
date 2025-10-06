#include <CosGUI.h>
CosGUI::CosGUI(ServiceProd& s, QWidget* parent) : QMainWindow(parent), service{ s }
{
    initGUI();
    loadData();
    initConnect();
}
void CosGUI::loadData()
{
    lst->clear();
    for (const Produs& p : service.getAllCos())
    {
        QString itemText = QString("%1 , %2 , %3 , %4")
            .arg(QString::fromStdString(p.getNume()))
            .arg(QString::fromStdString(p.getTip()))
            .arg(QString::fromStdString(p.getProducator()))
            .arg(QString::number(p.getPret()));

        lst->addItem(itemText);
    }
}



void CosGUI::adaugaProduselst(vector<Produs> v)
{
    lst->clear();
    for (const Produs& p : v)
    {
        QString itemText = QString("%1 , %2 , %3 , %4")
            .arg(QString::fromStdString(p.getNume()))
            .arg(QString::fromStdString(p.getTip()))
            .arg(QString::fromStdString(p.getProducator()))
            .arg(QString::number(p.getPret()));

        lst->addItem(itemText);
    }
}
void CosGUI::initConnect()
{
    service.register_observer(this);
    QObject::connect(exit_button, &QPushButton::clicked, this, &QWidget::close);

    QObject::connect(add_button, &QPushButton::clicked, [this]() {
        try {
            service.adaugaCos(input_name->text().toStdString());

            QMessageBox::information(this, "Success","Elementul a fost adaugat in cos!");
        }
        catch (const std::exception& error) {
            QMessageBox::warning(this, "Error", error.what());
        }
        });

    QObject::connect(empty_button, &QPushButton::clicked, [this]()
        {
            service.golesteCos();
        });
    QObject::connect(random_button, &QPushButton::clicked, [this]() {
        QDialog* dialog = new QDialog(this);
        dialog->setWindowTitle("Adaugare random");
        QVBoxLayout* layout = new QVBoxLayout(dialog);

        QLabel* label = new QLabel("Numar produse de adaugat:");
        QLineEdit* numberInput = new QLineEdit;
        QPushButton* confirmButton = new QPushButton("Adauga");

        layout->addWidget(label);
        layout->addWidget(numberInput);
        layout->addWidget(confirmButton);

        QObject::connect(confirmButton, &QPushButton::clicked, [this, dialog, numberInput]() {
            bool ok;
            int nr = numberInput->text().toInt(&ok);
            if (!ok || nr <= 0) {
                QMessageBox::warning(this, "Eroare", "Introdu un numar valid!");
                return;
            }

            try {
                service.adaugaRandom(nr);
                
                dialog->accept();
            }
            catch (const std::exception& e) {
                QMessageBox::warning(this, "Eroare", e.what());
            }
            });

        dialog->exec();
        });

    QObject::connect(html_button, &QPushButton::clicked, [this]()
        {
            service.exportaInHTML("html1.html");
        });
    QObject::connect(csv_button, &QPushButton::clicked, [this]()
        {
            service.exportaInCSV("csv1.csv");
        });

    QObject::connect(sterge_button, &QPushButton::clicked, [this]() {
        QListWidgetItem* selectedItem = lst->currentItem();
        if (!selectedItem) {
            QMessageBox::warning(this, "Eroare", "Selecteaza un produs pentru a-l sterge!");
            return;
        }

        QString itemText = selectedItem->text();  
        QStringList parts = itemText.split(',');

        if (parts.size() >= 1) {
            std::string nume = parts[0].trimmed().toStdString();

                service.stergeCos(nume);  
                QMessageBox::information(this, "Succes", "Produs sters cu succes!");
        }
        });
}


void CosGUI::actualizeazaButoaneTipuri()
{
    if (layoutTipuri) {
        // Șterge butoanele vechi
        QLayoutItem* item;
        while ((item = layoutTipuri->takeAt(0)) != nullptr) {
            delete item->widget();  // șterge butonul din memorie
            delete item;
        }
    }
    else {
        layoutTipuri = new QHBoxLayout;
    }

    map<string, int> tipuri = service.raportTip();

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
void CosGUI::initGUI()
{
    main_widget = new QWidget(this);
    main_layout = new QHBoxLayout(main_widget);
    form_layout = new QFormLayout;


    form_layout->addRow(new QLabel("Nume:"), input_name);
    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addWidget(new QLabel("Lista de produse:"));
    leftLayout->addWidget(lst); // Adauga lista in layout
    

    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->addLayout(form_layout);
    rightLayout->addWidget(add_button);
    rightLayout->addWidget(sterge_button);
    rightLayout->addWidget(random_button);
    rightLayout->addWidget(empty_button);
    rightLayout->addWidget(html_button);
    rightLayout->addWidget(csv_button);
    actualizeazaButoaneTipuri();
    rightLayout->addLayout(layoutTipuri);
    rightLayout->addStretch();
    rightLayout->addWidget(exit_button);
    main_layout->addLayout(leftLayout, 2);
    main_layout->addLayout(rightLayout, 2);

    // Seteaza widget-ul principal
    main_widget->setLayout(main_layout);
    setCentralWidget(main_widget);

    add_button->setText("Adauga");
    sterge_button->setText("Sterge");
    random_button->setText("Adauga Random");
    empty_button->setText("Goleste");
    html_button->setText("Exporta HTML");
    csv_button->setText("Exporta CSV");
    exit_button->setText("Iesire");
}

