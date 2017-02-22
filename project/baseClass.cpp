#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/nonfree/features2d.hpp"
//#pragma comment(lib ,"opencv_features2d245d.lib")
//#pragma comment(lib ,"opencv_nonfree245d.lib")

using namespace cv ;
using namespace std;

class baseClass
{
public:
	
	Mat image1,image2;
	vector<int> jpeg;
	
	void SaveImage(char *name,Mat image)
	{
		jpeg.push_back(CV_IMWRITE_JPEG_QUALITY);
		jpeg.push_back(95);
		imwrite(name,image,jpeg);
	}
	int initializeVideo()
	{
		VideoCapture camera("E:\\highwayII_raw.avi");
		/*if(!camera->isOpened())
	    {
			cout << "No Camera" << endl;
			return -1;
		}*/
		return 0;
	}

	Mat updateImage(Mat image)
	{	VideoCapture camera("E:\\highwayII_raw.avi");
		
		camera >> image;
		cvtColor(image,image,CV_RGB2GRAY);
		GaussianBlur(image,image,Size(7,7),3,3);
		return image;
	}

	int background(int arg,char *args[])
	{	
		int i=initializeVideo();
		if(i==-1)
		{
			cout<<"camera closed";
			return -1;
		}

		image1=updateImage(image1);
		 int minHessian = 400;
  /*SurfFeatureDetector detector( minHessian );
  std::vector<KeyPoint> keypoints_1;
  detector.detect( image1, keypoints_1 );
  Mat img_keypoints_1; 
  drawKeypoints( image1, keypoints_1, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
  
  imshow("Keypoints 1", img_keypoints_1 );
  */
		 imshow("sdfjkh",image1);
		//camera->release();
		destroyAllWindows();
		return 0;
	}

};