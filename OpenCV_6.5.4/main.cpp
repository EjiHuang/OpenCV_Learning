#include <opencv2/opencv.hpp>
using namespace cv;

Mat g_src_image, g_dst_image, g_gray_image, g_mask_image;
int g_fill_mode = 1;		// 漫水填充的模式
int g_low_difference = 20;	// 负差最大值
int g_up_difference = 20;	// 正差最大值
int g_connectivity = 4;		// 表示floodFill函数标识符低八位的连通值
bool g_is_color = true;		// 是否为彩色图的标识符布尔值
bool g_is_use_mask = false;	// 是否显示掩膜窗口的布尔值
int g_new_mask_val = 255;	// 新的重绘的掩膜的像素值

static void show_help_text();
static void on_mouse(int event, int x, int y, int, void*);

int main() {
	system("color 2F");

	g_src_image = imread("..\\_images\\5.jpg", 1);
	if (!g_src_image.data)
	{
		std::cout << "Oh，no，读取srcImage错误~！ \n";
		return 0;
	}
	// 显示帮助文件
	show_help_text();

	g_src_image.copyTo(g_dst_image);
	cvtColor(g_src_image, g_gray_image, COLOR_BGR2GRAY);	// 转换三通道的image0到灰度图
	g_mask_image.create(g_src_image.rows + 2, g_src_image.cols + 2, CV_8UC1);// 利用image0的尺寸来初始化掩膜mask

	// 此句代码的OpenCV2版本为：
	// namedWindow("效果图", CV_WINDOW_AUTOSIZE);
	// 此句代码的OpenCV3版本为：
	namedWindow("效果图", WINDOW_AUTOSIZE);

	// 创建Trackbar
	createTrackbar("负差最大值", "效果图", &g_low_difference, 255, nullptr);
	createTrackbar("正差最大值", "效果图", &g_up_difference, 255, nullptr);

	// 鼠标回调函数
	setMouseCallback("效果图", on_mouse, nullptr);

	// 循环轮询按键
	while (true)
	{
		// 先显示效果图
		imshow("效果图", g_is_color ? g_dst_image : g_gray_image);

		// 获取键盘按键
		const auto key = waitKey(0);
		//判断ESC是否按下，若按下便退出
		if (27 == (255 & key))
		{
			std::cout << "程序退出...........\n";
			break;
		}

		// 根据按键不同，执行各种操作
		switch (static_cast<char>(key))
		{
			// 如果键盘“1”被按下，效果图在灰度图和彩色图之间切换
		case '1':
			if (g_is_color)	// 若原来为彩色，转为灰度图，并且将掩膜mask所有元素设置为0
			{
				std::cout << "键盘“1”被按下，切换彩色/灰度模式，当前操作为将【彩色模式】切换为【灰度模式】\n";
				cvtColor(g_src_image, g_gray_image, COLOR_BGR2GRAY);
				g_mask_image = Scalar::all(0);	// 将mask所有元素设置为0
				g_is_color = false;	// 将标识符设置为false，表示当前图像不为彩色，而是灰度
			}
			else // 若原来为灰度图，便将原来的彩图image0再次拷贝给image，并且将掩膜mask所有元素设置为0
			{
				std::cout << "键盘“1”被按下，切换彩色/灰度模式，当前操作为将【彩色模式】切换为【灰度模式】\n";
				g_src_image.copyTo(g_dst_image);
				g_mask_image = Scalar::all(0);
				g_is_color = true;	// 将标识符设置为true，表示当前图像模式为彩色
			}
			break;
			// 如果键盘按键“2”被按下，显示/隐藏掩膜窗口
		case '2':
			if (g_is_use_mask)
			{
				destroyWindow("mask");
				g_is_use_mask = false;
			}
			else
			{
				namedWindow("mask", 0);
				g_mask_image = Scalar::all(0);
				imshow("mask", g_mask_image);
				g_is_use_mask = true;
			}
			break;
			// 如果键盘按键“3”被按下，恢复原始图像
		case '3':
			std::cout << "按键“3”被按下，恢复原始图像\n";
			g_src_image.copyTo(g_dst_image);
			cvtColor(g_dst_image, g_gray_image, COLOR_BGR2GRAY);
			g_mask_image = Scalar::all(0);
			break;
			//如果键盘按键“4”被按下，使用空范围的漫水填充
		case '4':
			std::cout << "按键“4”被按下，使用空范围的漫水填充\n";
			g_fill_mode = 0;
			break;
			//如果键盘按键“5”被按下，使用渐变、固定范围的漫水填充
		case '5':
			std::cout << "按键“5”被按下，使用渐变、固定范围的漫水填充\n";
			g_fill_mode = 1;
			break;
			//如果键盘按键“6”被按下，使用渐变、浮动范围的漫水填充
		case '6':
			std::cout << "按键“6”被按下，使用渐变、浮动范围的漫水填充\n";
			g_fill_mode = 2;
			break;
			//如果键盘按键“7”被按下，操作标志符的低八位使用4位的连接模式
		case '7':
			std::cout << "按键“7”被按下，操作标志符的低八位使用4位的连接模式\n";
			g_connectivity = 4;
			break;
			//如果键盘按键“8”被按下，操作标志符的低八位使用8位的连接模式
		case '8':
			std::cout << "按键“8”被按下，操作标志符的低八位使用8位的连接模式\n";
			g_connectivity = 8;
			break;
		default:
			break;
		}
	}
	return 0;
}

void show_help_text()
{
	//输出一些帮助信息  
	printf("\n\n\t欢迎来到漫水填充示例程序~");
	printf("\n\n\t本示例根据鼠标选取的点搜索图像中与之颜色相近的点，并用不同颜色标注。");

	printf("\n\n\t按键操作说明: \n\n"
		"\t\t鼠标点击图中区域- 进行漫水填充操作\n"
		"\t\t键盘按键【ESC】- 退出程序\n"
		"\t\t键盘按键【1】-  切换彩色图/灰度图模式\n"
		"\t\t键盘按键【2】- 显示/隐藏掩膜窗口\n"
		"\t\t键盘按键【3】- 恢复原始图像\n"
		"\t\t键盘按键【4】- 使用空范围的漫水填充\n"
		"\t\t键盘按键【5】- 使用渐变、固定范围的漫水填充\n"
		"\t\t键盘按键【6】- 使用渐变、浮动范围的漫水填充\n"
		"\t\t键盘按键【7】- 操作标志符的低八位使用4位的连接模式\n"
		"\t\t键盘按键【8】- 操作标志符的低八位使用8位的连接模式\n\n");
}

void on_mouse(const int event, const int x, const int y, int, void*)
{
	// 若鼠标左键没有按下，便返回
	// 此句代码的OpenCV2版本为：
	// if (event != CV_EVENT_LBUTTONDOWN)
	// 此句代码的OpenCV3版本为：
	if (EVENT_LBUTTONDOWN != event)
		return;

	// -------------------【<1>调用floodFill函数之前的参数准备部分】---------------
	// 调用floodFill函数之前的参数准备部分
	const auto seed = Point(x, y);
	// 空范围的漫水填充，此值设为0，否则设为全局的g_low_difference
	auto low_difference = g_fill_mode == 0 ? 0 : g_low_difference;
	// 空范围的漫水填充，此值设为0，否则设为全局的g_up_difference
	const auto up_difference = g_fill_mode == 0 ? 0 : g_up_difference;

	// 标识符的0~7位为g_nConnectivity，8~15位为g_nNewMaskVal左移8位的值，16~23位为CV_FLOODFILL_FIXED_RANGE或者0。
	// 此句代码的OpenCV2版本为：
	// auto flags = g_connectivity + (g_new_mask_val << 8) + (g_fill_mode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
	// 此句代码的OpenCV3版本为：
	const auto flags = g_connectivity + (g_new_mask_val << 8) + (g_fill_mode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);

	// 随机生成bgr值
	const int b = 255 & static_cast<unsigned>(theRNG());	// 随机返回一个0~255之间的值
	const int g = 255 & static_cast<unsigned>(theRNG());
	const int r = 255 & static_cast<unsigned>(theRNG());
	Rect ccomp;	// 定义重绘区域的最小边界矩形区域

	// 在重绘区域像素的新值，若是彩色图模式，取Scalar(b, g, r)；
	// 若是灰度图模式，取Scalar(r*0.299 + g*0.587 + b*0.114)
	const auto new_val = g_is_color ? Scalar(b, g, r) : Scalar(r * 0.299 + g * 0.587 + b * 0.114);

	auto dst = g_is_color ? g_dst_image : g_gray_image;	// 目标图的赋值
	int area;

	// --------------------【<2>正式调用floodFill函数】-----------------------------
	if (g_is_use_mask)
	{
		// 此句代码的OpenCV2版本为：
		// threshold(g_mask_image, g_mask_image, 1, 128, CV_THRESH_BINARY);
		// 此句代码的OpenCV3版本为：
		threshold(g_mask_image, g_mask_image, 1, 128, THRESH_BINARY);
		area = floodFill(dst, g_mask_image, seed, new_val, &ccomp,
			Scalar(low_difference, low_difference, low_difference),
			Scalar(up_difference, up_difference, up_difference),
			flags);
		imshow("mask", g_mask_image);
	}
	else
	{
		area = floodFill(dst, seed, new_val, &ccomp,
			Scalar(low_difference, low_difference, low_difference),
			Scalar(up_difference, up_difference, up_difference),
			flags);
	}

	imshow("效果图", dst);
	std::cout << area << " 个像素被重绘\n";
}