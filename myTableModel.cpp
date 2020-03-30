#include "myTableModel.h"
#include <qcolor.h>
myTableModel::myTableModel(Repository* re,QObject *parent)
	: QAbstractTableModel(parent),repo{re}
{
}

int myTableModel::rowCount(const QModelIndex& parent) const
{
	return this->repo->getSize();
}

int myTableModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant myTableModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();
	Idea id = this->repo->getAllIdeas()[row];

	if (role == Qt::DisplayRole) {
		switch (column)
		{
		case 0:
			return QString::fromStdString(id.getWritter());
		case 1:
			return QString::fromStdString(id.getDescription());
		case 2:
			return QString::fromStdString(id.getStatus());
		case 3:
			return QString::number(id.getAct());
		default:
			break;
		}
	}

	if (role == Qt::BackgroundRole) {
		if (row % 2 == 0) {
			return QColor{ Qt::green };
		}
	}
	return QVariant();
}

QVariant myTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section)
			{
			case 0:
				return QString{ "Creator" };
			case 1:
				return QString{ "Description" };
			case 2:
				return QString{ "Status" };
			case 3:
				return QString{ "Act" };
			default:
				break;
			}
		}
	}
	return QVariant();
}

void myTableModel::signalRowAdded()
{
	this->repo->sort();
	QAbstractItemModel::beginInsertRows(QModelIndex(), this->repo->getSize(), this->repo->getSize());
	QAbstractItemModel::endInsertRows();
}

void myTableModel::signalRowChanged()
{
	QAbstractItemModel::beginResetModel();
	QAbstractItemModel::endResetModel();
}
myTableModel::~myTableModel()
{
}
