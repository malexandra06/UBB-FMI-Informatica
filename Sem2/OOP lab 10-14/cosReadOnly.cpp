#include "cosReadOnly.h"

CosReadOnlyGUI::CosReadOnlyGUI(ServiceProd& service, QWidget* parent): QWidget(parent), service(service) {
    service.register_observer(this);
    image.load("im.jpg"); // Încarcă o imagine din resurse
    generateRandomElements();
    setMinimumSize(400, 300);
}

CosReadOnlyGUI::~CosReadOnlyGUI() {
    service.unregister_observer(this);
}

void CosReadOnlyGUI::update() {
    generateRandomElements();
    repaint(); 
}

void CosReadOnlyGUI::generateRandomElements() {
    positions.clear();
    colors.clear();

    int count = service.getAllCos().size();
    QRandomGenerator* rand = QRandomGenerator::global();

    for (int i = 0; i < count; ++i) {
        // Generează poziții random în limitele ferestrei
        int x = rand->bounded(width() - 50);
        int y = rand->bounded(height() - 50);
        positions.append(QPoint(x, y));

        // Generează culori random
        colors.append(QColor(
            rand->bounded(256),
            rand->bounded(256),
            rand->bounded(256)
        ));
    }
}

void CosReadOnlyGUI::paintEvent(QPaintEvent* ev) {
    QPainter painter(this);

    // Desenează fundalul
    painter.fillRect(rect(), Qt::white);

    // Desenează imaginea de fundal (opțional)
    if (!image.isNull()) {
        painter.drawImage(0, 0, image.scaled(size(), Qt::KeepAspectRatioByExpanding));
    }

    // Desenează figuri pentru fiecare element din cos
    for (int i = 0; i < positions.size(); ++i) {
        painter.setBrush(colors[i]);
        painter.setPen(Qt::black);

        // Alegeți una sau alternați între forme:
        switch (i % 4) {
        case 0:
            painter.drawEllipse(positions[i], 20, 20); // Cerc
            break;
        case 1:
            painter.drawRect(positions[i].x(), positions[i].y(), 40, 40); // Pătrat
            break;
        case 2:
            painter.drawRoundedRect(positions[i].x(), positions[i].y(), 40, 30, 10, 10); // Dreptunghi rotunjit
            break;
        case 3:
            painter.drawPie(positions[i].x(), positions[i].y(), 40, 40, 0, 180 * 16); // Semi-cerc
            break;
        }

        // Desenează numărul produsului (opțional)
        painter.drawText(positions[i], QString::number(i + 1));
    }
}