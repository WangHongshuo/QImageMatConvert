# Mat-QImage Mat-mwArray and QImage-mwArray convert
- This project based on Matlab2015a X86, Qt and opencv.
## Introduction: ##

Mat(opencv)和QImage(Qt)以及mwArray(matlab)三个类的相互转换。     
Mat-QImage和Mat-mwArray来源于互联网，QImage-mwArray是自己写的，可能有疏忽的地方。     

Mat(opencv) and QImage(Qt), Mat and mwArray(Matlab), QImage and mwArray convert.       
Mat-QImage and Mat-mwArray are obtained from the Internet, QImage-mwArray is created by myself, so it's unstable (       

## Change Log: ##

- 2017.12.16:

Updated mat_qimage_convert.cpp and now the Mat(QImage) can be converted to QImage(Mat) by deep copy(safer) or shallow copy(faster).

更新了mat_qimage_convert.cpp，现在Mat和QImage可以用深拷贝（更安全）或浅拷贝（更快）的方式来进行转换。

- 2017.11.30:

Changed cv::at to cv::ptr in Mat-mwArray convert, but I didn't test it bucause I give up coding C++ with matlab.

将Mat-mwArray转换中cv::at访问改为cv::ptr访问，好像at比较慢，但是没有测试，因为我一个月前就放弃matlab混合编程了，太慢了

- 2017.11.13:

Added QImage-mwArray convert

添加QImage-mwArray转换


