#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	//-----------------------------------【一、图像的载入和显示】---------------------------------
	//	描述：以下三行代码用于完成图像的载入和显示
	//------------------------------------------------------------------------------------------

	Mat girl = imread("..\\_images\\girl.jpg");
	namedWindow("1.动漫图片");	// 创建一个带名称窗口
	imshow("1.动漫图片", girl);

	//-----------------------------------【二、初级图像混合】--------------------------------------
	//	描述：二、初级图像混合
	//-------------------------------------------------------------------------------------------

	Mat image = imread("..\\_images\\dota.jpg", 1);	// 载入3通道的彩色图像，flag不能为199，否则报错
	Mat logo = imread("..\\_images\\dota_logo.jpg");

	// 载入后先显示
	namedWindow("2.原图片");
	imshow("2.原图片", image);

	namedWindow("3.logo图");
	imshow("3.logo图", logo);

	// 定义一个Mat类型，用于存放图像的ROI
	Mat imageROI;
	// 方法1
	imageROI = image(Rect(800, 350, logo.cols, logo.rows));
	// 方法2
	// imageROI = image(Range(350, 350 + logo.rows), Range(800, 800 + logo.cols));

	// 将logo加到原图上
	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);

	// 显示结果
	namedWindow("4.原画 + logo图");
	imshow("4.原画 + logo图", image);

	//-----------------------------------【三、图像的输出】--------------------------------------
	//	描述：将一个Mat图像输出到图像文件
	//-----------------------------------------------------------------------------------------
	//输出一张jpg图片到工程目录下
	imwrite("由imwrite生成的图片.jpg", image);

	waitKey();

	return 0;
}