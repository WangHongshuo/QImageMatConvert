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
    uchar* array = nullptr;

private slots:
    void initTestCase();

    void initTestCase01ForGrayImage();
    void testCase01Mat2QImageShadowCopyForGrayImage();
    void testCase01Mat2QImageDeepCopyForGrayImage();
    void testCase01QImage2MatShadowCopyForGrayImage();
    void testCase01QImage2MatShadowDeepCopyForGrayImage();
    void cleanupTest01ForGrayImage();

    void initTestCase01For3ChannelImage();
    void testCase01Mat2QImageShadowCopyFor3ChannelImage();
    void testCase01Mat2QImageDeepCopyFor3ChannelImage();
    void testCase01QImage2MatShadowCopyFor3ChannelImage();
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

void QImageMatConvert::initTestCase() { initArray(); }

void QImageMatConvert::initTestCase01ForGrayImage()
{
    mImg = Mat(2, 2, CV_8UC1, array);
    qImg = QImage(array, 2, 2, QImage::Format_Indexed8);
}

void QImageMatConvert::testCase01Mat2QImageShadowCopyForGrayImage()
{
    QImage qImgShadowCopy = Mat2QImageShadowCopy(mImg);
    QCOMPARE(qImgShadowCopy.bits(), mImg.data);
    QCOMPARE(qImgShadowCopy.scanLine(0)[0], mImg.data[0]);
    QCOMPARE(qImgShadowCopy.scanLine(0)[1], mImg.data[1]);
    QCOMPARE(&(qImgShadowCopy.scanLine(0)[1]), &(mImg.data[1]));
    QCOMPARE(&(qImgShadowCopy.scanLine(0)[2]), &(array[2]));
    QCOMPARE(&(mImg.data[2]), &(array[2]));
}

void QImageMatConvert::testCase01Mat2QImageDeepCopyForGrayImage()
{
    QImage qImgDeepCopy = Mat2QImageDeepCopy(mImg);
    QCOMPARE(qImgDeepCopy.bits() == mImg.data, false);
    QCOMPARE(qImgDeepCopy.scanLine(0)[0], mImg.data[0]);
    QCOMPARE(qImgDeepCopy.scanLine(0)[1], mImg.data[1]);
    QCOMPARE(&(qImgDeepCopy.scanLine(0)[1]) == &(mImg.data[1]), false);
    QCOMPARE(&(qImgDeepCopy.scanLine(0)[2]) == &(array[2]), false);
    QCOMPARE(&(mImg.data[2]), &(array[2]));
}

void QImageMatConvert::testCase01QImage2MatShadowCopyForGrayImage()
{
    Mat mImgShadowCopy = QImage2MatShadowCopy(qImg);
    QCOMPARE(mImgShadowCopy.data, qImg.bits());
    QCOMPARE(mImgShadowCopy.data[0], qImg.scanLine(0)[0]);
    QCOMPARE(mImgShadowCopy.data[1], qImg.scanLine(0)[1]);
    QCOMPARE(&(mImgShadowCopy.data[1]), &(qImg.scanLine(0)[1]));
    QCOMPARE(&(mImgShadowCopy.data[2]), &(array[2]));
    QCOMPARE(&(mImg.data[2]), &(array[2]));
}

void QImageMatConvert::testCase01QImage2MatShadowDeepCopyForGrayImage()
{
    Mat mImgDeepCopy = QImage2MatDeepCopy(qImg);
    QCOMPARE(mImgDeepCopy.data == qImg.bits(), false);
    QCOMPARE(mImgDeepCopy.data[0], qImg.scanLine(0)[0]);
    QCOMPARE(mImgDeepCopy.data[1], qImg.scanLine(0)[1]);
    QCOMPARE(&(mImgDeepCopy.data[0]) == &(qImg.scanLine(0)[1]), false);
    QCOMPARE(&(mImgDeepCopy.data[2]) == &(array[2]), false);
    QCOMPARE(&(qImg.scanLine(0)[2]), &(array[2]));
}

void QImageMatConvert::cleanupTest01ForGrayImage() {}

void QImageMatConvert::initTestCase01For3ChannelImage()
{
    initArray();
    mImg = Mat(2, 2, CV_8UC3, array);
    qImg = QImage(array, 2, 2, QImage::Format_RGB888);
}

void QImageMatConvert::testCase01Mat2QImageShadowCopyFor3ChannelImage()
{
    initTestCase01For3ChannelImage();
    // mImg BGR: [[0, 1, 2], [3, 4, 5]; [6, 7, 8], [9, 10, 11]]
    // qImg RGB: [[2, 1, 0], [5, 4, 3]; [8, 7, 6], [11, 10, 9]]
    QImage qImgShadowCopy = Mat2QImageShadowCopy(mImg);
    QCOMPARE(qImgShadowCopy.bits(), mImg.data);
    QCOMPARE(qImgShadowCopy.scanLine(0)[0], mImg.data[0]);
    QCOMPARE(qImgShadowCopy.scanLine(0)[1], mImg.data[1]);
    QCOMPARE(&(qImgShadowCopy.scanLine(0)[1]), &(mImg.data[1]));
    QCOMPARE(&(qImgShadowCopy.scanLine(0)[2]), &(array[2]));
    QCOMPARE(&(mImg.data[2]), &(array[2]));
    QCOMPARE(array[2], 0);
}

void QImageMatConvert::testCase01Mat2QImageDeepCopyFor3ChannelImage()
{
    initTestCase01For3ChannelImage();
    // qImg BGR: [[0, 1, 2], [3, 4, 5]; [6, 7, 8], [9, 10, 11]]
    // mImg RGB: [[0, 1, 2], [3, 4, 5]; [6, 7, 8], [9, 10, 11]]
    QImage qImgDeepCopy = Mat2QImageDeepCopy(mImg);
    QCOMPARE(qImgDeepCopy.bits() == mImg.data, false);
    QCOMPARE(qImgDeepCopy.scanLine(0)[0], mImg.data[2]);
    QCOMPARE(qImgDeepCopy.scanLine(0)[1], mImg.data[1]);
    QCOMPARE(&(qImgDeepCopy.scanLine(0)[1]) == &(mImg.data[1]), false);
    QCOMPARE(&(qImgDeepCopy.scanLine(0)[2]) == &(array[2]), false);
    QCOMPARE(&(mImg.data[2]), &(array[2]));
    QCOMPARE(array[2], 2);
}

void QImageMatConvert::testCase01QImage2MatShadowCopyFor3ChannelImage()
{
    initTestCase01For3ChannelImage();
    // qImg BGR: [[0, 1, 2], [3, 4, 5]; [6, 7, 8], [9, 10, 11]]
    // mImg RGB: [[2, 1, 0], [5, 4, 3]; [8, 7, 6], [11, 10, 9]]
    Mat mImgShadowCopy = QImage2MatShadowCopy(qImg);
    QCOMPARE(mImgShadowCopy.data, qImg.bits());
    QCOMPARE(mImgShadowCopy.data[0], qImg.scanLine(0)[0]);
    QCOMPARE(mImgShadowCopy.data[1], qImg.scanLine(0)[1]);
    QCOMPARE(&(mImgShadowCopy.data[1]), &(qImg.scanLine(0)[1]));
    QCOMPARE(&(mImgShadowCopy.data[2]), &(array[2]));
    QCOMPARE(&(mImg.data[2]), &(array[2]));
    QCOMPARE(array[2], 0);
}

void QImageMatConvert::testCase01QImage2MatDeepCopyFor3ChannelImage()
{
    initTestCase01For3ChannelImage();
    // qImg BGR: [[0, 1, 2], [3, 4, 5]; [6, 7, 8], [9, 10, 11]]
    // mImg RGB: [[0, 1, 2], [3, 4, 5]; [6, 7, 8], [9, 10, 11]]
    Mat mImgDeepCopy = QImage2MatDeepCopy(qImg);
    QCOMPARE(mImgDeepCopy.data == qImg.bits(), false);
    QCOMPARE(mImgDeepCopy.data[0], qImg.scanLine(0)[2]);
    QCOMPARE(mImgDeepCopy.data[1], qImg.scanLine(0)[1]);
    QCOMPARE(&(mImgDeepCopy.data[0]) == &(qImg.scanLine(0)[1]), false);
    QCOMPARE(&(mImgDeepCopy.data[2]) == &(array[2]), false);
    QCOMPARE(&(qImg.scanLine(0)[2]), &(array[2]));
    QCOMPARE(array[2], 2);
}

void QImageMatConvert::cleanupTestCase01For3ChannelImage() {}

void QImageMatConvert::initTestCase01For4ChannelImage()
{
    initArray();
    mImg = Mat(2, 2, CV_8UC4, array);
    qImg = QImage(array, 2, 2, QImage::Format_ARGB32);
}

void QImageMatConvert::testCase01Mat2QImageShadowCopyFor4ChannelImage()
{
    QImage qImgShadowCopy = Mat2QImageShadowCopy(mImg);
    QCOMPARE(qImgShadowCopy.bits(), mImg.data);
    QCOMPARE(qImgShadowCopy.scanLine(0)[0], mImg.data[0]);
    QCOMPARE(qImgShadowCopy.scanLine(0)[1], mImg.data[1]);
    QCOMPARE(&(qImgShadowCopy.scanLine(0)[1]), &(mImg.data[1]));
    QCOMPARE(&(qImgShadowCopy.scanLine(0)[2]), &(array[2]));
    QCOMPARE(&(mImg.data[2]), &(array[2]));
    QCOMPARE(array[2], 2);
}

void QImageMatConvert::testCase01Mat2QImageDeepCopyFor4ChannelImage()
{
    QImage qImgDeepCopy = Mat2QImageDeepCopy(mImg);
    QCOMPARE(qImgDeepCopy.bits() == mImg.data, false);
    QCOMPARE(qImgDeepCopy.scanLine(0)[0], mImg.data[0]);
    QCOMPARE(qImgDeepCopy.scanLine(0)[1], mImg.data[1]);
    QCOMPARE(&(qImgDeepCopy.scanLine(0)[1]) == &(mImg.data[1]), false);
    QCOMPARE(&(qImgDeepCopy.scanLine(0)[2]) == &(array[2]), false);
    QCOMPARE(&(mImg.data[2]), &(array[2]));
    QCOMPARE(array[2], 2);
}

void QImageMatConvert::testCase01QImage2MatCopyFor4ChannelImage()
{
    Mat mImgShadowCopy = QImage2MatShadowCopy(qImg);
    QCOMPARE(mImgShadowCopy.data, qImg.bits());
    QCOMPARE(mImgShadowCopy.data[0], qImg.scanLine(0)[0]);
    QCOMPARE(mImgShadowCopy.data[1], qImg.scanLine(0)[1]);
    QCOMPARE(&(mImgShadowCopy.data[1]), &(qImg.scanLine(0)[1]));
    QCOMPARE(&(mImgShadowCopy.data[2]), &(array[2]));
    QCOMPARE(&(mImg.data[2]), &(array[2]));
    QCOMPARE(array[2], 2);
}

void QImageMatConvert::testCase01QImage2MatDeepCopyFor4ChannelImage()
{
    Mat mImgDeepCopy = QImage2MatDeepCopy(qImg);
    QCOMPARE(mImgDeepCopy.data == qImg.bits(), false);
    QCOMPARE(mImgDeepCopy.data[0], qImg.scanLine(0)[0]);
    QCOMPARE(mImgDeepCopy.data[1], qImg.scanLine(0)[1]);
    QCOMPARE(&(mImgDeepCopy.data[0]) == &(qImg.scanLine(0)[1]), false);
    QCOMPARE(&(mImgDeepCopy.data[2]) == &(array[2]), false);
    QCOMPARE(&(qImg.scanLine(0)[2]), &(array[2]));
    QCOMPARE(array[2], 2);
}

void QImageMatConvert::cleanupTestCase01For4ChannelImage() {}

void QImageMatConvert::cleanupTestCase() { delete[] array; }

void QImageMatConvert::initArray()
{
    if (array != nullptr) {
        delete[] array;
    }
    array = new uchar[16] { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
}

QTEST_APPLESS_MAIN(QImageMatConvert)

#include "tst_qimagematconvert.moc"
