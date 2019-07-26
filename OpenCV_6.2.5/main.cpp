#include <opencv2/opencv.hpp>
using namespace cv;

// 全局变量
Mat g_src_image, g_dst_image1, g_dst_image2;
int g_median_blur_value = 10;		// 中值滤波参数值
int g_bilateral_filter_value = 10;	// 双边滤波参数值

// 全局函数
static void on_median_blur(int, void*);
static void on_bilateral_filter(int, void*);

int main() {
	system("color 5F");

	g_src_image = imread("..\\_images\\1.jpg", 1);
	if (!g_src_image.data)
	{
		std::cout << "Oh，no，读取srcImage错误~！ \n";
		return 0;
	}

	g_dst_image1 = g_src_image.clone();
	g_dst_image2 = g_src_image.clone();

	namedWindow("0.原图窗口", 1);
	imshow("0.原图窗口", g_src_image);

	namedWindow("1.中值滤波", 1);
	createTrackbar("内核值：", "1.中值滤波", &g_median_blur_value, 40, on_median_blur);
	on_median_blur(g_median_blur_value, nullptr);

	namedWindow("2.双边滤波", 1);
	createTrackbar("内核值：", "2.双边滤波", &g_bilateral_filter_value, 40, on_bilateral_filter);
	on_bilateral_filter(g_bilateral_filter_value, nullptr);

	// 输出一些帮助信息
	std::cout << std::endl << "\t运行成功，请调整滚动条观察图像效果~\n\n"
		<< "\t按下“q”键时，程序退出。\n";

	//按下“q”键时，程序退出
	while (char(waitKey(1)) != 'q') {}
	return 0;
}

void on_median_blur(int, void*)
{
	medianBlur(g_src_image, g_dst_image1, g_median_blur_value * 2 + 1);
	imshow("1.中值滤波", g_dst_image1);
}


void on_bilateral_filter(int, void*)
{
	bilateralFilter(g_src_image,
		g_dst_image2,
		g_bilateral_filter_value,
		2 * g_bilateral_filter_value,
		g_bilateral_filter_value / 2);
	imshow("2.双边滤波", g_dst_image2);
}
