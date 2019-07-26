#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	const auto image = imread("..\\_images\\1.jpg");

	namedWindow("方框滤波->原图");
	namedWindow("方框滤波->效果图");

	// 显示原图
	imshow("方框滤波->原图", image);

	// 进行方框滤波操作
	Mat out;
	boxFilter(image, out, -1, Size(5, 5));

	// 显示效果图
	imshow("方框滤波->效果图", out);

	waitKey(0);
	return 0;
}