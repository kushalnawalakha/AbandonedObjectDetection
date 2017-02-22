#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/video/background_segm.hpp>
#include<iostream>
#include<vector>
 using namespace std;
 using namespace cv;

int main(int argc, char *argv[])
{
    Mat frame;
    Mat bgmodel;
    Mat fg;
	Mat SL,LL,SM,DM,SF,LF,SV;
	//int x,y;
	int k = 10;
	int max = 100;
    //unsigned char sv[240*320];

	//VideoCapture cap("H:\\FinalProject\\dataset\\AVSS.mp4");
	
	VideoCapture cap("ds.mp4");
	
	
	int fcount = 0;
	cv::BackgroundSubtractorMOG2 slbg; 
	cv::BackgroundSubtractorMOG2 llbg;
	vector<vector<Point> > contours;

	namedWindow("SF");
	namedWindow("SL");
	namedWindow("LL");
	
	namedWindow("LF");
	namedWindow("Frame");
	
	

	for(;;)
	{
		cap >> frame;
		
		if(fcount < 50)
		{
			slbg.operator ()(frame,SF);
			slbg.getBackgroundImage(SL);
			llbg.operator ()(frame,LF);
			llbg.getBackgroundImage(LL);	

		}
		else
		{
			if(fcount % 20 == 0)
			{
			slbg.operator ()(frame,SF);
			slbg.getBackgroundImage(SL);
				
			}
			if(fcount % 80 == 0)
			{
			llbg.operator ()(frame,LF);
			llbg.getBackgroundImage(LL);	
				
			}
		}

		slbg.operator ()(frame,SF,0);
		llbg.operator ()(frame,LF,0);

	    erode(SF,SF,Mat());
		dilate(SF,SF,Mat());
	
	    erode(LF,LF,Mat());
		dilate(LF,LF,Mat());

		//GaussianBlur( SF,SF, Size( 3, 3 ), 0, 0 );
		//GaussianBlur( LF,LF, Size( 3, 3 ), 0, 0 );
		threshold(SF,SF,130,255,THRESH_BINARY);
		threshold(LF,LF,130,255,THRESH_BINARY);
		
		subtract(LF,SF,SV);

		findContours(SV,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

		for(auto i=0;i<contours.size();i++)
		{
			double area0 = contourArea(contours[i]);
			//cout<<area0<<endl;
			if(int(area0)>20)
			{
				Rect bound = boundingRect(contours[i]);
				rectangle(frame,bound,Scalar(0,255,0));
			}
		}


		//printf("%d\t",SF.rows);
		
		//Mat SV = Mat(SF.size(),CV_8UC3,sv);
		//threshold(SV,SV,128,255,THRESH_BINARY);
		imshow("SF",SF);
		imshow("SL",SL);
		imshow("LF",LF);
		imshow("LL",LL);
		
		imshow("SV",SV);
	    imshow("Frame",frame);
	    if(waitKey(30) == ' ') break;
		fcount++;
}
return 0;

}
