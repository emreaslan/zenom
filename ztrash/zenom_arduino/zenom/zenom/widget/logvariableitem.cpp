#include "logvariableitem.h"
#include <datarepository.h>

LogVariableItem::LogVariableItem( LogVariable* pLogVariable, int pRow, int pCol )
	: mLogVariable(pLogVariable), mRow(pRow), mCol(pCol)
{

}

LogVariableItem::~LogVariableItem()
{

}

void LogVariableItem::saveSettings( QSettings& pSettings )
{
	pSettings.setValue("logVariable", mLogVariable ? mLogVariable->name().c_str() : "");
	pSettings.setValue("row", mRow);
	pSettings.setValue("col", mCol);
}

void LogVariableItem::loadSettings( QSettings& pSettings )
{
    mLogVariable = DataRepository::instance()->findLogVariable( pSettings.value("logVariable", "").toString().toStdString() );
	mRow = pSettings.value("row", -1).toInt();
	mCol = pSettings.value("col", -1).toInt();
}

void LogVariableItem::set( LogVariable* pLogVariable, int pRow, int pColumn )
{
	mLogVariable = pLogVariable;
	mRow = pRow;
	mCol = pColumn;
}

LogVariable* LogVariableItem::logVariable() const
{
	return mLogVariable;
}

int LogVariableItem::row() const
{
	return mRow;
}

int LogVariableItem::column() const
{
	return mCol;
}

bool LogVariableItem::isNull() const
{
    return mLogVariable == NULL;
}

double LogVariableItem::lastHeapElement()
{
	return mLogVariable->lastHeapElement(mRow, mCol);
}

double LogVariableItem::lastTime()
{
    return mLogVariable->lastHeapElement(mLogVariable->size());
}

bool LogVariableItem::isValid() const
{
    return !isNull() && mLogVariable->isHeapValid();
}

int LogVariableItem::size() const
{
    return mLogVariable->heapSize();
}

QPointF LogVariableItem::heapElement(int pIndex) const
{
    return QPointF ( mLogVariable->heapElement(pIndex, mLogVariable->size()) , mLogVariable->heapElement(pIndex, mRow, mCol) );
}
