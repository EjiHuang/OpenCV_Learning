#include <opencv2/opencv.hpp>
using namespace cv;

static void contrast_and_bright(int, void*);
int g_contrast_value;	// 对比度
int g_bright_value;		// 亮度值
Mat g_src_image, g_dst_image;

int main() {
	system("color 2F");

	// 读入用户提供的图像
	g_src_image = imread("..\\_images\\1.jpg");
	if (!g_src_image.data)
	{
		std::cout << "读取g_srcImage图片错误~！ \n";
		return false;
	}
	g_dst_image = Mat::zeros(g_src_image.size(), g_src_image.type());

	// 设定对比度和亮度的初值
	g_contrast_value = 80;
	g_bright_value = 80;

	// 创建窗口
	namedWindow("[效果图窗口]", 1);

	// 创建轨迹条
	createTrackbar("对比度：", "[效果图窗口]", &g_contrast_value, 300, contrast_and_bright);
	createTrackbar("亮  度：", "[效果图窗口]", &g_bright_value, 200, contrast_and_bright);

	// 调用回调函数
	contrast_and_bright(g_contrast_value, nullptr);
	contrast_and_bright(g_bright_value, nullptr);

	std::cout 
		<< "\t运行成功，请调整滚动条观察图像效果\n\n"
		<< "\t按下“q”键时，程序退出\n";

	while (char(waitKey(1))!='q'){}
	return  0;
}

void contrast_and_bright(int, void*)
{
	// 创建窗口
	namedWindow("[原始图窗口]", 1);
	// 三个for循环，执行运算g_dst_image(i,j) = a * g_src_image(i,j) + b
	for (auto y = 0; y < g_src_image.rows; ++y)
	{
		for (auto x = 0; x < g_src_image.cols; ++x)
		{
			for (auto c = 0; c < 3; ++c)
			{
				g_dst_image.at<Vec3b>(y, x)[c] = 
					saturate_cast<uchar>((g_contrast_value * 0.01) * (g_src_image.at<Vec3b>(y, x)[c]) + g_bright_value);
			}
		}
	}

	// 显示图像
	imshow("[原始图窗口]", g_src_image);
	imshow("[效果图窗口]", g_dst_image);
}
