#ifndef MAT_MWARRAY_CONVERT_H
#define MAT_MWARRAY_CONVERT_H

#include "mclmcrrt.h"
#include "mclcppclass.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

mwArray mat2mwArray(const cv::Mat imgSrc);
cv::Mat mwArray2mat(const mwArray data);

#endif // MAT_MWARRAY_CONVERT_H
