#include <QtTest>

// add necessary includes here
#include "../mat_qimage_convert.h"
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
    Mat matImg;
    QImage qImg;

private slots:
    void test_case1();
    void test_case2();
    void Mat2QImageWithData_data();
    void initTestCase();
    void cleanupTestCase();
};

QImageMatConvert::QImageMatConvert() {}

QImageMatConvert::~QImageMatConvert() {}

void QImageMatConvert::initTestCase() {}

void QImageMatConvert::cleanupTestCase() {}

void QImageMatConvert::test_case1() {}

void QImageMatConvert::test_case2() {}

void QImageMatConvert::Mat2QImageWithData_data() {}

QTEST_APPLESS_MAIN(QImageMatConvert)

#include "tst_qimagematconvert.moc"
