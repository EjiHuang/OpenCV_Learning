#include <opencv2/opencv.hpp>
using namespace cv;

/*
	����ͼ�񣬽���ת���ɻҶ�ͼ������blur��������ͼ��ģ���Խ���
	Ȼ����canny�������б�Ե���
*/

int main() {
	// ����һ��ͼƬ
	Mat srcImage = imread("..\\_images\\1.jpg");
	
	// ��ʾԭʼͼƬ
	imshow("Source image", srcImage);

	// ��������
	Mat edge, grayImage;

	// ��ԭͼ��ת��Ϊ�Ҷ�ͼ��
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	// ����3x3�ں�������
	blur(grayImage, edge, Size(3, 3));

	// ����Canny����
	Canny(edge, edge, 3, 9, 3);

	// ��ʾЧ��ͼ
	imshow("Final image(Blur - Canny)", edge);

	waitKey(0);
	return 0;
}