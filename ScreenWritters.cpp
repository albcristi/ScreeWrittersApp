#include "ScreenWritters.h"
#include <qerrormessage.h>

ScreenWritters::ScreenWritters(Writter wri, Controller co,myTableModel* m,QWidget *parent)
	: QMainWindow(parent), wr{ wri },con{co},model{m}
{
	ui.setupUi(this);
	this->developButton = nullptr;
	this->develop = new QHBoxLayout();
	this->utlimataLayout = new QVBoxLayout();
	this->ui.horizontalLayout_3->addLayout(this->develop);
	this->developLayoutLineEdits = new QVBoxLayout();
	setWindowTitle(this->wr.getName().c_str());
	if (this->wr.getExpertise() != "Senior") {
		this->ui.aprooveButton->setDisabled(true);
	}
	if (this->con.hasAcceptedIdeas(this->wr) == true) {
		this->developButton = new QPushButton();
		this->developButton->setText("Develop");
		QFont f{ "Times",20 };
		this->developButton->setFont(f);
		this->develop->addWidget(this->developButton);
	
	}
	this->ui.myTable->setModel(model);
	QFont f{ "Times",20 };
	this->ui.actLabel->setFont(f);
	this->ui.descriptionLabel->setFont(f);
	this->ui.addPropButton->setFont(f);
	this->ui.aprooveButton->setFont(f);
	this->ui.savePlotButton->setFont(f);

	QObject::connect(ui.addPropButton, &QPushButton::clicked, this, &ScreenWritters::add);
	QObject::connect(ui.aprooveButton, &QPushButton::clicked, this, &ScreenWritters::revise);
	QObject::connect(ui.savePlotButton, &QPushButton::clicked, this, &ScreenWritters::savePlot);
	QObject::connect(this->developButton, &QPushButton::clicked, this, &ScreenWritters::developClicked);
	//this->utlimataLayout->addLayout(this->ui.horizontalLayout_3);
	
}

void ScreenWritters::revise()
{
	QModelIndex index = this->ui.myTable->currentIndex();
	if (index.row() == -1) {
		QErrorMessage* ms = new QErrorMessage();
		ms->showMessage("Nothing has been selected!\n");
		return;
	}

	std::string status = this->con.getAllIdeas()[index.row()].getStatus();
	if (status != "proposed") {
		QErrorMessage* ms = new QErrorMessage();
		ms->showMessage("The selected item is already aprooved!\n");
		return;
	}
	Idea id = this->con.getAllIdeas()[index.row()];
	id.setStatus("accepted");
	if (this->developButton == nullptr) {
		this->developButton = new QPushButton();
		this->developButton->setText("Develop");
		QFont f{ "Times",20 };
		this->developButton->setFont(f);
		this->develop->addWidget(this->developButton);
	}
	this->con.update(id);
	this->model->signalRowChanged();
}

void ScreenWritters::savePlot()
{
	std::ofstream dest("all_accepted.txt", std::ios::out);
	dest.close();
	std::ofstream d("all_accepted.txt", std::ios::app);
	d << "\tACT 1\n";
	for (auto id : this->con.getAprobByAct(1)) {
		std::string idea;
		idea.append("[" + id.getWritter() + "] " + id.getDescription() + "\n");
		d << idea;
	}
	d << "\tACT 2\n";
	for (auto id : this->con.getAprobByAct(2)) {
		std::string idea;
		idea.append("[" + id.getWritter() + "] " + id.getDescription() + "\n");
		d << idea;
	}
	d << "\tACT 3\n";
	for (auto id : this->con.getAprobByAct(3)) {
		std::string idea;
		idea.append("[" + id.getWritter() + "] " + id.getDescription() + "\n");
		d << idea;
	}
	d.close();
}

void ScreenWritters::developClicked()
{
	this->developLayoutLineEdits->destroyed();
	if (this->saveButtonsDevelop.size() > 0) {
		this->saveButtonsDevelop.clear();
		this->lineEditsDevelop.clear();
	}
	this->saveButtonsDevelop.reserve(this->con.allWritterApprovedIdeas(wr).size() + 2);
	this->lineEditsDevelop.reserve(this->con.allWritterApprovedIdeas(wr).size() + 2);
	int i = 0;
	for (auto idea : this->con.allWritterApprovedIdeas(wr)) {
		this->lineEditsDevelop.push_back(new QLineEdit());
		this->saveButtonsDevelop.push_back(new QPushButton());
		this->lineEditsDevelop[i]->setText(idea.getDescription().c_str());
		this->saveButtonsDevelop[i]->setText("Save");
		this->developLayoutLineEdits->addWidget(this->lineEditsDevelop[i]);
		this->developLayoutLineEdits->addWidget(this->saveButtonsDevelop[i]);
		i++;
	}
	this->ui.horizontalLayout_3->addLayout(this->developLayoutLineEdits);
	
}

void ScreenWritters::add() {
	std::string errors;
	std::string desc = this->ui.descriptionBuddy->text().toStdString();
	if (desc.size() == 0) {
		errors.append("No description has been provided!\n");
	}
	int act = this->ui.actBuddy->text().toInt();
	if (act < 1 || act > 3) {
		errors.append("Invalid act number!\n");
	}
	for (auto id : this->con.getAllIdeas()) {
		if (id.getDescription() == desc) {
			errors.append("PLEASE COME WITH YOUR OWN IDEAS!\n");
			break;
		}
	}
	if (errors.size() == 0) {

		this->ui.descriptionBuddy->clear();
		this->ui.actBuddy->clear();
		//add the idea
		Idea id(desc, "proposed", this->wr.getName(), act);
		this->con.add(id);
		this->model->signalRowAdded();
	
	}
	else {
		QErrorMessage* ms = new QErrorMessage();
		ms->showMessage(errors.c_str());
	}
}
