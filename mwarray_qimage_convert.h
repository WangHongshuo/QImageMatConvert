#ifndef MWARRAY_QIMAGE_CONVERT_H
#define MWARRAY_QIMAGE_CONVERT_H

#include "mclmcrrt.h"
#include "mclcppclass.h"
#include <QImage>

QImage mwArray2QImage(const mwArray input);
mwArray QImage2mwArray(QImage input);

#endif // MWARRAY_QIMAGE_CONVERT_H
