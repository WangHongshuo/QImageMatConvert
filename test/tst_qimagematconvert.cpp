#include <QtTest>

// add necessary includes here
#include "../mat_qimage_convert.h"
#include <QDebug>
#include <QImage>
#include <QString>
#include <opencv2/core.hpp>
#include <vector>

using cv::Mat;
using cv::Point2i;
using cv::Point3i;
using std::vector;

class QImageMatConvert : public QObject {
    Q_OBJECT

public:
    QImageMatConvert();
    ~QImageMatConvert();
    Mat mImg;
    QImage qImg;

private slots:
    void initTestCase();

    void initTestCase01ForGrayImage();
    void testCase01Mat2QImageShadowCopyForGrayImage();
    void testCase01Mat2QImageDeepCopyForGrayImage();
    void testCase01QImage2MatShadowCopyForGrayImage();
    void testCase01QImage2MatDeepCopyForGrayImage();
    void cleanupTest01ForGrayImage();

    void initTestCase01For3ChannelImage();
    void testCase01Mat2QImageShadowCopyFor3ChannelImage();
    void testCase01Mat2QImageDeepCopyFor3ChannelImage();
    void testCase01QImage2MatShadowCopyFor3ChannelImage();
    void testCase01QImage2MatShadowCopyFor3ChannelImageCleanUp();
    void testCase01QImage2MatDeepCopyFor3ChannelImage();
    void cleanupTestCase01For3ChannelImage();

    void initTestCase01For4ChannelImage();
    void testCase01Mat2QImageShadowCopyFor4ChannelImage();
    void testCase01Mat2QImageDeepCopyFor4ChannelImage();
    void testCase01QImage2MatCopyFor4ChannelImage();
    void testCase01QImage2MatDeepCopyFor4ChannelImage();
    void cleanupTestCase01For4ChannelImage();

    void cleanupTestCase();

private:
    void initArray();
};

QImageMatConvert::QImageMatConvert() {}

QImageMatConvert::~QImageMatConvert() {}

void QImageMatConvert::initTestCase() {}

void QImageMatConvert::initTestCase01ForGrayImage()
{
    // Gray_Test.bmp row: 1, col: 3, 1 channel, 8 bit, 8-bit for each pixel
    // Original(Opencv) Data:
    // [  0, 127, 255]
    mImg = cv::imread("..//test//img//Gray_Test.bmp", cv::IMREAD_UNCHANGED);
    QCOMPARE(mImg.rows, 1);
    QCOMPARE(mImg.cols, 3);
    QCOMPARE(mImg.dataend - mImg.datastart, 3);
    QCOMPARE(mImg.type(), CV_8UC1);
    QCOMPARE(mImg.data[0], 0);
    QCOMPARE(mImg.data[1], 127);
    QCOMPARE(mImg.data[2], 255);
    // QImage Data:
    // [  0, 127, 255, 0]
    qImg.load("..//test//img//Gray_Test.bmp");
    QCOMPARE(qImg.format(), QImage::Format_Indexed8);
    QCOMPARE(qImg.sizeInBytes(), 4);
    QCOMPARE(qImg.bytesPerLine(), 4);
    QCOMPARE(qImg.scanLine(0)[0], 0);
    QCOMPARE(qImg.scanLine(0)[1], 127);
    QCOMPARE(qImg.scanLine(0)[2], 255);
    QCOMPARE(qImg.scanLine(0)[3], 0);
}

void QImageMatConvert::testCase01Mat2QImageShadowCopyForGrayImage()
{
    QImage qImgShadowCopy = ConvertMatToQImage(mImg);
    QCOMPARE(qImgShadowCopy.bits(), mImg.data);
    QCOMPARE(qImgShadowCopy.scanLine(0)[0], mImg.data[0]);
    QCOMPARE(qImgShadowCopy.scanLine(0)[1], mImg.data[1]);
    QCOMPARE(&(qImgShadowCopy.scanLine(0)[1]), &(mImg.data[1]));
}

void QImageMatConvert::testCase01Mat2QImageDeepCopyForGrayImage()
{
    QImage qImgDeepCopy = ConvertMatToQImage(mImg, true);
    QCOMPARE(qImgDeepCopy.bits() == mImg.data, false);
    QCOMPARE(qImgDeepCopy.scanLine(0)[0], mImg.data[0]);
    QCOMPARE(qImgDeepCopy.scanLine(0)[1], mImg.data[1]);
    QCOMPARE(&(qImgDeepCopy.scanLine(0)[1]) == &(mImg.data[1]), false);
}

void QImageMatConvert::testCase01QImage2MatShadowCopyForGrayImage()
{
    Mat mImgShadowCopy = ConvertQImageToMat(qImg);
    QCOMPARE(mImgShadowCopy.data, qImg.bits());
    QCOMPARE(mImgShadowCopy.data[0], qImg.scanLine(0)[0]);
    QCOMPARE(mImgShadowCopy.data[1], qImg.scanLine(0)[1]);
    QCOMPARE(&(mImgShadowCopy.data[1]), &(qImg.scanLine(0)[1]));
}

void QImageMatConvert::testCase01QImage2MatDeepCopyForGrayImage()
{
    Mat mImgDeepCopy = ConvertQImageToMat(qImg, true);
    QCOMPARE(mImgDeepCopy.data == qImg.bits(), false);
    QCOMPARE(mImgDeepCopy.data[0], qImg.scanLine(0)[0]);
    QCOMPARE(mImgDeepCopy.data[1], qImg.scanLine(0)[1]);
    QCOMPARE(&(mImgDeepCopy.data[1]) == &(qImg.scanLine(0)[1]), false);
}

void QImageMatConvert::cleanupTest01ForGrayImage() {}

void QImageMatConvert::initTestCase01For3ChannelImage()
{
    // RGBA_Test.bmp row: 2, col: 3, 3 channel, 8 bit, 24-bit for each pixel
    // Original Data(BGR order):
    // [[  0,   0, 255], [  0, 255,   0], [255,   0,   0];
    //  [  0,   0,   0], [127, 127, 127], [255, 255, 255]]
    mImg = cv::imread("..//test//img//RGBA_Test.bmp", cv::IMREAD_UNCHANGED);
    QCOMPARE(mImg.rows, 2);
    QCOMPARE(mImg.cols, 3);
    QCOMPARE(mImg.dataend - mImg.datastart, 18);
    QCOMPARE(mImg.type(), CV_8UC3);
    QCOMPARE(mImg.data[2], 255);
    QCOMPARE(mImg.data[6], 255);
    QCOMPARE(mImg.data[13], 127);
    // QImage Data(Format_RGB32, BGRA order, alpha == 0xff):
    // [[  0,   0, 255, 255], [  0, 255,   0, 255], [255,   0,   0, 255];
    //  [  0,   0,   0, 255], [127, 127, 127, 255], [255, 255, 255, 255]]
    qImg.load("..//test//img//RGBA_Test.bmp");
    QCOMPARE(qImg.format(), QImage::Format_RGB32);
    QCOMPARE(qImg.sizeInBytes(), 24);
    QCOMPARE(qImg.bytesPerLine(), 12);
    QCOMPARE(qImg.scanLine(0)[2], 255);
    QCOMPARE(qImg.scanLine(0)[3], 255);
    QCOMPARE(qImg.scanLine(0)[8], 255);
    // QImage Data(Format_RGB888, RGB order):
    // [[255,   0,   0], [  0, 255,   0], [  0,   0, 255], ??, ??, ??;
    //  [  0,   0,   0], [127, 127, 127], [255, 255, 255], ??, ??, ??]
    qImg.convertTo(QImage::Format_RGB888);
    QCOMPARE(qImg.sizeInBytes(), 24);
    QCOMPARE(qImg.bytesPerLine(), 12);
    QCOMPARE(qImg.scanLine(0)[0], 255);
    QCOMPARE(qImg.scanLine(0)[8], 255);
    QCOMPARE(qImg.scanLine(1)[4], 127);
}

void QImageMatConvert::testCase01Mat2QImageShadowCopyFor3ChannelImage()
{
    QImage qImgShadowCopy = ConvertMatToQImage(mImg);
    QCOMPARE(qImgShadowCopy.bits(), mImg.data);
    QCOMPARE(qImgShadowCopy.scanLine(0)[0], mImg.data[0]);
    QCOMPARE(qImgShadowCopy.scanLine(0)[1], mImg.data[1]);
    QCOMPARE(&(qImgShadowCopy.scanLine(0)[1]), &(mImg.data[1]));
    QCOMPARE(qImgShadowCopy.format(), QImage::Format_BGR888);
}

void QImageMatConvert::testCase01Mat2QImageDeepCopyFor3ChannelImage()
{
    QImage qImgDeepCopy = ConvertMatToQImage(mImg, true);
    QCOMPARE(qImgDeepCopy.bits() == mImg.data, false);
    QCOMPARE(qImgDeepCopy.scanLine(0)[0], mImg.data[0]);
    QCOMPARE(qImgDeepCopy.scanLine(0)[1], mImg.data[1]);
    QCOMPARE(&(qImgDeepCopy.scanLine(0)[1]) == &(mImg.data[1]), false);
    QCOMPARE(qImgDeepCopy.format(), QImage::Format_BGR888);
}

void QImageMatConvert::testCase01QImage2MatShadowCopyFor3ChannelImage()
{
    // QImage Data(Format_RGB888, RGB order):
    // [[255,   0,   0], [  0, 255,   0], [  0,   0, 255], ??, ??, ??;
    //  [  0,   0,   0], [127, 127, 127], [255, 255, 255], ??, ??, ??]
    // the pixel order of qImg will be converted to BGR:
    // [[  0,   0, 255], [  0, 255,   0], [255,   0,   0], ??, ??, ??;
    //  [  0,   0,   0], [127, 127, 127], [255, 255, 255], ??, ??, ??]
    Mat mImgShadowCopy = ConvertQImageToMat(qImg);
    QCOMPARE(mImgShadowCopy.data, qImg.bits());
    QCOMPARE(mImgShadowCopy.data[0], qImg.scanLine(0)[0]);
    QCOMPARE(mImgShadowCopy.data[1], qImg.scanLine(0)[1]);
    QCOMPARE(&(mImgShadowCopy.data[1]), &(qImg.scanLine(0)[1]));
    // check qImg pixel order
    QCOMPARE(qImg.scanLine(0)[0], 0);
    QCOMPARE(qImg.scanLine(0)[8], 0);
    QCOMPARE(qImg.scanLine(0)[2], 255);
    QCOMPARE(qImg.scanLine(0)[6], 255);
}

void QImageMatConvert::testCase01QImage2MatShadowCopyFor3ChannelImageCleanUp()
{
    std::swap(qImg.scanLine(0)[0], qImg.scanLine(0)[2]);
    std::swap(qImg.scanLine(0)[6], qImg.scanLine(0)[8]);
    QCOMPARE(qImg.scanLine(0)[0], 255);
    QCOMPARE(qImg.scanLine(0)[8], 255);
}

void QImageMatConvert::testCase01QImage2MatDeepCopyFor3ChannelImage()
{
    Mat mImgDeepCopy = ConvertQImageToMat(qImg, true);
    QCOMPARE(mImgDeepCopy.data == qImg.bits(), false);
    QCOMPARE(mImgDeepCopy.data[0], qImg.scanLine(0)[2]);
    QCOMPARE(mImgDeepCopy.data[1], qImg.scanLine(0)[1]);
    QCOMPARE(&(mImgDeepCopy.data[0]) == &(qImg.scanLine(0)[1]), false);
}

void QImageMatConvert::cleanupTestCase01For3ChannelImage() {}

void QImageMatConvert::initTestCase01For4ChannelImage()
{
    // RGBA_Test.png row: 2, col: 3, 4 channel, 8 bit, 32-bit for each pixel
    // Original Data(BGRA order):
    // [[  0,   0, 255, 255], [  0, 255,   0, 255], [255,   0,   0, 255];
    //  [  0,   0,   0, 255], [127, 127, 127, 255], [255, 255, 255, 255]]
    mImg = cv::imread("..//test//img//RGBA_Test.png", cv::IMREAD_UNCHANGED);
    QCOMPARE(mImg.rows, 2);
    QCOMPARE(mImg.cols, 3);
    QCOMPARE(mImg.dataend - mImg.datastart, 24);
    QCOMPARE(mImg.type(), CV_8UC4);
    QCOMPARE(mImg.data[2], 255);
    QCOMPARE(mImg.data[8], 255);
    QCOMPARE(mImg.data[17], 127);
    // QImage Data(Format_RGB32, BGRA order):
    // [[  0,   0, 255, 255], [  0, 255,   0, 255], [255,   0,   0, 255];
    //  [  0,   0,   0, 255], [127, 127, 127, 255], [255, 255, 255, 255]]
    qImg.load("..//test//img//RGBA_Test.png");
    QCOMPARE(qImg.format(), QImage::Format_ARGB32);
    QCOMPARE(qImg.sizeInBytes(), 24);
    QCOMPARE(qImg.bytesPerLine(), 12);
    QCOMPARE(qImg.scanLine(0)[2], 255);
    QCOMPARE(qImg.scanLine(0)[3], 255);
    QCOMPARE(qImg.scanLine(0)[17], 127);
}

void QImageMatConvert::testCase01Mat2QImageShadowCopyFor4ChannelImage()
{
    QImage qImgShadowCopy = ConvertMatToQImage(mImg);
    QCOMPARE(qImgShadowCopy.bits(), mImg.data);
    QCOMPARE(qImgShadowCopy.scanLine(0)[0], mImg.data[0]);
    QCOMPARE(qImgShadowCopy.scanLine(0)[1], mImg.data[1]);
    QCOMPARE(&(qImgShadowCopy.scanLine(0)[1]), &(mImg.data[1]));
}

void QImageMatConvert::testCase01Mat2QImageDeepCopyFor4ChannelImage()
{
    QImage qImgDeepCopy = ConvertMatToQImage(mImg, true);
    QCOMPARE(qImgDeepCopy.bits() == mImg.data, false);
    QCOMPARE(qImgDeepCopy.scanLine(0)[0], mImg.data[0]);
    QCOMPARE(qImgDeepCopy.scanLine(0)[1], mImg.data[1]);
    QCOMPARE(&(qImgDeepCopy.scanLine(0)[1]) == &(mImg.data[1]), false);
}

void QImageMatConvert::testCase01QImage2MatCopyFor4ChannelImage()
{
    Mat mImgShadowCopy = ConvertQImageToMat(qImg);
    QCOMPARE(mImgShadowCopy.data, qImg.bits());
    QCOMPARE(mImgShadowCopy.data[0], qImg.scanLine(0)[0]);
    QCOMPARE(mImgShadowCopy.data[1], qImg.scanLine(0)[1]);
    QCOMPARE(&(mImgShadowCopy.data[1]), &(qImg.scanLine(0)[1]));
}

void QImageMatConvert::testCase01QImage2MatDeepCopyFor4ChannelImage()
{
    Mat mImgDeepCopy = ConvertQImageToMat(qImg, true);
    QCOMPARE(mImgDeepCopy.data == qImg.bits(), false);
    QCOMPARE(mImgDeepCopy.data[0], qImg.scanLine(0)[0]);
    QCOMPARE(mImgDeepCopy.data[1], qImg.scanLine(0)[1]);
    QCOMPARE(&(mImgDeepCopy.data[0]) == &(qImg.scanLine(0)[1]), false);
}

void QImageMatConvert::cleanupTestCase01For4ChannelImage() {}

void QImageMatConvert::cleanupTestCase() {}

QTEST_APPLESS_MAIN(QImageMatConvert)

#include "tst_qimagematconvert.moc"
