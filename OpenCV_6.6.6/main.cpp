#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	// ����ԭʼͼƬ
	const auto src_image = imread("..\\_images\\6.jpg");
	Mat dst_image;
	const auto tmp_image = src_image;

	imshow("ԭʼͼ", src_image);
	// ��������ȡ������
	pyrUp(tmp_image, dst_image, Size(tmp_image.cols * 2, tmp_image.rows * 2));
	// ��ʾЧ��ͼ
	imshow("����ȡ������->Ч��ͼ", dst_image);

	// ��������ȡ������
	pyrDown(tmp_image, dst_image, Size(tmp_image.cols / 2, tmp_image.rows / 2));
	imshow("����ȡ������->Ч��ͼ", dst_image);

	waitKey(0);
	return 0;
}