#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	// 实例化VideoCapture
	VideoCapture capture("..\\_video\\1.avi");
	// 如果参数为0，则为摄像头采集
	// VideoCapture capture(0);

	// 定义变量用于视频帧处理
	Mat edges;

	// 循环显示每一帧
	while (true)
	{
		Mat frame;			// 定义一个Mat，用于存储每一帧的图像
		capture >> frame;	// 读取当前帧

		// 若视频播放完成，退出循环
		/*if (frame.empty())
		{
			break;
		}*/

		// 下面为Canny处理
		// cvtColor(frame, edges, CV_BGR2GRAY);	// OpenCV2版本
		cvtColor(frame, edges, COLOR_BGR2GRAY);	// OpenCV3版本
		blur(edges, edges, Size(7, 7));
		Canny(edges, edges, 0, 30, 3);

		imshow("Load video before canny.", frame);	// 显示当前帧
		imshow("Load video after canny.", edges);	// 显示当前帧
		if (waitKey(30) >= 0)	break;				// 延时30ms
	}

	return 0;
}