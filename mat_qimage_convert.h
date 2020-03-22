// opencv version >= 3.0

#ifndef MAT_QIMAGE_CONVERT_H
#define MAT_QIMAGE_CONVERT_H

#include <QImage>
#include <assert.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

// ==================================================================================
// Warning!
// When the src Mat channels is 3 or the src QImage format is RGB,
// the Mat2QImageShadowCopy() and QImage2MatShadowCopy will change the src image.
// When use Mat2QImageShadowCopy or QImage2MatShadowCopy,
// the src Mat::data (src QImage::bits()) address is the same as
// dst QImage::bits() (dst Mat::data) address !
// ===================================================================================
QImage Mat2QImageShadowCopy(const cv::Mat& src);
cv::Mat QImage2MatShadowCopy(const QImage& src);

QImage Mat2QImageDeepCopy(const cv::Mat& src);
cv::Mat QImage2MatDeepCopy(const QImage& src);

#endif // MAT_QIMAGE_CONVERT_H
