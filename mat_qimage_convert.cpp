#include "mat_qimage_convert.h"
#include <QDebug>

// cv::Mat::data is the same as QImage::bits()
QImage Mat2QImageShadowCopy(const cv::Mat& src)
{
    // 1 channel
    if (src.type() == CV_8UC1) {
        QImage dst(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_Indexed8);
        dst.setColorCount(256);
        for (int i = 0; i < 256; i++) {
            dst.setColor(i, qRgb(i, i, i));
        }
        return dst;
    }
    // 3 channels
    else if (src.type() == CV_8UC3) {
        // warning: pay attention to this:
        cv::cvtColor(src, src, cv::COLOR_BGR2RGB);
        // it will change BRG to RBG in src Mat
        QImage dst(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_RGB888);
        return dst;
    }
    // 4 channels
    else if (src.type() == CV_8UC4) {
        QImage dst(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_ARGB32);
        return dst;
    } else {
        bool Nonsupport_Mat_Format = false;
        assert(Nonsupport_Mat_Format == true);
        return QImage();
    }
}

// cv::Mat::data is the same as QImage::bits()
cv::Mat QImage2MatShadowCopy(const QImage& src)
{
    cv::Mat dst;
    switch (src.format()) {
    // 4 channels
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        dst = cv::Mat(src.height(), src.width(), CV_8UC4, const_cast<unsigned char*>(src.constBits()),
            static_cast<size_t>(src.bytesPerLine()));
        break;
    // 3 channels
    case QImage::Format_RGB888:
        dst = cv::Mat(src.height(), src.width(), CV_8UC3, const_cast<unsigned char*>(src.constBits()),
            static_cast<size_t>(src.bytesPerLine()));
        // warning: pay attention to this:
        cv::cvtColor(dst, dst, cv::COLOR_BGR2RGB);
        // it will change BRG to RBG in src QImage
        break;
    // 1 channel
    case QImage::Format_Indexed8:
        dst = cv::Mat(src.height(), src.width(), CV_8UC1, const_cast<unsigned char*>(src.constBits()),
            static_cast<size_t>(src.bytesPerLine()));
        break;
    default:
        bool Nonsupport_QImage_Format = false;
        assert(Nonsupport_QImage_Format == true);
    }
    return dst;
}

// cv::Mat::data and QImage::bits() are different
QImage Mat2QImageDeepCopy(const cv::Mat& src)
{
    // 1 channel
    if (src.type() == CV_8UC1) {
        QImage dst(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_Indexed8);
        dst.setColorCount(256);
        for (int i = 0; i < 256; i++) {
            dst.setColor(i, qRgb(i, i, i));
        }
        return dst.copy();
    }
    // 3 channels
    else if (src.type() == CV_8UC3) {
        cv::Mat temp;
        cv::cvtColor(src, temp, cv::COLOR_BGR2RGB);
        QImage dst(temp.data, temp.cols, temp.rows, static_cast<int>(temp.step), QImage::Format_RGB888);
        return dst.copy();
    }
    // 4 channels
    else if (src.type() == CV_8UC4) {
        QImage dst(src.data, src.cols, src.rows, static_cast<int>(src.step), QImage::Format_ARGB32);
        return dst.copy();
    } else {
        bool Nonsupport_Mat_Format = false;
        assert(Nonsupport_Mat_Format == true);
        return QImage();
    }
}

// cv::Mat::data and QImage::bits() are different
cv::Mat QImage2MatDeepCopy(const QImage& src)
{
    cv::Mat dst;
    switch (src.format()) {
    // 4 channels
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied: {
        dst = cv::Mat(src.height(), src.width(), CV_8UC4, const_cast<unsigned char*>(src.constBits()),
            static_cast<size_t>(src.bytesPerLine()));
        return dst.clone();
    }
    // 3 channels
    case QImage::Format_RGB888: {
        dst = cv::Mat(src.height(), src.width(), CV_8UC3, const_cast<unsigned char*>(src.constBits()),
            static_cast<size_t>(src.bytesPerLine()));
        cv::Mat dstTemp;
        cv::cvtColor(dst, dstTemp, cv::COLOR_BGR2RGB);
        return dstTemp;
    }
    // 1 channel
    case QImage::Format_Indexed8: {
        dst = cv::Mat(src.height(), src.width(), CV_8UC1, const_cast<unsigned char*>(src.constBits()),
            static_cast<size_t>(src.bytesPerLine()));
        return dst.clone();
    }
    default:
        bool Nonsupport_QImage_Format = false;
        assert(Nonsupport_QImage_Format == true);
        return dst;
    }
}
