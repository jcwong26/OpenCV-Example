#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;


int main()
{
	double scale = 3.0;

	//load pretrained model
	CascadeClassifier faceCascade;
	faceCascade.load("C:\\Users\\Jillian\\Documents\\OpenCV\\build\\install\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");

	VideoCapture cap(0);
	if (!cap.isOpened())
		return -1;

	for (;;)
	{
		Mat frame;
		cap >> frame;

		//convert colour frame to grayscale
		Mat grayscale;
		cvtColor(frame, grayscale, COLOR_BGR2GRAY);

		//scale webcam to workable size
		resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));

		vector<Rect> faces;
		faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

		for (Rect area : faces)
		{
			Scalar drawColor = Scalar(255, 0, 0);
			rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)), 
				Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)), drawColor);
		}

		imshow("Webcam Frame", frame);

		if (waitKey(30) >= 0)
			break;
	}

	return 0;
}