#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ScreenWritters.h"
#include "Controller.h"
#include "myTableModel.h"
#include <qpushbutton.h>
#include <qboxlayout.h>
#include <qlineedit.h>

class ScreenWritters : public QMainWindow
{
	Q_OBJECT
private:
	Controller con;
	Writter wr;
	myTableModel* model;
	QPushButton* developButton;
	QHBoxLayout* develop;
	std::vector<QPushButton*> saveButtonsDevelop;
	std::vector<QLineEdit*> lineEditsDevelop;
	QVBoxLayout* developLayoutLineEdits;
	QVBoxLayout* utlimataLayout;
public:
	ScreenWritters(Writter wri,Controller co,myTableModel* m,QWidget *parent = Q_NULLPTR);

private:
	Ui::ScreenWrittersClass ui;

private slots:
	void add();
	
	void revise();

	void savePlot();

	void developClicked();
};
