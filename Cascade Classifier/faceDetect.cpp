// 2019�� 12�� x��.
// ��ǻ�� ���� ���� 
//
// �̵�� ��������� �а�
// 201421513 ���ν�.
// video���� face detect ����.

#include "stdafx.h"
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;


void detect_face(Mat src) {
	CascadeClassifier classifier("../_model/haarcascade_frontalface_default.xml");
	CascadeClassifier eye_classifier("../_model/haarcascade_eye.xml");
	vector<Rect> faces;
	classifier.detectMultiScale(src, faces);
	
	Mat image = imread("../_res/src.png");
	Mat image_gray = imread("../_res/src.png", IMREAD_GRAYSCALE);
	
	Mat imageg = imread("../_res/glass.jpg");
	Mat imageg_gray = imread("../_res/glass.jpg", IMREAD_GRAYSCALE);
	for (Rect rc : faces) {

		Mat imageRoi(src, Rect(rc.width-60 , rc.height-260, image.cols, image.rows));
		Mat mask(120 - image_gray);
		rectangle(src, rc, Scalar(255, 255, 0), 2); // face detect
		image.copyTo(imageRoi, mask); // ���� mask;
		
		/* -- �Ȱ��� ���� �ߴµ�, ���� ������ �߸��Ǽ� �Ȱ��� �������� ���ɴϴ�..
		�ּ�Ǯ�� �Ȱ��� ���ɴϴ�. �ٵ� �ٸ� �κе� ������ �����ϴ� ������ �ֽ��ϴ�..
		Mat faceRoi = src(rc);
		vector<Rect> eyes;
		eye_classifier.detectMultiScale(faceRoi, eyes);
		
		for (Rect eye : eyes) {
			Mat gimageRoi(src, Rect(eye.width + 310, eye.height + 350, imageg.cols, imageg.rows));
			Mat mask(120 - imageg_gray);
			imageg.copyTo(gimageRoi, mask);
			//Point center(eye.x + eye.width / 2, eye.y + eye.height / 2);
			//circle(faceRoi, center, eye.width / 2, Scalar(255, 0, 0), 2, LINE_AA);
		}
		*/
	}
	imshow("src", src);
}
int main()
{
	VideoCapture cap("../_res/insig.avi");

	if (!cap.isOpened()) {
		cerr << "Video open failed!" << endl;
		return 1;
	}

	double fps = cap.get(CAP_PROP_FPS);
	int delay = cvRound(100 / fps);

	Mat frame;
	Mat result;

	while (true) {
		cap >> frame;
		if (frame.empty())
			break;

		detect_face(frame);

		if (waitKey(delay) == 27)
			break;
	}
	waitKey();
    return 0;
}
