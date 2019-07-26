#include <opencv2/opencv.hpp>
using namespace cv;

bool linear_blending()
{
	// 定义一些局部变量
	const auto alpha_value = 0.5;
	double beta_value;
	Mat dst_image;
	const auto src_image2 = imread("..\\_images\\mogu.jpg");
	const auto src_image3 = imread("..\\_images\\rain.jpg");

	if (!src_image2.data)
	{
		std::cout << "读取'..\\_images\\mogu.jpg'错误。\n";
		return false;
	}
	if (!src_image3.data)
	{
		std::cout << "读取'..\\_images\\rain.jpg'错误。\n";
		return false;
	}

	// 进行图像混合加权操作
	beta_value = (1.0 - alpha_value);
	addWeighted(src_image2, alpha_value, src_image3, beta_value, 0.0, dst_image);

	// 显示
	imshow("<2>线性混合示例窗口【原图】", src_image2);
	imshow("<3>线性混合示例窗口【效果图】", dst_image);

	return true;
}

int main() {
	linear_blending();

	waitKey(0);
	return  0;
}