#pragma once
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QImage>
#include <QRandomGenerator>
#include "service.h"

class CosReadOnlyGUI : public QWidget, public Observer {
    Q_OBJECT
public:
    CosReadOnlyGUI(ServiceProd& service, QWidget* parent = nullptr);
    ~CosReadOnlyGUI();

    void update() override; // Din Observer
    void paintEvent(QPaintEvent* ev) override;

private:
    ServiceProd& service;
    QVector<QPoint> positions; // Poziții random pentru figuri
    QVector<QColor> colors;    // Culori random pentru figuri
    QImage image;              // Imagine opțională

    void generateRandomElements();
};