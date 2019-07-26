#include <opencv2/opencv.hpp>
using namespace cv;

bool multi_channel_blending();

int main() {
	system("color 9F");

	if (multi_channel_blending())
	{
		std::cout << "\n运行成功，得出了需要的图像~! ";
	}

	waitKey(0);
	return 0;
}

bool multi_channel_blending()
{
	std::vector<Mat> channels;
	//=================【蓝色通道部分】=================
	//	描述：多通道混合-蓝色分量部分
	//============================================

	// 读入图片
	auto logo_image = imread("..\\_images\\dota_logo.jpg", 0);
	auto src_image = imread("..\\_images\\dota_jugg.jpg");

	if (!src_image.data)
	{
		std::cout << "读取'..\\_images\\dota_jugg.jpg'错误。\n";
		return false;
	}
	if (!logo_image.data)
	{
		std::cout << "读取'..\\_images\\dota_logo.jpg'错误。\n";
		return false;
	}

	// 把一个3通道图像转换成3个单通道图像
	split(src_image, channels);

	// 将原图的蓝色通道引用返回给image_blue_channel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
	const auto image_blue_channel = channels.at(0);
	// 将原图的蓝色通道的（500，250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageBlueChannel中
	addWeighted(image_blue_channel(Rect(500, 250, logo_image.cols, logo_image.rows)), 
		1.0,
		logo_image, 
		0.5, 
		0., 
		image_blue_channel(Rect(500, 250, logo_image.cols, logo_image.rows)));

	// 将3个单通道重新合并成一个三通道
	merge(channels, src_image);

	// 显示效果图
	namedWindow(" <1>游戏原画+logo蓝色通道");
	imshow(" <1>游戏原画+logo蓝色通道", src_image);


	//=================【绿色通道部分】=================
	//	描述：多通道混合-绿色分量部分
	//============================================

	// 重新读入图片
	logo_image = imread("..\\_images\\dota_logo.jpg", 0);
	src_image = imread("..\\_images\\dota_jugg.jpg");

	if (!src_image.data)
	{
		std::cout << "读取'..\\_images\\dota_jugg.jpg'错误。\n";
		return false;
	}
	if (!logo_image.data)
	{
		std::cout << "读取'..\\_images\\dota_logo.jpg'错误。\n";
		return false;
	}

	split(src_image, channels);
	const auto image_green_channel = channels.at(1);
	addWeighted(image_green_channel(Rect(500, 250, logo_image.cols, logo_image.rows)),
		1.0,
		logo_image,
		0.5,
		0.,
		image_green_channel(Rect(500, 250, logo_image.cols, logo_image.rows)));

	// 将3个单通道重新合并成一个三通道
	merge(channels, src_image);

	// 显示效果图
	namedWindow("<2>游戏原画+logo绿色通道");
	imshow("<2>游戏原画+logo绿色通道", src_image);


	//=================【红色通道部分】=================
	//	描述：多通道混合-红色分量部分
	//============================================

	// 重新读入图片
	logo_image = imread("..\\_images\\dota_logo.jpg", 0);
	src_image = imread("..\\_images\\dota_jugg.jpg");

	if (!src_image.data)
	{
		std::cout << "读取'..\\_images\\dota_jugg.jpg'错误。\n";
		return false;
	}
	if (!logo_image.data)
	{
		std::cout << "读取'..\\_images\\dota_logo.jpg'错误。\n";
		return false;
	}

	split(src_image, channels);
	const auto image_red_channel = channels.at(2);
	addWeighted(image_red_channel(Rect(500, 250, logo_image.cols, logo_image.rows)),
		1.0,
		logo_image,
		0.5,
		0.,
		image_red_channel(Rect(500, 250, logo_image.cols, logo_image.rows)));
	merge(channels, src_image);
	// 显示效果图
	namedWindow("<3>游戏原画+logo红色通道 ");
	imshow("<3>游戏原画+logo红色通道 ", src_image);

	return true;
}
