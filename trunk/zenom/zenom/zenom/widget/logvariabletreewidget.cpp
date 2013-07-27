#include "logvariabletreewidget.h"

LogVariableTreeWidget::LogVariableTreeWidget(QWidget *pParent)
	: QTreeWidget(pParent)
{
    setHeaderLabel("Log Variables");
}

LogVariableTreeWidget::~LogVariableTreeWidget()
{

}

void LogVariableTreeWidget::setLogVariableList(const LogVariableList &pLogVariableList)
{
    clear();

    for ( unsigned int i = 0; i < pLogVariableList.size(); ++i )
    {
        QTreeWidgetItem * parent = new QTreeWidgetItem();
        parent->setText(0, pLogVariableList[i]->name().c_str() );
        parent->setData(1, Qt::UserRole, (qulonglong)pLogVariableList[i]);
        parent->setData(2, Qt::UserRole, 0);
        parent->setData(3, Qt::UserRole, 0);

        if ( pLogVariableList[i]->size() > 1 )
        {
            // Parent item is not selectable if size of log variable is greater than 1.
            parent->setFlags( Qt::ItemIsEnabled );

            for ( unsigned int row = 0; row < pLogVariableList[i]->row(); ++row )
            {
                for ( unsigned int col = 0; col < pLogVariableList[i]->col(); ++col )
                {
                    QTreeWidgetItem * child = new QTreeWidgetItem();
                    child->setText(0, QString("%1[%2][%3]").arg(pLogVariableList[i]->name().c_str()).arg(row).arg(col) );
                    child->setData(1, Qt::UserRole, (qulonglong)pLogVariableList[i]);
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
}

/*
	Returns the current log variable item in the tree widget.
*/
LogVariableItem LogVariableTreeWidget::currentLogVariableItem() const
{
	LogVariableItem logVariableItem;

	if ( currentItem() )
	{
		LogVariable* logVariable = (LogVariable*)currentItem()->data(1, Qt::UserRole).value<qulonglong>();
		int row = currentItem()->data(2, Qt::UserRole).toInt();
		int col = currentItem()->data(3, Qt::UserRole).toInt();
		logVariableItem.set( logVariable, row, col );
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

        LogVariable* logVariable = (LogVariable*)item->data(1, Qt::UserRole).value<qulonglong>();
        int row = item->data(2, Qt::UserRole).toInt();
        int col = item->data(3, Qt::UserRole).toInt();

		selectedLogVariableList.push_back( LogVariableItem(logVariable, row, col) );
	}

	return selectedLogVariableList;
}

/*
	Sets the current log variable item in the tree widget.
*/
void LogVariableTreeWidget::setCurrentLogVariableItem( LogVariableItem pLogVariableItem )
{
	if ( !pLogVariableItem.isNull() )
    {
        QList<QTreeWidgetItem *> treeWidgetItems = QTreeWidget::findItems( QString("%1[%2][%3]")
			.arg(pLogVariableItem.logVariable()->name().c_str())
			.arg(pLogVariableItem.row())
            .arg(pLogVariableItem.column()), Qt::MatchFixedString | Qt::MatchRecursive | Qt::MatchCaseSensitive );

		if ( treeWidgetItems.size() > 0 )
		{
			QTreeWidget::setCurrentItem( treeWidgetItems[0] );
		}
		else
		{
			 treeWidgetItems = findItems( QString("%1")
                 .arg(pLogVariableItem.logVariable()->name().c_str()), Qt::MatchFixedString | Qt::MatchRecursive | Qt::MatchCaseSensitive );
			 if ( treeWidgetItems.size() > 0 )
			 {
				 QTreeWidget::setCurrentItem( treeWidgetItems[0] );
             }
		}
	}
}
