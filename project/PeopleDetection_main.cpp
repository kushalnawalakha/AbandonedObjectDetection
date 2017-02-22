#include "Clustering.h"

int main_c()
{


	VideoCapture capture("d:\\out.avi");
	Clustering cluster;
	namedWindow("prueba");

	while (capture.grab())
	{
		Mat frame;
		capture.retrieve(frame);
//		cluster.clusterImage(frame);
	}
	capture.release();

}