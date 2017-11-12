#include "mat_mwarray_convert.h"


mwArray mat2mwArray(const cv::Mat imgSrc)
{
    cv::Mat imgSrcs = imgSrc.clone();
    int h, w, c;
    h = imgSrcs.rows;
    w = imgSrcs.cols;
    c = imgSrcs.channels();
    if(c == 1) // gray
    {
        mwSize dims[2] = {w, h};
        mwArray pMat(2,dims,mxDOUBLE_CLASS);
        UINT8_T* x = (UINT8_T*)imgSrcs.data;
        pMat.SetData(x, h*w);
        return pMat;
    }
    else if(c == 3)
    {
        mwSize dims[3] = {h, w, c};
        mwArray pMat(3, dims, mxUINT8_CLASS);
        for (int i = 0; i < h; ++i)
        {
            for (int j = 0; j < w; ++j)
            {
                pMat(i+1,j+1,1) = (UINT8_T)imgSrcs.at<cv::Vec3b>(i,j)[2];
                pMat(i+1,j+1,2) = (UINT8_T)imgSrcs.at<cv::Vec3b>(i,j)[1];
                pMat(i+1,j+1,3) = (UINT8_T)imgSrcs.at<cv::Vec3b>(i,j)[0];

            }
        }
        return pMat;
    }

}

cv::Mat mwArray2mat(const mwArray data)
{
    mwArray dims = data.GetDimensions();
    int n = data.NumberOfDimensions();
    int M = dims(1);
    int N = dims(2);
    if (n == 2)
    {
        int h = M;
        int w = N;
        cv::Mat image(h, w, CV_8UC1);
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                int index = data(i+1,j+1);
                image.row(i).col(j).data[0] = index;
            }
        }
        return image;
    }
    else if (n == 3)
    {
        int h = M;
        int w = N;
        cv::Mat image(h, w, CV_8UC3);
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                image.at<cv::Vec3b>(i,j)[0] = (int)data.Get(3,i+1,j+1,3);
                image.at<cv::Vec3b>(i,j)[1] = (int)data.Get(3,i+1,j+1,2);
                image.at<cv::Vec3b>(i,j)[2] = (int)data.Get(3,i+1,j+1,1);
            }
        }
        return image;
    }
}
