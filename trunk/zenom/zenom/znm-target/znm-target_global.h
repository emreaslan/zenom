#ifndef ZNM_TARGET_GLOBAL_H
#define ZNM_TARGET_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ZNM_TARGET_LIBRARY)
#  define ZNM_TARGET_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define ZNM_TARGET_SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ZNM_TARGET_GLOBAL_H
