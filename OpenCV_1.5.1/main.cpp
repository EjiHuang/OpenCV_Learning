#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	Mat srcImage = imread("1.jpg");		// ����ͼ��
	imshow("Source image", srcImage);	// ��ʾͼ��
	waitKey(0);	// �ȴ����������
}