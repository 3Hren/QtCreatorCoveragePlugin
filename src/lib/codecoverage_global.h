#pragma once

#include <QtGlobal>

#if defined(CODECOVERAGE_LIBRARY)
#  define CODECOVERAGESHARED_EXPORT Q_DECL_EXPORT
#else
#  define CODECOVERAGESHARED_EXPORT Q_DECL_IMPORT
#endif
