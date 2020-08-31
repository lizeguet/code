#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char **argv)
{
	IplImage* image;
	IplImage* colorImg;

	const char *filename = "F:\\小模数塑料齿轮\\比列因子棋盘图\\12000-1.bmp";
	if (argc == 2)
	{
		image = cvLoadImage(argv[1], 0);
	}
	else
	{
		image = cvLoadImage(filename, 0);
	}
	colorImg = cvCreateImage(cvGetSize(image), 8, 3);
	cvCvtColor(image, colorImg, CV_GRAY2BGR);


	CvSize pattern_size;
	pattern_size.height = 11;
	pattern_size.width = 8 ;

	int win_size = 7;

	CvPoint2D32f *corners = new CvPoint2D32f[pattern_size.height*pattern_size.width];
	int corner_count;

	if (0==cvFindChessboardCorners(image,pattern_size,corners,&corner_count, CV_CALIB_CB_FILTER_QUADS));
	{
		cout << "提取角点失败"<< endl;
	}

	for (int i = 0; i<corner_count; i++)
	{
		cout << corners[i].x << "  " << corners[i].y << endl;
		//cvCircle(colorImg, cvPoint(cvRound(corners[i].x), cvRound(corners[i].y)),0,CV_RGB(0,255,0), 1,8,0);
		cvLine(colorImg, cvPoint(cvRound(corners[i].x - 7), cvRound(corners[i].y)), cvPoint(cvRound(corners[i].x + 7), cvRound(corners[i].y)), CV_RGB(0, 255, 0), 1, 8, 0);
		cvLine(colorImg, cvPoint(cvRound(corners[i].x), cvRound(corners[i].y - 7)), cvPoint(cvRound(corners[i].x), cvRound(corners[i].y + 7)), CV_RGB(0, 255, 0), 1, 8, 0);
	}


	cvFindCornerSubPix(image, corners, corner_count,
		cvSize(win_size, win_size), cvSize(-1, -1),
		cvTermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10, 0.03));


	//for (int i = 0; i<corner_count; i++)
	//{
	//	//cvCircle(colorImg, cvPoint(cvRound(corners[i].x), cvRound(corners[i].y)),0,CV_RGB(255,0,0), 1,8,0);
	//	cvLine(colorImg, cvPoint(cvRound(corners[i].x - 5), cvRound(corners[i].y)), cvPoint(cvRound(corners[i].x + 5), cvRound(corners[i].y)), CV_RGB(255, 0, 0), 1, 8, 0);
	//	cvLine(colorImg, cvPoint(cvRound(corners[i].x), cvRound(corners[i].y - 5)), cvPoint(cvRound(corners[i].x), cvRound(corners[i].y + 5)), CV_RGB(255, 0, 0), 1, 8, 0);
	//	cout << corners[i].x << "  " << corners[i].y << endl;
	//}

	cvSaveImage("corner.bmp", colorImg);

	cout << corner_count << endl;

	cvShowImage("detect", colorImg);
	cvWaitKey();

	cvReleaseImage(&colorImg);
	cvReleaseImage(&image);

	return 0;
}