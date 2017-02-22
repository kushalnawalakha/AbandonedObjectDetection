#include"header.h"

int peopleDescriptor(Mat img)
{

    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    vector<Rect> found;
    hog.detectMultiScale(img,found, 0, Size(8,8),Size(32,32),1.05,2);
	if(found.size()>1)
		return 1;
	else
		return 0;
}
