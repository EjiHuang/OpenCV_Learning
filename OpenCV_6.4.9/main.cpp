#include <opencv2/opencv.hpp>
using namespace cv;

Mat g_src_image, g_dst_image;
int g_element_shape = MORPH_RECT;

int g_max_iteration_num = 10;
int g_open_close_num = 0;
int g_erode_dilate_num = 0;
int g_top_black_hat_num = 0;

static void on_open_close(int, void*);
static void on_erode_dilate(int, void*);
static void on_top_black_hat(int, void*);

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

	namedWindow("【开运算/闭运算】", 1);
	namedWindow("【腐蚀/膨胀】", 1);
	namedWindow("【顶帽/黑帽】", 1);

	g_open_close_num = 9;
	g_erode_dilate_num = 9;
	g_top_black_hat_num = 2;

	createTrackbar("迭代值",
		"【开运算/闭运算】",
		&g_open_close_num,
		g_max_iteration_num * 2 + 1,
		on_open_close);
	createTrackbar("迭代值",
		"【腐蚀/膨胀】",
		&g_erode_dilate_num,
		g_max_iteration_num * 2 + 1,
		on_erode_dilate);
	createTrackbar("迭代值",
		"【顶帽/黑帽】",
		&g_top_black_hat_num,
		g_max_iteration_num * 2 + 1,
		on_top_black_hat);

	while (true)
	{
		on_open_close(g_open_close_num, nullptr);
		on_erode_dilate(g_erode_dilate_num, nullptr);
		on_top_black_hat(g_top_black_hat_num, nullptr);

		const auto key = waitKey(0);
		// 按下键盘按键Q或者ESC，程序退出
		if (static_cast<char>(key) == 'q' || static_cast<char>(key) == 27)
			break;
		// 按下键盘按键1，使用椭圆（Elliptic）结构元素MORPH_ELLIPSE
		if (static_cast<char>(key) == 49)
			g_element_shape = MORPH_ELLIPSE;
		// 按下键盘按键2，使用矩形（Rectangle）结构元素MORPH_RECT
		else if (static_cast<char>(key) == 50)
			g_element_shape = MORPH_RECT;
		// 按下键盘按键3，使用十字形（Cross-shaped）结构元素MORPH_CROSS
		else if (static_cast<char>(key) == 51)
			g_element_shape = MORPH_CROSS;
		// 按下键盘按键space，在矩形、椭圆、十字形结构元素中循环
		else if (static_cast<char>(key) == ' ')
			g_element_shape = (g_element_shape + 1 % 3);
	}

	return 0;
}

void on_open_close(int, void*)
{
	// 偏移量的定义
	const auto offset = g_open_close_num - g_max_iteration_num;	// 偏移量
	const auto absolute_offset = offset > 0 ? offset : -offset;	// 偏移量绝对值
	// 自定义核
	const auto element = getStructuringElement(g_element_shape,
		Size(absolute_offset * 2 + 1, absolute_offset * 2 + 1),
		Point(absolute_offset, absolute_offset));
	// 进行操作
	if (0 > offset)
	{
		// OpenCV2 version：
		// morphologyEx(g_src_image, g_dst_image, CV_MOP_OPEN, element);
		// OpenCV3 version:
		morphologyEx(g_src_image, g_dst_image, MORPH_OPEN, element);
	}
	else
	{
		// OpenCV2 version：
		// morphologyEx(g_src_image, g_dst_image, CV_MOP_CLOSE, element);
		// OpenCV3 version:
		morphologyEx(g_src_image, g_dst_image, MORPH_CLOSE, element);
	}

	imshow("【开运算/闭运算】", g_dst_image);
}

void on_erode_dilate(int, void*)
{
	// 偏移量的定义
	const auto offset = g_erode_dilate_num - g_max_iteration_num;	// 偏移量
	const auto absolute_offset = offset > 0 ? offset : -offset;	// 偏移量绝对值
	// 自定义核
	const auto element = getStructuringElement(g_element_shape,
		Size(absolute_offset * 2 + 1, absolute_offset * 2 + 1),
		Point(absolute_offset, absolute_offset));
	// 进行操作
	if (0 > offset)
		erode(g_src_image, g_dst_image, element);
	else
		dilate(g_src_image, g_dst_image, element);
	// 显示图像
	imshow("【腐蚀/膨胀】", g_dst_image);
}

void on_top_black_hat(int, void*)
{
	// 偏移量的定义
	const auto offset = g_top_black_hat_num - g_max_iteration_num;	// 偏移量
	const auto absolute_offset = offset > 0 ? offset : -offset;		// 偏移量的绝对值
	// 自定义核
	const auto element = getStructuringElement(g_element_shape,
		Size(absolute_offset * 2 + 1, absolute_offset * 2 + 1),
		Point(absolute_offset, absolute_offset));
	// 进行操作
	if (0 > offset)
		morphologyEx(g_src_image, g_dst_image, MORPH_TOPHAT, element);
	else
		morphologyEx(g_src_image, g_dst_image, MORPH_BLACKHAT, element);
	// 显示图像
	imshow("【顶帽/黑帽】", g_dst_image);
}


