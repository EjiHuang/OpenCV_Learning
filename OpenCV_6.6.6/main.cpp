#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	// 载入原始图片
	const auto src_image = imread("..\\_images\\6.jpg");
	Mat dst_image;
	const auto tmp_image = src_image;

	imshow("原始图", src_image);
	// 进行向上取样操作
	pyrUp(tmp_image, dst_image, Size(tmp_image.cols * 2, tmp_image.rows * 2));
	// 显示效果图
	imshow("向上取样操作->效果图", dst_image);

	// 进行向下取样操作
	pyrDown(tmp_image, dst_image, Size(tmp_image.cols / 2, tmp_image.rows / 2));
	imshow("向下取样操作->效果图", dst_image);

	waitKey(0);
	return 0;
}