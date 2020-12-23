#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    //if ( argc != 2 )
    //{
    //    printf("usage: DisplayImage.out <Image_Path>\n");
    //    return -1;
    //}

    //Mat image;
    //image = imread( argv[1], 1);
    //std::cout<<image.row(1)<<std::endl;
    Mat D(2,9, 1, Scalar(0,0,255));
    std::cout<<D<<std::endl;
    std::cout<<D.dims<<std::endl;
    for(int i = 0; i < D.rows * D.cols; i++){
       std::cout<<(int)D.data[i]<<std::endl;
    }
    std::cout<<D.rows<<std::endl;

    //if ( !image.data )
    //{
    //    printf("No image data \n");
    //    return -1;
    //}


    //namedWindow("Display Image", WINDOW_AUTOSIZE );
    //imshow("Display Image", image);

    //waitKey(0);

    return 0;
}
