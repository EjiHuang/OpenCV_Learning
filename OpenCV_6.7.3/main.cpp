#include <opencv2/opencv.hpp>
using namespace cv;

constexpr auto g_window_name = "���򴰿�";
auto g_threshold_value = 100;
auto g_threshold_type = 3;
Mat g_src_image, g_gray_image, g_dst_image;

static void show_help_text();
void on_threshold(int, void*);

int main() {
	system("color 1F");
	show_help_text();

	g_src_image = imread("..\\_images\\5.jpg");
	imshow("ԭʼͼ", g_src_image);

	// ����һ��ԭͼ�ĻҶ�ͼ
	cvtColor(g_src_image, g_gray_image, COLOR_RGB2GRAY);
	// �������ڲ���ʾԭʼͼ
	namedWindow(g_window_name, WINDOW_AUTOSIZE);
	// ������������������ֵ
	createTrackbar("ģʽ", g_window_name, &g_threshold_type, 4, on_threshold);
	createTrackbar("����ֵ", g_window_name, &g_threshold_value, 255, on_threshold);

	// ��ʼ���Զ�����ֵ�ص�����
	on_threshold(0, nullptr);
	while (true)// ESC�˳�
	{
		const auto key = waitKey(20);
		if (static_cast<char>(key) == 27) { break; }
	}
}

void show_help_text()
{
	//���һЩ������Ϣ  
	printf("\n\t��ӭ������������ֵ������ʾ������~\n\n");
	printf("\n\t��������˵��: \n\n"
		"\t\t���̰�����ESC��- �˳�����\n"
		"\t\t������ģʽ0- ��������ֵ\n"
		"\t\t������ģʽ1- ����������ֵ\n"
		"\t\t������ģʽ2- �ض���ֵ\n"
		"\t\t������ģʽ3- ����ֵ��Ϊ0\n"
		"\t\t������ģʽ4- ��ֵ��Ϊ0\n");
}

void on_threshold(int, void*)
{
	// ������ֵ����
	threshold(g_src_image, g_dst_image, g_threshold_value, 255, g_threshold_type);

	// ����Ч��ͼ
	imshow(g_window_name, g_dst_image);
}

