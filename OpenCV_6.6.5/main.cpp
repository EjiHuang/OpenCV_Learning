#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	// 载入原始图片
	const auto src_image = imread("..\\_images\\6.jpg");
	Mat dst_image1, dst_image2;
	const auto tmp_image = src_image;

	imshow("原图", src_image);

	// 进行尺寸调整操作
	resize(tmp_image, 
		dst_image1, 
		Size(tmp_image.cols / 2, tmp_image.rows / 2), 
		(0, 0), 
		(0, 0), 
		3);
	resize(tmp_image,
		dst_image2,
		Size(tmp_image.cols * 2, tmp_image.rows * 2),
		(0, 0),
		(0, 0),
		3);

	//显示效果图  
	imshow("【效果图】之一", dst_image1);
	imshow("【效果图】之二", dst_image2);
	
	waitKey(0);
	return 0;
}