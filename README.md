# Mat-QImage_Mat_mwArray_convert

Mat(opencv)和QImage(Qt)以及mwArray(matlab)三个类的相互转换。

Mat(opencv) and QImage(Qt), Mat and mwArray(Matlab), QImage and mwArray convert.

Mat-QImage和Mat-mwArray来源于互联网，QImage-mwArray是自己写的，可能有疏忽的地方。

Mat-QImage and Mat-mwArray are obtained from the Internet, QImage-mwArray is created by myself, so it's unstable (

2017.11.13:

添加QImage-mwArray转换

add QImage-mwArray convert

2017.11.30

将Mat-mwArray转换中cv::at访问改为cv::ptr访问，好像at比较慢，但是没有测试，因为我一个月前就放弃matlab混合编程了，太慢了

Changed cv::at to cv::ptr in Mat-mwArray convert, but I didn't test it bucause I give up coding C++ with matlab.
