#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	const auto src = imread("..\\_images\\4.jpg");
	imshow("ԭʼͼ", src);
	Rect ccomp;
	floodFill(src, 
		Point(50, 300), 
		Scalar(155, 255, 55), 
		&ccomp, 
		Scalar(20, 20, 20), 
		Scalar(20, 20, 20));
	imshow("Ч��ͼ", src);

	waitKey(0);
	return 0;
}