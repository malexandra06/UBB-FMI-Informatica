#pragma once
#include <QAbstractListModel>
#include "service.h"
#include<vector>
#include <algorithm>
#include<qstringlist.h>
using std::vector;

class Lista : public QAbstractListModel {
	Q_OBJECT

private:
	vector<Produs>produse;

public:
	void setList(const vector<Produs>& list) {
		beginResetModel();
		produse = list;
		endResetModel();
	}
	void addDIS(const Produs& prod) {
		beginInsertRows(QModelIndex(), rowCount(), rowCount());
		produse.push_back(prod);
		endInsertRows();
	}

	void removeDIS(int index) {
		if (index < 0 or index >= produse.size()) return;
		beginRemoveRows(QModelIndex(), index, index);
		produse.erase(produse.begin() + index);
		endRemoveRows();
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		Q_UNUSED(parent);
		return static_cast<int>(produse.size());
	}
	QVariant data(const QModelIndex& index, int role) const override {
		if (!index.isValid()) return QVariant();

		const Produs& prod = produse.at(index.row());

		if (role == Qt::DisplayRole) {
			return QString::fromStdString("Nume: " + prod.getNume() +
				", Tip: " + prod.getTip() +
				", Producator: " + prod.getProducator() +
				", Pret: " + std::to_string(prod.getPret()));
		}

		return QVariant();
	}

};