//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <iostream>
//using namespace std;
//using namespace cv;
//
//#define IMAGE_WIDTH 640
//#define IMAGE_HEIGHT 480
//
//Mat src, resi, dst, cdst, can, erd, dil;
//
//int main (int argc, char** argv ) {
//    //Load the source image
//    src = imread(argv[1], 1);
//
//    resize(src, resi, Size(IMAGE_WIDTH, IMAGE_HEIGHT));
//
//
//    blur(resi, src, Size(3, 3));
//    imshow("blur", src);
//    waitKey();
//
//    Canny(src, can, 50, 200, 3);
//    //imshow("can", can);
//
//
//    int dilate_size = 6;
//    Mat elementD = getStructuringElement(cv::MORPH_CROSS,
//              cv::Size(2 * dilate_size + 1, 2 * dilate_size + 1),
//              cv::Point(dilate_size, dilate_size) );
//    dilate(can, dil, elementD);
//    //imshow("dil", dil);
//
//
//    int erosion_size = 7;
//    Mat elementE = getStructuringElement(cv::MORPH_CROSS,
//              cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
//              cv::Point(erosion_size, erosion_size) );
//    erode(dil, erd, elementE);
//    //imshow("erd", erd);
//
//    Mat erd1;
//    int erosion_size1 = 1;
//    Mat elementE1 = getStructuringElement(cv::MORPH_CROSS,
//              cv::Size(2 * erosion_size1 + 1, 2 * erosion_size1 + 1),
//              cv::Point(erosion_size1, erosion_size1) );
//    erode(erd, erd1, elementE1);
//    // imshow("erd1", erd1);
//
//
//    Mat dil1;
//    dilate(erd1, dil1, elementE1);
//    //imshow("dil1", dil1);
//
//
//    Mat sub1;
//    sub1 = erd - dil1;
//    //imshow("sub1", sub1);
//
//    blur(sub1, sub1, Size(3,3));
//
//
//    Mat lineMat = Mat::zeros( sub1.size(), CV_32F );
//    cvtColor(lineMat, lineMat, CV_GRAY2BGR);
//
//    // detect lines
//    vector<Vec2f> lines;
//    HoughLines(sub1, lines, 1, CV_PI/180*5, 150, 0, 0 );
//
//
//    // draw lines
//    for( size_t i = 0; i < lines.size(); i++ )
//    {
//        float rho = lines[i][0], theta = lines[i][1];
//        Point pt1, pt2;
//        double a = cos(theta), b = sin(theta);
//        double x0 = a*rho, y0 = b*rho;
//        pt1.x = cvRound(x0 + 1000*(-b));
//        pt1.y = cvRound(y0 + 1000*(a));
//        pt2.x = cvRound(x0 - 1000*(-b));
//        pt2.y = cvRound(y0 - 1000*(a));
//        line( resi, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
//        line( lineMat, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
//    }
//    // imshow("linemat", lineMat);
//
//    //Fill mask with value 128
//    Mat fillMat = Mat::zeros( sub1.rows + 2, sub1.cols + 2, CV_8U );
//    uchar fillValue = 128;
//    cv::floodFill(lineMat, fillMat, Point(IMAGE_WIDTH/2,IMAGE_HEIGHT/2), cv::Scalar(255) ,0, cv::Scalar(), cv::Scalar(), 4 | cv::FLOODFILL_MASK_ONLY | (fillValue << 8));
//    // imshow("fillmat", fillMat);
//
//    //
//    Rect roi(1,1,IMAGE_WIDTH,IMAGE_HEIGHT);
//    Mat fillMatROI(fillMat, roi);
//    Mat croppedFillMat;
//    fillMatROI.copyTo(croppedFillMat);
//
//    Mat subParLine;
//    subParLine = sub1 - croppedFillMat;
//    // imshow("subParLine", subParLine);
//
//    Mat diagLine = sub1 - subParLine;
//    // imshow("diagLine", diagLine);
//
//    vector<Vec2f> lines2;
//    HoughLines(diagLine, lines2, 1, CV_PI/180, 50, 0, 0);
//    for( size_t i = 0; i < lines2.size(); i++ )
//    {
//        float rho = lines2[i][0], theta = lines2[i][1];
//        Point pt1, pt2;
//        double a = cos(theta), b = sin(theta);
//        double x0 = a*rho, y0 = b*rho;
//        pt1.x = cvRound(x0 + 1000*(-b));
//        pt1.y = cvRound(y0 + 1000*(a));
//        pt2.x = cvRound(x0 - 1000*(-b));
//        pt2.y = cvRound(y0 - 1000*(a));
//        line( resi, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
//    }
//    //imshow("lineMat2", lineMat);
//
//    imshow("detected lines", resi);
//
//    waitKey();
//    return 0;
//}
