/*
 * ZPath.h
 *
 *  Created on: Dec 15, 2010
 *      Author: root
 */

#ifndef ZPATH_H
#define ZPATH_H

#include "ZString.h"

class ZPath {
public:
	ZPath();
	ZPath(const ZString& pPath);

	void setPath(const ZString& pPath);
	ZString fullPath();
	ZString directoryName();
	ZString fileName();
	ZString extension();
	ZString fileNameWithoutExtension();
	ZString changeExtension(const ZString& pExtension);

private:
	ZString mFullPath;
};

#endif /* ZPATH_H */
