#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	// ����ԭʼͼƬ
	const auto src_image = imread("..\\_images\\6.jpg");
	Mat dst_image1, dst_image2;
	const auto tmp_image = src_image;

	imshow("ԭͼ", src_image);

	// ���гߴ��������
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

	//��ʾЧ��ͼ  
	imshow("��Ч��ͼ��֮һ", dst_image1);
	imshow("��Ч��ͼ��֮��", dst_image2);
	
	waitKey(0);
	return 0;
}