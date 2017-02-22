#include "ObjectFile.h"

int check(Rect current,Vector<ObjectFile> list)
{
	int i;

	for(i=0;i<list.size();i++)
	{
		if((abs(current.x-list[i].rect.x)<10)&&abs(current.width-list[i].rect.width)<10)
		{
			if((abs(current.y-list[i].rect.y)<10)&&abs(current.height-list[i].rect.width)<10)
			{
				return 1;
			}
		}
	}
	return 0;
}

Vector<ObjectFile> add(Rect current,Vector<ObjectFile>list)
{
	ObjectFile o;

	if(check(current,list)==0)
	{
		list.push_back(o.create(current));
	}
	return list;
}


Vector<ObjectFile> del(vector<vector<Point> > contours,Vector<ObjectFile>list)
{
	int i,j;

	Vector <ObjectFile>temp;
	ObjectFile o;
	for(j=0;j<contours.size();j++)
	{
		Rect current = boundingRect(contours[j]);
		for(i=0;i<list.size();i++)
		{
			if((abs(current.x-list[i].rect.x)<10)&&abs(current.width-list[i].rect.width)<10)
			{
				if((abs(current.y-list[i].rect.y)<10)&&abs(current.height-list[i].rect.width)<10)
				{
					temp.push_back(o.ObjectCopy(list[i]));
				}
			}
		}
			
		
	}
	return temp;
}