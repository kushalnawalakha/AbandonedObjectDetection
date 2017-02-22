#include"header.h"

int feature(Mat img_object,Mat img_scene)
{
  cvtColor(img_object,img_object,CV_RGB2GRAY);
  cvtColor(img_scene,img_scene,CV_RGB2GRAY);
  
  //-- Step 1: Detect the keypoints using SURF Detector

  int minHessian = 300;

  SurfFeatureDetector detector( minHessian );

  std::vector<KeyPoint> keypoints_object, keypoints_scene;

  detector.detect( img_object, keypoints_object );
  detector.detect( img_scene, keypoints_scene );

  //-- Step 2: Calculate descriptors (feature vectors)
  SurfDescriptorExtractor extractor;

  Mat descriptors_object, descriptors_scene;

  extractor.compute( img_object, keypoints_object, descriptors_object );
  extractor.compute( img_scene, keypoints_scene, descriptors_scene );

  Mat img_keypoints_1; Mat img_keypoints_2;

  drawKeypoints( img_object, keypoints_object, img_keypoints_1, Scalar::all(-1), DrawMatchesFlags::DEFAULT );
  drawKeypoints( img_scene, keypoints_scene, img_keypoints_2, Scalar::all(-1), DrawMatchesFlags::DEFAULT );

  //-- Show detected (drawn) keypoints
  imshow("Keypoints 1", img_keypoints_1 );
  imshow("Keypoints 2", img_keypoints_2 );

  /*FileStorage fo("keypoints_object.yml", FileStorage::APPEND);
  write( fo , "objects", keypoints_object );
  fo.release();
  */
  return 0;
  }



vector<Rect> peopleDiscriptor(Mat img)
{
	
    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    vector<Rect> found, found_filtered;
    //hog.detectMultiScale(img, found, 0, Size(8,8), Size(32,32), 1.05, 2);
	hog.detectMultiScale(img,found,0,Size(8,8),Size(0,0),1.05,2);
    size_t i, j;
    for( i = 0; i < found.size(); i++ )
    {
		Rect r = found[i];
        for( j = 0; j < found.size(); j++ )
			if( j != i && (r & found[j]) == r)
				break;
            if( j == found.size() )
                found_filtered.push_back(r);
	}
    for( i = 0; i < found_filtered.size(); i++ )
    {
		
		Rect r = found_filtered[i];
        r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);
        rectangle(img, r.tl(), r.br(), cv::Scalar(0,255,0), 3);
    }

     imshow("people detector", img);
	 return found_filtered;
}



int main1(int arg,char *args[])
{	

	cv::BackgroundSubtractorMOG2 bg;
	vector<vector<Point>> contours;
	Mat background,current,bgmodel,fg;;
	Rect r;
	int i=0,j=0,x=1,frame=0;

	vector<Rect> people;
	vector<Rect> object;

	VideoCapture camera1("easycampus.mp4");
	
	
	camera1>>background;
	

	while(true)
	{		
		Mat final(background.rows,background.cols,background.type());
		camera1>>current;

		if(waitKey(30)>=0)
		{
			break;
		}
		if(frame%10==0)
		{
			people=peopleDiscriptor(current);
			frame=0;
		}
		
		for(int cnt=0;cnt<people.size();cnt++)
		{
			r = people[i];
			r.x += cvRound(r.width*0.1);
	        r.width = cvRound(r.width*0.8);
	        r.y += cvRound(r.height*0.07);
	        r.height = cvRound(r.height*0.8);
			Mat f=final.adjustROI(r.y,r.y-r.height,r.x,r.x-r.width);
			//if(f.data!=NULL)
			//	feature(final,f);
		}

		bg.operator ()(current,fg);
		bg.getBackgroundImage(bgmodel);
		erode(fg,fg,Mat());
		dilate(fg,fg,Mat());
		findContours(fg,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);

		for(auto q=0;q<contours.size();q++)
		{
			double area0 = contourArea(contours[q]);
			if(int(area0)>50)
			{
				Rect bound = boundingRect(contours[q]);
				rectangle(final,bound,Scalar(0,255,0));
			}
		}
		
		cvtColor(current,current,CV_BGR2HSV);
		Mat i1;
		current.copyTo(i1);
		inRange(current,Scalar(38,60,70),Scalar(75, 181, 256),i1);
		GaussianBlur(i1,i1,Size(7,7),3,3);
		Mat e;
		current.copyTo(e);
		vector<Vec3f> circles;
		vector<cv::Rect> faces;

		//detectMultiScale(current,faces,1.1,3,0,Size(),Size());
		//HoughCircles(i1,circles,CV_HOUGH_GRADIENT,2,i1.rows / 4,100,50,10,400);


		for(i=0; i < circles.size(); i++) 
		{
			float x = circles.at(i).val[0];	
			float y = circles.at(i).val[1];	
			float r = circles.at(i).val[2];	
			circle(current,cvPoint(cvRound(x), cvRound(y)),3,CV_RGB(0,255,0), CV_FILLED);
			circle(current,cvPoint(cvRound(x), cvRound(y)),cvRound(r),CV_RGB(255,0,0),3);
		}
		imshow("final",final);
		imshow("contour detection",fg);
		imshow("hsv",current);
		imshow("i1",i1);
		frame++;
	}
	
	destroyAllWindows();

    return 0;
}