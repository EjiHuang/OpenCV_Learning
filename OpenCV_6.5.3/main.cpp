#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	const auto src = imread("..\\_images\\4.jpg");
	imshow("原始图", src);
	Rect ccomp;
	floodFill(src, 
		Point(50, 300), 
		Scalar(155, 255, 55), 
		&ccomp, 
		Scalar(20, 20, 20), 
		Scalar(20, 20, 20));
	imshow("效果图", src);

	waitKey(0);
	return 0;
}