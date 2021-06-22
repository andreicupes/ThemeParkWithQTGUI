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
#include <qtablewidget.h>

class Nwindow :public QWidget, public Observer {
private:
	vector<QColor> col;
	Service& s;
	QTableWidget* tbl = new QTableWidget(5,6);
	QHBoxLayout* ly = new QHBoxLayout;
public:
	Nwindow(Service& s1, vector<QColor> a) :s{ s1 } { s.addObs(this); this->col = a; setComp(); update(); }
	void setComp() {
		setLayout(ly);
		ly->addWidget(tbl);
		tbl->setColumnCount(6);
		tbl->setRowCount(5);
		tbl->setVerticalHeaderItem(0, new QTableWidgetItem("A"));
		tbl->setVerticalHeaderItem(1, new QTableWidgetItem("B"));
		tbl->setVerticalHeaderItem(2, new QTableWidgetItem("C"));
		tbl->setVerticalHeaderItem(3, new QTableWidgetItem("D"));
		tbl->setVerticalHeaderItem(4, new QTableWidgetItem("E"));
	}
	void update() override {
		tbl->clear();
		tbl->setColumnCount(6);
		tbl->setRowCount(5);
		tbl->setVerticalHeaderItem(0, new QTableWidgetItem("A"));
		tbl->setVerticalHeaderItem(1, new QTableWidgetItem("B"));
		tbl->setVerticalHeaderItem(2, new QTableWidgetItem("C"));
		tbl->setVerticalHeaderItem(3, new QTableWidgetItem("D"));
		tbl->setVerticalHeaderItem(4, new QTableWidgetItem("E"));
		vector<Building> b = s.getSVB();
		vector<Ethnologist> e = s.getSVE();
		int i, j;
		for (i = 0; i < 5; i++)
		{
			for (j = 0; j < 5; j++) {
				/*string l;
				if (j == 0) l = "1";
				else if (j == 1) l = "2";
				else if (j == 2) l = "3";
				else if (j == 3) l = "4";
				else if (j == 4) l = "5";
				else if (j == 5) l = "6";*/
				string a;
				if (i == 0) a = "A" + to_string(j+1);
				else if (i == 1) a = "B" + to_string(j+1);
				else if (i == 2) a = "C" + to_string(j+1);
				else if (i == 3) a = "D" + to_string(j+1);
				else if (i == 4) a = "E" + to_string(j+1);

				for (auto& it : b) {
					if (it.getCoord().find(a) != std::string::npos)
					{
						tbl->setItem(i, j, new QTableWidgetItem);
						string area = it.getArea();
						int k;
						for (k = 0; k < e.size(); k++) if (e[k].getArea() == area) break;
						QColor d = this->col[k];
						tbl->item(i, j)->setBackground(d);

					}
					
				}

			}
		}
		/*for (i = 0; i < 5; i++) {
			string a;
			if (i == 0) a = "A6";
			else if (i == 1) a = "B6" ;
			else if (i == 2) a = "C6" ;
			else if (i == 3) a = "D6" ;
			else if (i == 4) a = "E6" ;
			for (auto& it : b) {
				if (it.getCoord().find(a) != std::string::npos)
				{
					tbl->setItem(i, 5, new QTableWidgetItem);
					string area = it.getArea();
					int k;
					for (k = 0; k < e.size(); k++) if (e[k].getArea() == area) break;
					QColor d = this->col[k];
					tbl->item(i, 5)->setBackground(d);

				}

			}
		}*/
		tbl->setItem(4, 5, new QTableWidgetItem);
		tbl->item(4, 5)->setBackground(Qt::black);
	}
};



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
	EtWindow(Service& s1, string a, string b, QColor d) :s{ s1 } 
	{	s.addObs(this); 
		this->name = a; 
		this->area = b; 
		setWindowTitle(QString::fromStdString(a)); 
		this->model= new MyTableModel{ s.getSVB(),this->area }; 
		setComp(); 
		this->update();
		QPalette pal = this->palette();
		col = d;
		pal.setColor(QPalette::Window,col );
		this->setPalette(pal);
	}
	void update() override {

		model->setFiles(s.sortare(area));
		tabel->setModel(model);
	}
	void setComp() {
		setLayout(ly); ly->addWidget(tabel);
		tabel->setSelectionMode(QAbstractItemView::SingleSelection);
		tabel->setSelectionBehavior(QAbstractItemView::SelectRows);
		QVBoxLayout* vl1 = new QVBoxLayout();
		QVBoxLayout* vl2 = new QVBoxLayout();
		QHBoxLayout* hl1 = new QHBoxLayout();
		QLabel* li = new QLabel("Id: ");
		QLabel* ld = new QLabel("Description: ");
		QLabel* lc = new QLabel("Location(capital letters, space as delimiter): ");
		QLineEdit* de = new QLineEdit();
		QLineEdit* id = new QLineEdit();
		QLineEdit* loc = new QLineEdit();
		QPushButton* add = new QPushButton("Add");
		QPushButton* upd = new QPushButton("Update");
		vl1->addWidget(li); vl1->addWidget(id);vl1->addWidget(ld); vl1->addWidget(de); vl1->addWidget(lc); vl1->addWidget(loc);
		hl1->addLayout(vl1);
		vl2->addWidget(add); vl2->addWidget(upd);
		upd->setEnabled(false);

		hl1->addLayout(vl2);
		ly->addLayout(hl1);

		QObject::connect(add, &QPushButton::clicked, this, [=]() {
			string s1 = id->text().toStdString();
			string s2 = de->text().toStdString();
			string s3 = loc->text().toStdString();
			try { this->s.addServ(s1,s2,s3,this->area); update(); }
			catch (exception e) { QMessageBox::warning(this, "Error: ", QString::fromStdString(e.what())); }
			});

		QObject::connect(tabel, &QAbstractItemView::clicked, this, [=]() {
			auto index = (tabel->selectionModel()->currentIndex());
			string a = index.sibling(index.row(), 2).data().toString().toStdString();
			if(a==this->area){ upd->setEnabled(true); }
			else upd->setEnabled(false);
			});

		QObject::connect(upd, &QPushButton::clicked, this, [=]() {
			auto index = (tabel->selectionModel()->currentIndex());
			string id = index.sibling(index.row(), 0).data().toString().toStdString();
			string s2 = de->text().toStdString();
			string s3 = loc->text().toStdString();
			try { this->s.updServ(id, s2, s3); update(); }
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
		vector<QColor> q;
		for (auto it : v) {
			model= new MyTableModel{ s.getSVB() ,it.getArea()};
			QColor d= QColor(qrand() % 255, qrand() % 255, qrand() % 255);
			q.push_back(d);
			EtWindow* a = new EtWindow(s, it.getName(), it.getArea(),d);
			//s.addObs(a);
			a->resize(1000, 300);
			a->show();
		}
		Nwindow* w = new Nwindow(s, q);
		w->resize(700, 400);
		w->show();
	}
};