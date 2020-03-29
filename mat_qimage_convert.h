// opencv version >= 3.0

#ifndef MAT_QIMAGE_CONVERT_H
#define MAT_QIMAGE_CONVERT_H

#include <QImage>
#include <assert.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

/** WARNING!
 *  When the src QImage format is QImage::Format_RGB8888 and the enableDeepCopy == false,
 *  the ConvertQImageToMat() will change the pixel order of src QImage(RGB to BGR).
 *  ShadowCopy for show image(faster), DeepCopy for process image data(safer).
 */
QImage ConvertMatToQImage(const cv::Mat& src, bool enableDeepCopy = false);
cv::Mat ConvertQImageToMat(const QImage& src, bool enableDeepCopy = false);

#endif // MAT_QIMAGE_CONVERT_H
