#include <opencv2/opencv.hpp>
using namespace cv;

bool roi_linear_blending()
{
	const auto src_image = imread("..\\_images\\dota_pa.jpg", 1);
	const auto logo_image = imread("..\\_images\\dota_logo.jpg");

	if (!src_image.data)
	{
		std::cout << "读取'..\\_images\\dota_pa.jpg'错误。\n";
		return false;
	}
	if (!logo_image.data)
	{
		std::cout << "读取'..\\_images\\dota_logo.jpg'错误。\n";
		return false;
	}

	// 定义一个Mat类型并给其设定ROI区域
	auto image_roi = src_image(Rect(200, 250, logo_image.cols, logo_image.rows));
	// 方法2
	// auto image_roi = src_image(Range(250, 250 + logo_image.rows), Range(200, 200 + logo_image.cols));

	// 将logo加到原图上
	addWeighted(image_roi, 0.5, logo_image, 0.3, 0., image_roi);

	// 显示结果
	imshow("区域线性图像混合示例窗口", src_image);

	return true;
}

int main() {
	roi_linear_blending();

	waitKey(0);
	return 0;
}