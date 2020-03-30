#pragma once

#include  <qabstractitemmodel.h>
#include "Repository.h"

class myTableModel : public QAbstractTableModel
{
	
private:
    Repository* repo;
public:
	myTableModel(Repository* re,QObject *parent=0);

	int rowCount(const QModelIndex& parent) const;
	
	int columnCount(const QModelIndex& parent) const;

	QVariant data(const QModelIndex& index, int role) const;
	
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;

	void signalRowAdded();

	void signalRowChanged();
	~myTableModel();
};
