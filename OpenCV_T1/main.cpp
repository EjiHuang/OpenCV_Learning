#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	// [1] ����һ��ͼƬ
	Mat img = imread("1.jpg");
	// [2] �ڴ�������ʾ�����ͼƬ
	imshow("�������ͼƬ��", img);
	// [3] �ȴ�6000ms�󴰿��Զ��ر�
	waitKey(6000);
}