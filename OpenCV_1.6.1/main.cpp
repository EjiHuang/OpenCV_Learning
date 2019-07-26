#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	// ʵ����VideoCapture
	VideoCapture capture("..\\_video\\1.avi");
	// �������Ϊ0����Ϊ����ͷ�ɼ�
	// VideoCapture capture(0);

	// �������������Ƶ֡����
	Mat edges;

	// ѭ����ʾÿһ֡
	while (true)
	{
		Mat frame;			// ����һ��Mat�����ڴ洢ÿһ֡��ͼ��
		capture >> frame;	// ��ȡ��ǰ֡

		// ����Ƶ������ɣ��˳�ѭ��
		/*if (frame.empty())
		{
			break;
		}*/

		// ����ΪCanny����
		// cvtColor(frame, edges, CV_BGR2GRAY);	// OpenCV2�汾
		cvtColor(frame, edges, COLOR_BGR2GRAY);	// OpenCV3�汾
		blur(edges, edges, Size(7, 7));
		Canny(edges, edges, 0, 30, 3);

		imshow("Load video before canny.", frame);	// ��ʾ��ǰ֡
		imshow("Load video after canny.", edges);	// ��ʾ��ǰ֡
		if (waitKey(30) >= 0)	break;				// ��ʱ30ms
	}

	return 0;
}