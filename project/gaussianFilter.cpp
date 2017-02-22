#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int arg,char *args[])
{
    VideoCapture *camera = new VideoCapture(); 
	double filter[3][3]={{0.1,0.1,0.1},{0.1,0.1,0.1},{0.1,0.1,0.1}};
	double frames=0,sum=0;

	int flag=0;
	if(arg==1);
	{
		camera->open(0);
	}
	

	 if(!camera->isOpened())
    {
        cout << "No Camera" << endl;
        return -1;
    }
	
    Mat image,blur,canny;

    namedWindow("Video");

    while(true)
    {
        *camera>>image;

		
		for(int i=0;i<image.cols-3;i++)
		{
			for(int j=0;j<image.cols-3;j++)
			{
				sum=0;
				for(int k=0;k<3;k++)
				{
					for(int l=0;l<3;l++)
					{
						for(int g=0;g<3;g++)
						{
							sum=sum+image.at<uchar>(i+k,j+g)*filter[g][l];
						}
					}
				}
				cout<<"before"<<image.at<uchar>(i,j);

			//blur.at<uchar>(i+1,j+1)=sum;
			cout<<"before"<<blur.at<uchar>(i+1,j+1);
			}
		}
		
        //imshow("Video",image);

//        GaussianBlur(image,blur,Size(7,7),3,3);
       // Canny(blur,canny,10,30,3);

       //imshow("cANNY",blur);

        if(waitKey(30)>=0 ||(flag==1 && frames<1))
        {
            break;
			camera->release();
        }

		frames--;

    }
	destroyAllWindows();

    return 0;
}