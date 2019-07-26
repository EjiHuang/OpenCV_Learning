#include <opencv2/opencv.hpp>
using namespace cv;

/*
	载入图像，将其转换成灰度图，在用blur函数进行图像模糊以降噪
	然后用canny函数进行边缘检测
*/

int main() {
	// 读入一张图片
	Mat srcImage = imread("..\\_images\\1.jpg");
	
	// 显示原始图片
	imshow("Source image", srcImage);

	// 参数定义
	Mat edge, grayImage;

	// 将原图像转换为灰度图像
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	// 先用3x3内核来降噪
	blur(grayImage, edge, Size(3, 3));

	// 运行Canny算子
	Canny(edge, edge, 3, 9, 3);

	// 显示效果图
	imshow("Final image(Blur - Canny)", edge);

	waitKey(0);
	return 0;
}