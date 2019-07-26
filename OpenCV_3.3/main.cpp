#include <opencv2/opencv.hpp>
using namespace cv;

// ȫ�ֱ���������
constexpr auto WINDOW_NAME = "���򴰿�";
Rect g_rectangle;
bool g_bDrawingBox = false;	// �Ƿ���л���
RNG g_rng(12345);

// ȫ�ֺ���������
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(cv::Mat& img, cv::Rect box);

int main() {
	// �ı�console������ɫ
	system("color 9F");

	// ��ʾʹ�õ�OpenCV�汾
	printf("\n\n\t\t\t   ��ǰʹ�õ�OpenCV�汾Ϊ��" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");

	// ׼������
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 800, CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1, -1, 0, 0);
	srcImage = Scalar::all(0);

	// �����������ص�����
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)& srcImage);

	// ������ѭ���������л��Ƶı�ʶΪ��ʱ�����л���
	while (true)
	{
		srcImage.copyTo(tempImage);	// ����Դͼ����ʱ����
		// �����л��Ƶı�ʶΪ��ʱ�����л���
		if (g_bDrawingBox)
		{
			DrawRectangle(tempImage, g_rectangle);
		}
		imshow(WINDOW_NAME, tempImage);
		if (waitKey(10) == 27)
		{
			break;
		}
	}

	return 0;
}

// �˴���x��y����Ϊͼ���е���ߣ����Ǵ�������
void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	Mat& image = *(cv::Mat*)param;
	switch (event)
	{
		// ����ƶ���Ϣ
	case EVENT_MOUSEMOVE:
	{
		if (g_bDrawingBox)	// ����Ƿ���л��Ƶı�ʶΪ�棬���¼�³��Ϳ�Rect�ͱ�����
		{
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
	break;

	// ���������Ϣ
	case EVENT_LBUTTONDOWN:
	{
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 0, 0);	// ��¼��ʼ��
	}
	break;

	// ���̧����Ϣ
	case EVENT_LBUTTONUP:
	{
		g_bDrawingBox = false;	// ���ñ�ʶ��false
		// �Կ�͸�С��0�Ĵ���
		if (g_rectangle.width < 0)
		{
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}

		if (g_rectangle.height < 0)
		{
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		// ���ú������л���
		DrawRectangle(image, g_rectangle);
	}
	break;
	}
}

void DrawRectangle(cv::Mat& img, cv::Rect box)
{
	// �����ɫ�ľ���
	cv::rectangle(img, box.tl(), box.br(), cv::Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}