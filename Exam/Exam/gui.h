#pragma once
#pragma once
#include "service.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include<QtWidgets/qboxlayout.h>
#include <QtWidgets\qformlayout.h>
#include <qmessagebox.h>
#include <QString>
#include <QLabel>
#include <windows.h>
#include <shellapi.h>
#include <QShortcut>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QMainWindow>
#include <QTableView>
#include "MyTableModel.h"
#include <qsortfilterproxymodel.h>
class EtWindow : public QWidget, public Observer {
private:
	QTableView* tabel = new QTableView;
	Service& s;
	MyTableModel* model = new MyTableModel{ s.getSVB() };
	QHBoxLayout* ly = new QHBoxLayout;
	QColor col;
	string name;
	string area;
public:
	EtWindow(Service& s1, string a, string b) :s{ s1 } 
	{ s.addObs(this); this->name = a; this->area = b; setWindowTitle(QString::fromStdString(a)); setComp(); this->update();
	QPalette pal = this->palette();
	//qsrand(time(0));
	col = QColor(qrand() % 255, qrand() % 255, qrand() % 255);
	pal.setColor(QPalette::Window,col );
	this->setPalette(pal);
	}
	void update() override {
		model->setFiles(s.getSVB());
		tabel->setModel(model);
	}
	void setComp() {
		setLayout(ly); ly->addWidget(tabel);
	};
};


class GUI :public QWidget {
private:
	QTableView* tabel = new QTableView;
	Service& s;
	MyTableModel* model = new MyTableModel{ s.getSVB() };
public:
	GUI(Service& s1) : s{ s1 } {
		vector<Ethnologist> v = this->s.getSVE();
		for (auto it : v) {

			EtWindow* a = new EtWindow(s, it.getName(), it.getArea());
			//s.addObs(a);
			a->resize(1000, 300);
			a->show();
		}
	}
};