#include <opencv2/opencv.hpp>
using namespace cv;

// 全局变量
Mat g_src_image, g_dst_image1, g_dst_image2, g_dst_image3;
auto g_box_filter_value = 3;	// 方框滤波参数值
auto g_mean_blur_value = 3;		// 均值滤波参数值
auto g_gaussian_blur_value = 3;	// 高斯滤波参数值

// 全局函数
static void on_box_filter(int, void*);
static void on_mean_blur(int, void*);
static void on_gaussian_blur(int, void*);

int main() {
	system("color 5F");

	g_src_image = imread("..\\_images\\1.jpg", 1);
	if (!g_src_image.data)
	{
		std::cout << "Oh，no，读取srcImage错误~！ \n";
		return false;
	}

	g_dst_image1 = g_src_image.clone();
	g_dst_image2 = g_src_image.clone();
	g_dst_image3 = g_src_image.clone();

	namedWindow("0.原图窗口", 1);
	imshow("0.原图窗口", g_src_image);

	namedWindow("1.方框滤波", 1);
	createTrackbar("内核值：", "1.方框滤波", &g_box_filter_value, 40, on_box_filter);
	on_box_filter(g_box_filter_value, nullptr);

	namedWindow("2.均值滤波", 1);
	createTrackbar("内核值：", "2.均值滤波", &g_mean_blur_value, 40, on_mean_blur);
	on_mean_blur(g_mean_blur_value, nullptr);

	namedWindow("3.高斯滤波", 1);
	createTrackbar("内核值：", "3.高斯滤波", &g_gaussian_blur_value, 40, on_gaussian_blur);
	on_gaussian_blur(g_gaussian_blur_value, nullptr);

	//输出一些帮助信息
	std::cout << std::endl << "\t运行成功，请调整滚动条观察图像效果~\n\n"
		<< "\t按下“q”键时，程序退出。\n";

	//按下“q”键时，程序退出
	while (char(waitKey(1)) != 'q') {}
	return 0;
}

void on_box_filter(int, void*)
{
	boxFilter(g_src_image, 
		g_dst_image1, 
		-1, 
		Size(g_box_filter_value + 1, g_box_filter_value + 1));
	imshow("1.方框滤波", g_dst_image1);
}

void on_mean_blur(int, void*)
{
	blur(g_src_image, 
		g_dst_image2, 
		Size(g_mean_blur_value + 1, g_mean_blur_value + 1));
	imshow("2.均值滤波", g_dst_image2);
}

void on_gaussian_blur(int, void*)
{
	GaussianBlur(g_src_image, 
		g_dst_image3, 
		Size(g_gaussian_blur_value * 2 + 1, g_gaussian_blur_value * 2 + 1), 
		0, 
		0);
	imshow("3.高斯滤波", g_dst_image3);
}


