#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	Mat srcImage = imread("1.jpg");		// 载入图像
	imshow("Source image", srcImage);	// 显示图像
	waitKey(0);	// 等待按下任意键
}