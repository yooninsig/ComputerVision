// 2019년 12월 x일.
// 컴퓨터 비전 과제 
//
// 미디어 기술콘텐츠 학과
// 201421513 윤인식.
// video에서 face detect 예제.

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
		image.copyTo(imageRoi, mask); // 모자 mask;
		
		/* -- 안경은 구현 했는데, 눈알 검출이 잘못되서 안경이 복수개가 나옵니다..
		주석풀면 안경은 나옵니다. 근데 다른 부분도 눈으로 검출하는 오류가 있습니다..
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
