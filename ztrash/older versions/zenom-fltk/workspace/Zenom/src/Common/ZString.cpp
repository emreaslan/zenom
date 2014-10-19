#include "ZString.h"
#include <string.h>
#include <iostream>

ZString::ZString(void) : mStrPtr(NULL)
{
	createNullStr();	
}

ZString::ZString(const char *pStr) :  mStrPtr(NULL)
{
	if (pStr == NULL)
	{
		createNullStr();
		return;
	}
	int size = strlen(pStr);
	if (size)
	{
		reserveStr(size);
		strncpy(mStrPtr, pStr , mLength + 1 ); // +1 \0 icin
	}
	else
		createNullStr();
}


ZString::ZString(const ZString &pStr): mStrPtr(NULL)
{
	reserveStr(pStr.length());
	strncpy(mStrPtr, pStr.c_str() , mLength + 1);
}

ZString::ZString(const int pInt): mStrPtr(NULL)
{
	char *tempStr = new char[100];
	sprintf(tempStr,"%d", pInt);
	mLength = strlen(tempStr);
	reserveStr(mLength);
	strncpy(mStrPtr, tempStr , mLength + 1);
	delete[] tempStr;
}

ZString::ZString(const double pDouble, const int pPrecision): mStrPtr(NULL)
{
	char *tempStr = new char[100];
	switch(pPrecision)
	{
	case 0:
		sprintf(tempStr,"%.0f", pDouble);
		break;
	case 1:
		sprintf(tempStr,"%.1f", pDouble);
		break;
	case 2:
		sprintf(tempStr,"%.2f", pDouble);
		break;
	case 3:
		sprintf(tempStr,"%.3f", pDouble);
		break;
	case 4:
		sprintf(tempStr,"%.4f", pDouble);
		break;
	case 5:
		sprintf(tempStr,"%.5f", pDouble);
		break;
	default:
		sprintf(tempStr,"%.6f", pDouble);
		break;
	}
	
	mLength = strlen(tempStr);
	reserveStr(mLength);
	strncpy(mStrPtr, tempStr , mLength + 1);
	delete[] tempStr;
}

ZString ZString::operator=(const ZString &pLeft)
{
	reserveStr(pLeft.length());
	strncpy(mStrPtr, pLeft.c_str() , mLength + 1);
	return *this;
}

void ZString::reserveStr(int pSize)
{
	delete[] mStrPtr;
	mLength = pSize;
	mStrPtr = new char[mLength + 1]; // +1 \n icin
}

void ZString::createNullStr()
{
	delete[] mStrPtr;
	mStrPtr = new char[1];
	mStrPtr[0] = '\000';
	mLength = 0;
}
 
int ZString::find(const char pChar, const int pCount /* = 1 */ ) const
{
	int count = 0;
	for (int i = 0; i < mLength ; ++i)
	{
		if (mStrPtr[i] == pChar)
		{
			++count;
			if (count == pCount)
				return i;
		}
	}
	return -1;
}

int ZString::length() const
{
	return mLength;
}

const char* ZString::c_str() const
{
	return mStrPtr;
}


ZString::~ZString(void)
{
	delete[] mStrPtr;
}


ZString ZString::operator+(const ZString &pLeft) const
{
	char *newStr = new char[pLeft.length() + this->length() + 1]; // +1 \n icin
	sprintf(newStr, "%s%s", this->c_str(), pLeft.c_str());
	ZString rStr(newStr);
	delete[] newStr;
	return rStr;
}

ZString& ZString::operator<<(const ZString &pLeft)
{
	(*this) = (*this) + pLeft;
	return (*this);
}

bool ZString::operator==(const ZString &pLeft) const
{
	if ( mLength != pLeft.length())
		return false;
	else
		return (strcmp(mStrPtr, pLeft.c_str()) == 0 );
}

bool ZString::operator!=(const ZString &pLeft) const
{
	return !(*this == pLeft);
}

int ZString::findReverse(const char pChar, const int pCount /* = 1 */ ) const
{
	int count = 0;
	for (int i = mLength; i > 0 ; --i )
	{
		if (mStrPtr[i] == pChar)
		{
			++count;
			if (count == pCount)
				return i;
		}
	}
	return -1;
}

ZString ZString::removeFromBack(const char pChar)
{
	int pos = findReverse(pChar);
	if (pos == -1)
		return *this;
	else
	{
		char temp = mStrPtr[pos];
		mStrPtr[pos] = '\000';
		ZString rStr(mStrPtr);
		mStrPtr[pos] = temp;
		return rStr;
	}
}

ZString ZString::right(const int pCount) const
{
	if(pCount >= mLength)
	{
		return *this;
	}
	else
	{
		return ZString(&mStrPtr[mLength-pCount]);
	}
}

ZString ZString::left(const int pCount) const
{
	if(pCount >= mLength)
	{
		return *this;
	}
	else
	{
		char temp = mStrPtr[pCount];
		mStrPtr[pCount] = '\000';
		ZString rStr(mStrPtr);
		mStrPtr[pCount] = temp;
		return rStr;
	}
}

