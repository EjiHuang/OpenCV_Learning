#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	const auto src_image = imread("..\\_images\\1.jpg", 1);
	Mat dstImage;
	cvtColor(src_image, dstImage, COLOR_BGR2GRAY);
	imshow("Ð§¹ûÍ¼", dstImage);

	waitKey();
	return 0;
}