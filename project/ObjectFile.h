#include"header.h"


class ObjectFile
{
private:
	ObjectFile(Rect r)
	{
		rect=r;
		time_t now = time(0);
		t = ctime(&now);
	}
	ObjectFile(Rect r,char *temp)
	{
		rect=r;
		t = temp;
		cout<<" " <<temp;
	}
public:
	Rect rect;
	char *t;
	ObjectFile()
	{
	}
	
	ObjectFile create(Rect r)
	{
		ObjectFile temp(r);
		return temp;
	}

	ObjectFile ObjectCopy(ObjectFile obj)
	{
		ObjectFile temp(obj.rect,obj.t);
		return temp;
	}
};