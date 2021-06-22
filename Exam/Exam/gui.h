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
	MyTableModel* model;
	QHBoxLayout* ly = new QHBoxLayout;
	QColor col;
	string name;
	string area;
public:
	EtWindow(Service& s1, string a, string b) :s{ s1 } 
	{	s.addObs(this); 
		this->name = a; 
		this->area = b; 
		setWindowTitle(QString::fromStdString(a)); 
		this->model= new MyTableModel{ s.getSVB(),this->area }; 
		setComp(); 
		this->update();
		QPalette pal = this->palette();
		col = QColor(qrand() % 255, qrand() % 255, qrand() % 255);
		pal.setColor(QPalette::Window,col );
		this->setPalette(pal);
	}
	void update() override {

		model->setFiles(s.sortare(area));
		tabel->setModel(model);
	}
	void setComp() {
		setLayout(ly); ly->addWidget(tabel);
		
		QVBoxLayout* vl1 = new QVBoxLayout();
		QHBoxLayout* hl1 = new QHBoxLayout();
		QLabel* li = new QLabel("Id: ");
		QLabel* ld = new QLabel("Description: ");
		QLabel* lc = new QLabel("Location(capital letters, space as delimiter): ");
		QLineEdit* de = new QLineEdit();
		QLineEdit* id = new QLineEdit();
		QLineEdit* loc = new QLineEdit();
		QPushButton* add = new QPushButton("Add");
		vl1->addWidget(li); vl1->addWidget(id);vl1->addWidget(ld); vl1->addWidget(de); vl1->addWidget(lc); vl1->addWidget(loc);
		hl1->addLayout(vl1);
		hl1->addWidget(add);
		ly->addLayout(hl1);

		QObject::connect(add, &QPushButton::clicked, this, [=]() {
			string s1 = id->text().toStdString();
			string s2 = de->text().toStdString();
			string s3 = loc->text().toStdString();
			try { this->s.addServ(s1,s2,s3,this->area); update(); }
			catch (exception e) { QMessageBox::warning(this, "Error: ", QString::fromStdString(e.what())); }
			});
	}
};



class GUI :public QWidget {
private:
	QTableView* tabel = new QTableView;
	Service& s;
	MyTableModel* model; 
public:
	GUI(Service& s1) : s{ s1 } {
		vector<Ethnologist> v = this->s.getSVE();
		for (auto it : v) {
			model= new MyTableModel{ s.getSVB() ,it.getArea()};
			EtWindow* a = new EtWindow(s, it.getName(), it.getArea());
			//s.addObs(a);
			a->resize(1000, 300);
			a->show();
		}
	}
};