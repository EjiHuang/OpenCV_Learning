#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	const auto image = imread("..\\_images\\1.jpg");

	namedWindow("高斯滤波->原图");
	namedWindow("高斯滤波->效果图");

	// 显示原图
	imshow("高斯滤波->原图", image);

	// 进行方框滤波操作
	Mat out;
	GaussianBlur(image, out, Size(5, 5), 0, 0);

	// 显示效果图
	imshow("高斯滤波->效果图", out);

	waitKey(0);
	return 0;
}