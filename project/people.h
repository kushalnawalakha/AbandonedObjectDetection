#include"header.h"

CascadeClassifier face_cascade("haarcascade_mcs_upperbody.xml");

int peopleDescriptor(Mat img)
{
	Mat greyscale;
	cvtColor(img,greyscale, CV_BGR2GRAY);

    //HOGDescriptor hog;
    //hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    vector<Rect> found;
	
	
	
	try
	{
		
		cvtColor(img,img, CV_BGR2GRAY );
		face_cascade.detectMultiScale(img,found,1.05,3,0,Size(24,24),Size(48,48));

		//(winSize - blockSize) % blockStride == 0
		//hog.detectMultiScale(img,found, 0,Size(8,8),Size(0,0),1.05,2);

		if(found.size()>0)
		{
			cout<<"person dtected"<<found.size()<<endl;
			return 1;
		}
		else
			return 0;	
		
	}
	catch( std::exception& e )
	{
		cout<<"exception occured";
	}
	return 0;
	
}