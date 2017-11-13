#include "mwarray_qimage_convert.h"
#include <QDebug>

QImage mwArray2QImage(const mwArray input)
{
    mwArray mw_array_size = input.GetDimensions();
    int c = input.NumberOfDimensions();
    int row = mw_array_size(1);
    int col = mw_array_size(2);

    if(c == 2)
    {
        int h = row;
        int w = col;
        QImage Q_img(w,h,QImage::Format_Indexed8);
        // set color count
        Q_img.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            Q_img.setColor(i, qRgb(i, i, i));
        }
        for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
//                int a = input.Get(2,i+1,j+1);
//                qDebug() << a;
                *(Q_img.scanLine(i)+j) = input.Get(2,i+1,j+1);
//                qDebug() << *(Q_img.scanLine(i)+j);
            }
        }
        return Q_img;
    }
    else if(c == 3)
    {
        int h = row;
        int w = col;
        QImage Q_img(w,h,QImage::Format_RGB888);
        for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
                //
                *(Q_img.scanLine(i)+(j*3)) = input.Get(3,i+1,j+1,3);
                *(Q_img.scanLine(i)+(j*3)+1) = input.Get(3,i+1,j+1,2);
                *(Q_img.scanLine(i)+(j*3)+2) = input.Get(3,i+1,j+1,1);
            }
        }
        return Q_img;
    }
}

mwArray QImage2mwArray(QImage input)
{
    int h, w;
    h = input.height();
    w = input.width();
//    qDebug() << input.format();
    switch(input.format())
    {
    // 4 channel L to H: BGRA remove A
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
    {
        mwSize dims[3] = {h,w,3};
        mwArray mw_array(3,dims,mxUINT8_CLASS);
        for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
                //RGB
                mw_array(i+1,j+1,1) = (UINT8_T)(*(input.scanLine(i)+(j*4)+2));
                mw_array(i+1,j+1,2) = (UINT8_T)(*(input.scanLine(i)+(j*4)+1));
                mw_array(i+1,j+1,3) = (UINT8_T)(*(input.scanLine(i)+(j*4)));
            }
        }
        return mw_array;
    }

    // 3 channel
    case QImage::Format_RGB888:
    {
        mwSize dims[3] = {h,w,3};
        mwArray mw_array(3,dims,mxUINT8_CLASS);
        for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
                //RGB
                mw_array(i+1,j+1,1) = (UINT8_T)(*(input.scanLine(i)+(j*3)+2));
                mw_array(i+1,j+1,2) = (UINT8_T)(*(input.scanLine(i)+(j*3)+1));
                mw_array(i+1,j+1,3) = (UINT8_T)(*(input.scanLine(i)+(j*3)));
            }
        }
        return mw_array;
    }

     // 1 channel
    case QImage::Format_Indexed8:
    {
        mwArray mw_array(h,w,mxUINT8_CLASS);
        for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
                mw_array(i+1,j+1) = (UINT8_T)(*(input.scanLine(i)+j));
                //                qDebug() << *(input.scanLine(i)+j);
            }
        }

        // test
//        int a;
//        for (int i=1;i<3;i++)
//        {
//            // ?,row,col
//            a = mw_array.Get(2,1,i);
//            qDebug() << a;
//        }
        return mw_array;
    }
    }
}
