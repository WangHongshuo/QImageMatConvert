# Mat-QImage conversion
- This project based on Qt and opencv.
- The mwArray convert to Mat and QImage is moved to [HERE](https://github.com/WangHongshuo/mwArrayConvertToQImageMat).
## Introduction: ##

The QImage(Qt) and Mat(opencv) can be convert to each other in this function. It can use deep copy (the data don't share the same memory) or shadow copy (the data share the same memory) to do conversion.      

PAY ATTENTION: When the `Mat::channels == 3` or `QImage::format == QImage::Format_RGB888`, using shadow copy will change the src data, because the sequence of RGB is different between QImage and Mat.       

QImage(Qt) 和 Mat(opencv) 相互转化，可以通过深拷贝(data不共用一块内存)和浅拷贝(data共用一块内存)来进行转化。     
   
注意：当 `Mat::channels == 3` 或 `QImage::format == QImage::Format_RGB888` 时，进行浅拷贝会改变src的data，Mat和QImage的RGB排序不同。    

## Change Log: ##

- 2018.01.09:     

Set `mat_qimage_convert` to submodule.      

将`mat_qimage_convert`的转换独立为子模块。       

- 2018.01.08:      

Changed the variable names in `mat_qimage_convert` and added annotation. Tested all the function and fixed a small error.        

修改`mat_qimage_convert`中的变量名称，加入详细的说明，并对所有的转换进行了测试。修复了小错误。       

- 2017.12.16:

Updated` mat_qimage_convert.cpp` and now the Mat(QImage) can be converted to QImage(Mat) by deep copy(safer) or shallow copy(faster).

更新了 `mat_qimage_convert.cpp`，现在Mat和QImage可以用深拷贝（更安全）或浅拷贝（更快）的方式来进行转换。

- 2017.11.30:

Changed `cv::at` to `cv::ptr` in Mat-mwArray convert, but I didn't test it bucause I give up coding C++ with matlab.

将`Mat-mwArray`转换中`cv::at`访问改为`cv::ptr`访问，好像at比较慢，但是没有测试，因为我一个月前就放弃matlab混合编程了，太慢了

- 2017.11.13:

Added QImage-mwArray convert

添加QImage-mwArray转换


