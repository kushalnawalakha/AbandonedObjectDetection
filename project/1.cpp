#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int arg,char *args[])
{	
	int i=0;
	VideoCapture *camera = new VideoCapture(); 
	if(arg==1)
		camera->open(0);
	
	 if(!camera->isOpened())
    {
        cout << "No Camera" << endl;
        return -1;
    }
	
    Mat image1,image2;
	*camera>>image1;
	waitKey(300);
	*camera>>image1;
	cvtColor(image1,image1,CV_RGB2GRAY);
	GaussianBlur(image1,image1,Size(7,7),3,3);
	while(true)
	{
		if(i++%100==0)
		{
			*camera>>image1;
			cvtColor(image1,image1,CV_RGB2GRAY);
			GaussianBlur(image1,image1,Size(7,7),3,3);
		}

		*camera>>image2;
		GaussianBlur(image2,image2,Size(7,7),3,3);
		cvtColor(image2,image2,CV_RGB2GRAY);
		Mat final(image2.rows,image2.cols,image2.type());
		
		for(int i=0;i<image1.cols;i++)
		{
			for(int j=0;j<image1.rows;j++)
			{
				final.at<uchar>(j,i)=image2.at<uchar>(j, i)-image1.at<uchar>(j, i);

			}
		}
		if(waitKey(300)>=0)
		{
			break;
		}
		/*vector<int> jpeg;
		jpeg.push_back(CV_IMWRITE_JPEG_QUALITY);
		jpeg.push_back(95);
		imwrite("image1.jpeg",image1,jpeg);
		imwrite("image2.jpeg",image2,jpeg);
		threshold(final,final,128,255,CV_THRESH_BINARY | CV_THRESH_OTSU);
		imwrite("image3.jpeg",final,jpeg);
		*/

		imshow("final",final);
	}
	camera->release();
	destroyAllWindows();

    return 0;
}