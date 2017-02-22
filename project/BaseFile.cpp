#include"header.h"
#include"people.h"
#include"RectOperations.h"

int main(int argc, char *argv[])
{
	int a;
	Vector <ObjectFile> list;
    Mat frame,checkFrame,bgmodel,fg;
	Mat SL,LL,SM,DM,SF,LF,SV;
	Rect bound;
	int k = 10,people=0,max = 100;
	VideoCapture cap("ds.mp4");
	int fcount = 0;
	cv::BackgroundSubtractorMOG2 slbg; 
	cv::BackgroundSubtractorMOG2 llbg;
	vector<vector<Point> > contours;
	


	try
	{
		while(true)
		{
			cap >> frame;
			if(!frame.data)
			{
				cout<<"end";
				break;
			}
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
				if(int(area0)>20)
				{
					bound = boundingRect(contours[i]);
					checkFrame=frame(Rect(bound.x,bound.y,bound.width-bound.width%8,bound.height-bound.height%8));
					if(checkFrame.rows>23&&checkFrame.cols>23)
					{
						list=add(bound,list);
						if(peopleDescriptor(frame)==0)
						{
							rectangle(frame,bound,Scalar(0,255,0));
						}
					}
					{
						rectangle(frame,bound,Scalar(0,255,0));
					}
				}
			}
			if(fcount%1000==0)
			{
				list=del(contours,list);
			}
			imshow("SF",SF);
			imshow("SL",SL);
			imshow("LF",LF);
			imshow("LL",LL);
			imshow("SV",SV);
		    imshow("Frame",frame);
			if(waitKey(30) == ' ') break;
				fcount++;
		}
	}
	catch( std::exception& e )
	{
		cout<<"exception occured";
	}
return 0;
}
