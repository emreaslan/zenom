/*
 * ZPath.cpp
 *
 *  Created on: Dec 15, 2010
 *      Author: root
 */

#include "ZPath.h"

ZPath::ZPath()
{

}

ZPath::ZPath(const ZString& pPath)
{
	setPath(pPath);
}

void ZPath::setPath(const ZString& pPath)
{
	mFullPath = pPath;
}

ZString ZPath::fullPath()
{
	return mFullPath;
}

ZString ZPath::directoryName()
{
	return mFullPath.left(mFullPath.length() - fileName().length());
}

ZString ZPath::fileName()
{
	int pos = mFullPath.findReverse('/');
	if(pos == -1)
	{
		return mFullPath;
	}
	else
	{
		if(mFullPath.length() - pos)
			return mFullPath.right(mFullPath.length() - pos - 1);
		else
			return "";
	}
}

ZString ZPath::extension()
{
	ZString filename = fileName();
	if(filename.length())
	{
		int pos = filename.findReverse('.');
		if(filename.length() - pos > 0 && pos != -1)
			return filename.right(filename.length() - pos - 1);
		else
			return "";
	}
	else
	{
		return "";
	}
}

ZString ZPath::fileNameWithoutExtension()
{
	ZString filename = fileName();
	ZString ext = extension();
	if(ext.length())
		return filename.left(filename.length()-extension().length()-1);
	else
		return filename;
}

ZString ZPath::changeExtension(const ZString& pExtension)
{
	ZString filename = fileNameWithoutExtension();
	ZString dir = directoryName();
	return dir + filename + "." + pExtension;
}
