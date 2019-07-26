#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	const auto image = imread("..\\_images\\1.jpg");
	namedWindow("中值滤波&双边滤波->原图");
	namedWindow("中值滤波->效果图");
	namedWindow("双边滤波->效果图");

	imshow("中值滤波&双边滤波->原图", image);

	Mat out;
	medianBlur(image, out, 7);
	imshow("中值滤波->效果图", out);

	bilateralFilter(image, out, 25, 25 * 2, 25 / 2);
	imshow("双边滤波->效果图", out);

	waitKey(0);
	return 0;
}