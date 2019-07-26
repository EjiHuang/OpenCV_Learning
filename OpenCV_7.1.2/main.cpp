#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	const auto src_image = imread("..\\_images\\10.jpg");
	const auto src_image1 = src_image.clone();

	imshow("【原始图】Canny边缘检测", src_image);

	//----------------------------------------------------------------------------------
	//	一、最简单的canny用法，拿到原图后直接用。
	//	注意：此方法在OpenCV2中可用，在OpenCV3中已失效
	//----------------------------------------------------------------------------------
	//Canny( srcImage, srcImage, 150, 100,3 );
	//imshow("【效果图】Canny边缘检测", srcImage); 

	//----------------------------------------------------------------------------------
	//	二、高阶的canny用法，转成灰度图，降噪，用canny，最后将得到的边缘作为掩码，拷贝原图到效果图上，
	//  得到彩色的边缘图
	//----------------------------------------------------------------------------------
	Mat dst_image, edge, gray_image;

	// 1.创建于src同类型和大小的矩阵（dst）
	dst_image.create(src_image1.size(), src_image1.type());
	// 2.将原图像转换位灰度图像
	cvtColor(src_image1, gray_image, COLOR_BGR2GRAY);
	// 3.先使用 3x3内核来降噪
	blur(gray_image, edge, Size(3, 3));
	// 4.运行Canny算子
	Canny(edge, edge, 3, 9, 3);
	// 5.将g_dst_image内的所有元素置零
	dst_image = Scalar::all(0);
	// 6.使用Canny算子输出的边缘图g_canny_detected_edges作为掩码，
	//   来将原图g_src_image拷贝到目标图g_dst_image中
	src_image1.copyTo(dst_image, edge);
	// 7.显示效果图
	imshow("【效果图】Canny边缘检测2", dst_image);

	waitKey(0);
	return 0;
}