#pragma once
#pragma once
#pragma once
#include<qtableview.h>
#include "service.h"

using namespace std;
class MyTableModel :public QAbstractTableModel
{
private:
	vector<Building> i;
public:
	MyTableModel(vector<Building> s) :i{ s } {}

	int rowCount(const QModelIndex& parent = QModelIndex())const override { return i.size(); }

	int columnCount(const QModelIndex& parent = QModelIndex())const override { return 4; }

	QVariant data(const QModelIndex& index, int role)const override {//= Qt::DisplayRole
		Building sf = i[index.row()];
		if (role == Qt::DisplayRole)
		{
			if (index.column() == 0)
				return QString::fromStdString(sf.getID());
			else if (index.column() == 1)
				return QString::fromStdString(sf.getDesc());
			else if (index.column() == 2)
				return QString::fromStdString(sf.getArea());
			else if (index.column() == 3)
				return QString::fromStdString(sf.getCoord());
		}
		/*if (role == Qt::FontRole && sf.getStatus() != "revised") {
			QFont font;
			font.setBold(true);
			return font;
		}
		if (role == Qt::BackgroundRole && sf.getStatus() == "revised") {
			return QColor(Qt::green);
		}*/
		return QVariant();
	}

	void setFiles(vector<Building> sf) { this->i = sf; emit layoutChanged(); }

	QVariant headerData(int section, Qt::Orientation orientation, int role)const override {
		if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal)
			{
				if (section == 0)
					return "ID";
				else if (section == 1)
					return "Description";
				else if (section == 2)
					return "Thematic Sector";
				else if (section == 3)
					return "Location";
			}
		}
		return QVariant();
	}
};