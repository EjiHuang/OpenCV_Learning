#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	// [1] ����ԭʼͼƬ
	Mat srcImage = imread("1.jpg");

	// [2] �ڴ�������ʾ�����ͼƬ
	imshow("��ֵ�˲���ԭͼ��", srcImage);

	// [3] ���о�ֵ�˲�����
	Mat dstImage;
	blur(srcImage, dstImage, Size(7, 7));

	// [4] ��ʾЧ��ͼ
	imshow("��ֵ�˲���Ч��ͼ��", dstImage);

	waitKey(0);
}