#include "logvariabletreewidget.h"

LogVariableTreeWidget::LogVariableTreeWidget(QWidget *pParent)
	: QTreeWidget(pParent)
{

}

LogVariableTreeWidget::~LogVariableTreeWidget()
{

}

/*
	Returns the current log variable item in the tree widget.
*/
LogVariableItem LogVariableTreeWidget::currentLogVariableItem() const
{
	LogVariableItem logVariableItem;

	if ( currentItem() )
	{
		logVariableItem.mLogVariable = (LogVariable*)currentItem()->data(1, Qt::UserRole).value<qulonglong>();
		logVariableItem.mRow = currentItem()->data(2, Qt::UserRole).toInt();
		logVariableItem.mCol = currentItem()->data(3, Qt::UserRole).toInt();
	}

	return logVariableItem;
}

/*
	Returns a list of all selected non-hidden log variable items.
*/
QList<LogVariableItem> LogVariableTreeWidget::selectedLogVariableItems() const
{
	QList<LogVariableItem> selectedLogVariableList;

	QList<QTreeWidgetItem *> selectedItemList = selectedItems();
	for (int i = 0; i < selectedItemList.size(); ++i) 
	{
		QTreeWidgetItem* item = selectedItemList[i];

		LogVariableItem logVariableItem;
		logVariableItem.mLogVariable = (LogVariable*)currentItem()->data(1, Qt::UserRole).value<qulonglong>();
		logVariableItem.mRow = currentItem()->data(2, Qt::UserRole).toInt();
		logVariableItem.mCol = currentItem()->data(3, Qt::UserRole).toInt();

		selectedLogVariableList.push_back(logVariableItem);
	}

	return selectedLogVariableList;
}

/*
	Sets the current log variable item in the tree widget.
*/
void LogVariableTreeWidget::setCurrentItem( LogVariableItem pLogVariableItem )
{
	if ( pLogVariableItem.mLogVariable )
	{
		QList<QTreeWidgetItem *> treeWidgetItems = findItems( QString("%1[%2][%3]").arg(pLogVariableItem.mLogVariable->name().c_str()).arg(pLogVariableItem.mRow).arg(pLogVariableItem.mCol), Qt::MatchFixedString | Qt::MatchRecursive );
		if ( treeWidgetItems.size() > 0 )
		{
			QTreeWidget::setCurrentItem( treeWidgetItems[0] );
		}
		else
		{
			 treeWidgetItems = findItems( QString("%1").arg(pLogVariableItem.mLogVariable->name().c_str()), Qt::MatchFixedString | Qt::MatchRecursive );
			 if ( treeWidgetItems.size() > 0 )
			 {
				 QTreeWidget::setCurrentItem( treeWidgetItems[0] );
			 }
		}
	}
}

void LogVariableTreeWidget::showEvent( QShowEvent * pEvent )
{
	clear();

	for ( int i = 0; i < DataRepository::instance()->mLogVariableList.size(); ++i )
	{
		QTreeWidgetItem * parent = new QTreeWidgetItem();
		parent->setText(0, DataRepository::instance()->mLogVariableList[i]->name().c_str() );
		parent->setData(1, Qt::UserRole, (qulonglong)DataRepository::instance()->mLogVariableList[i]);
		parent->setData(2, Qt::UserRole, 0);
		parent->setData(3, Qt::UserRole, 0);

		if ( DataRepository::instance()->mLogVariableList[i]->size() > 1 )
		{
			// Parent item is not selectable if size of log variable is greater than 1.
			parent->setFlags( Qt::ItemIsEnabled );

			for ( int row = 0; row < DataRepository::instance()->mLogVariableList[i]->row(); ++row )
			{
				for ( int col = 0; col < DataRepository::instance()->mLogVariableList[i]->col(); ++col )
				{
					QTreeWidgetItem * child = new QTreeWidgetItem();
					child->setText(0, QString("%1[%2][%3]").arg(DataRepository::instance()->mLogVariableList[i]->name().c_str()).arg(row).arg(col) );
					child->setData(1, Qt::UserRole, (qulonglong)DataRepository::instance()->mLogVariableList[i]);
					child->setData(2, Qt::UserRole, row);
					child->setData(3, Qt::UserRole, col);
					parent->addChild( child );
				}
			}
		}
		else
		{
			// Parent item is selectable if size of log variable is equal to 1.
			parent->setFlags( Qt::ItemIsSelectable | Qt::ItemIsEnabled );
		}

		addTopLevelItem ( parent );
	}

	QTreeWidget::showEvent(pEvent);
}