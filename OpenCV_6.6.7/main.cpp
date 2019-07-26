#include <opencv2/opencv.hpp>
using namespace cv;

constexpr auto g_window_name = "程序窗口";
Mat g_src_image, g_dst_image, g_tmp_image;

static void show_help_text();

int main() {
	system("color 2F");
	show_help_text();

	g_src_image = imread("..\\_images\\6.jpg", 1);
	if (!g_src_image.data)
	{
		std::cout << "Oh，no，读取srcImage错误~！ \n";
		return 0;
	}

	// 创建显示窗口
	namedWindow(g_window_name, WINDOW_AUTOSIZE);
	imshow(g_window_name, g_src_image);

	// 参数赋值
	g_tmp_image = g_src_image;
	g_dst_image = g_tmp_image;

	auto key = 0;

	while (true)
	{
		key = waitKey(0);
		switch (key)
		{
		case 27:// 按键ESC
			return 0;
			break;
		case 'q':// 按键Q
			return 0;
			break;
		case 'a':// 按键A按下，调用pyrUp函数
			pyrUp(g_tmp_image, g_dst_image, Size(g_tmp_image.cols * 2, g_tmp_image.rows * 2));
			printf(">检测到按键【A】被按下，开始进行基于【pyrUp】函数的图片放大：图片尺寸×2 \n");
			break;
		case 'w':// 按键W按下，调用resize函数
			resize(g_tmp_image, g_dst_image, Size(g_tmp_image.cols * 2, g_tmp_image.rows * 2));
			printf(">检测到按键【W】被按下，开始进行基于【resize】函数的图片放大：图片尺寸×2 \n");
			break;
		case '1':// 按键1按下，调用resize函数
			resize(g_tmp_image, g_dst_image, Size(g_tmp_image.cols * 2, g_tmp_image.rows * 2));
			printf(">检测到按键【1】被按下，开始进行基于【resize】函数的图片放大：图片尺寸×2 \n");
			break;
		case '3':// 按键3按下，调用pyrUp函数
			pyrUp(g_tmp_image, g_dst_image, Size(g_tmp_image.cols * 2, g_tmp_image.rows * 2));
			printf(">检测到按键【3】被按下，开始进行基于【pyrUp】函数的图片放大：图片尺寸×2 \n");
			break;
		case 'd':// 按键D按下，调用pyrDown函数
			pyrDown(g_tmp_image, g_dst_image, Size(g_tmp_image.cols / 2, g_tmp_image.rows / 2));
			printf(">检测到按键【D】被按下，开始进行基于【pyrDown】函数的图片缩小：图片尺寸/2\n");
			break;
		case 's':// 按键S按下，调用resize函数
			resize(g_tmp_image, g_dst_image, Size(g_tmp_image.cols / 2, g_tmp_image.rows / 2));
			printf(">检测到按键【S】被按下，开始进行基于【resize】函数的图片缩小：图片尺寸/2\n");
			break;
		case '2':// 按键2按下，调用resize函数
			resize(g_tmp_image, g_dst_image, Size(g_tmp_image.cols / 2, g_tmp_image.rows / 2));
			printf(">检测到按键【2】被按下，开始进行基于【resize】函数的图片缩小：图片尺寸/2\n");
			break;
		case '4':
			pyrDown(g_tmp_image, g_dst_image, Size(g_tmp_image.cols / 2, g_tmp_image.rows / 2));
			printf(">检测到按键【4】被按下，开始进行基于【pyrDown】函数的图片缩小：图片尺寸/2\n");
			break;
		default: ;
		}
		// 显示变化后的图
		imshow(g_window_name, g_dst_image);
		// 将g_dst_image赋给g_tmp_image，方便下次循环
		g_tmp_image = g_dst_image;
	}
}

void show_help_text()
{
	//输出一些帮助信息
	printf("\n\t欢迎来到OpenCV图像金字塔和resize示例程序~\n\n");
	printf("\n\n\t按键操作说明: \n\n"
		"\t\t键盘按键【ESC】或者【Q】- 退出程序\n"
		"\t\t键盘按键【1】或者【W】- 进行基于【resize】函数的图片放大\n"
		"\t\t键盘按键【2】或者【S】- 进行基于【resize】函数的图片缩小\n"
		"\t\t键盘按键【3】或者【A】- 进行基于【pyrUp】函数的图片放大\n"
		"\t\t键盘按键【4】或者【D】- 进行基于【pyrDown】函数的图片缩小\n"
	);
}
