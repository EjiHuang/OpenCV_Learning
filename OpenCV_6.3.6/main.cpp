#include <opencv2/opencv.hpp>
using namespace cv;

Mat g_src_image, g_dst_image;
int g_track_bar_number = 0;		// 0表示腐蚀erode，1表示膨胀dilate
int g_struct_element_size = 3;	// 结构元素（内核矩阵）的尺寸

void process();	// 膨胀和腐蚀的处理函数
void on_track_bar_num_change(int, void*);
void on_element_size_change(int, void*);

int main() {
	system("color 2F");

	g_src_image = imread("..\\_images\\3.jpg");
	if (!g_src_image.data)
	{
		std::cout << "Oh，no，读取srcImage错误~！ \n";
		return 0;
	}
	namedWindow("原图窗口", 1);
	imshow("原图窗口", g_src_image);

	// 进行初次腐蚀操作并显示效果图
	namedWindow("效果图");
	// 获取自定义核
	const auto element = getStructuringElement(MORPH_RECT, 
		Size(2 * g_struct_element_size + 1, 2 * g_struct_element_size + 1), 
		Point(g_struct_element_size, g_struct_element_size));
	erode(g_src_image, g_dst_image, element);
	imshow("效果图", g_dst_image);

	// 创建轨迹条
	createTrackbar("腐蚀/膨胀", "效果图", &g_track_bar_number, 1, on_track_bar_num_change);
	createTrackbar("内核尺寸", "效果图", &g_struct_element_size, 21, on_element_size_change);

	// 输出一些帮助信息
	std::cout << std::endl << "\t运行成功，请调整滚动条观察图像效果~\n\n"
		<< "\t按下“q”键时，程序退出。\n";

	//按下“q”键时，程序退出
	while (char(waitKey(1)) != 'q') {}
	return 0;
}

void process()
{
	// 获取自定义核
	auto element = getStructuringElement(MORPH_RECT, 
		Size(2 * g_struct_element_size + 1, 2 * g_struct_element_size + 1), 
		Point(g_struct_element_size, g_struct_element_size));

	// 进行腐蚀或膨胀操作
	if (g_track_bar_number == 0)
	{
		erode(g_src_image, g_dst_image, element);
	}
	else { dilate(g_src_image, g_dst_image, element); }

	// 显示效果图
	imshow("效果图", g_dst_image);
}

void on_element_size_change(int, void*)
{
	// 内核尺寸已改变，回调函数体内需调用一次Process函数，使改变后的效 果立即生效并显示出来
	process();
}

void on_track_bar_num_change(int, void*)
{
	//腐蚀和膨胀之间效果已经切换，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
	process();
}


