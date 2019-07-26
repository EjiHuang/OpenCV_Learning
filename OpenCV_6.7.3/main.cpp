#include <opencv2/opencv.hpp>
using namespace cv;

constexpr auto g_window_name = "程序窗口";
auto g_threshold_value = 100;
auto g_threshold_type = 3;
Mat g_src_image, g_gray_image, g_dst_image;

static void show_help_text();
void on_threshold(int, void*);

int main() {
	system("color 1F");
	show_help_text();

	g_src_image = imread("..\\_images\\5.jpg");
	imshow("原始图", g_src_image);

	// 留存一份原图的灰度图
	cvtColor(g_src_image, g_gray_image, COLOR_RGB2GRAY);
	// 创建窗口并显示原始图
	namedWindow(g_window_name, WINDOW_AUTOSIZE);
	// 创建滑动条来控制阈值
	createTrackbar("模式", g_window_name, &g_threshold_type, 4, on_threshold);
	createTrackbar("参数值", g_window_name, &g_threshold_value, 255, on_threshold);

	// 初始化自定义阈值回调函数
	on_threshold(0, nullptr);
	while (true)// ESC退出
	{
		const auto key = waitKey(20);
		if (static_cast<char>(key) == 27) { break; }
	}
}

void show_help_text()
{
	//输出一些帮助信息  
	printf("\n\t欢迎来到【基本阈值操作】示例程序~\n\n");
	printf("\n\t按键操作说明: \n\n"
		"\t\t键盘按键【ESC】- 退出程序\n"
		"\t\t滚动条模式0- 二进制阈值\n"
		"\t\t滚动条模式1- 反二进制阈值\n"
		"\t\t滚动条模式2- 截断阈值\n"
		"\t\t滚动条模式3- 反阈值化为0\n"
		"\t\t滚动条模式4- 阈值化为0\n");
}

void on_threshold(int, void*)
{
	// 调用阈值函数
	threshold(g_src_image, g_dst_image, g_threshold_value, 255, g_threshold_type);

	// 更新效果图
	imshow(g_window_name, g_dst_image);
}

