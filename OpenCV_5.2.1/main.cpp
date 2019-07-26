#include <opencv2/opencv.hpp>
using namespace cv;

bool roi_add_image()
{
	const auto scr_image_1 = imread("..\\_images\\dota_pa.jpg");
	const auto logo_image = imread("..\\_images\\dota_logo.jpg");
	if (!scr_image_1.data)
	{
		std::cout << "读取 '..\\_images\\dota_pa.jpg' 错误" << std::endl;
		return false;
	}
	if (!logo_image.data)
	{
		std::cout << "读取 '..\\_images\\dota_logo.jpg' 错误" << std::endl;
		return false;
	}

	// 定义一个Mat类型并给其设定ROI区域
	auto image_roi = scr_image_1(Rect(200, 250, logo_image.cols, logo_image.rows));
	// 加载掩膜，必须是灰度图
	const auto mask = imread("..\\_images\\data_logo.jpg", 0);
	// 将掩膜拷贝到ROI
	logo_image.copyTo(image_roi, mask);

	// 显示结nnn果
	namedWindow("<1>利用ROI实现图像叠加示例窗口");
	imshow("<1>利用ROI实现图像叠加示例窗口", scr_image_1);

	return true;
}

int main() {
	roi_add_image();

	waitKey(0);
	return 0;
}
