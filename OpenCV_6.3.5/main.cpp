#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	auto image = imread("..\\_images\\22.jpg");
	namedWindow("膨胀操作&腐蚀操作->原图");
	namedWindow("膨胀操作->效果图");
	namedWindow("腐蚀操作->效果图");
	imshow("膨胀操作&腐蚀操作->原图", image);

	const auto element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out;

	// 进行膨胀操作
	dilate(image, out, element);
	imshow("膨胀操作->效果图", out);

	// 进行腐蚀操作
	erode(image, out, element);
	imshow("腐蚀操作->效果图", out);

	waitKey(0);
	return 0;
}