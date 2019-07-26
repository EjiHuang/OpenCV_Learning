#include <opencv2/opencv.hpp>
using namespace cv;

// ȫ�ֱ���
Mat g_src_image, g_dst_image1, g_dst_image2, g_dst_image3;
auto g_box_filter_value = 3;	// �����˲�����ֵ
auto g_mean_blur_value = 3;		// ��ֵ�˲�����ֵ
auto g_gaussian_blur_value = 3;	// ��˹�˲�����ֵ

// ȫ�ֺ���
static void on_box_filter(int, void*);
static void on_mean_blur(int, void*);
static void on_gaussian_blur(int, void*);

int main() {
	system("color 5F");

	g_src_image = imread("..\\_images\\1.jpg", 1);
	if (!g_src_image.data)
	{
		std::cout << "Oh��no����ȡsrcImage����~�� \n";
		return false;
	}

	g_dst_image1 = g_src_image.clone();
	g_dst_image2 = g_src_image.clone();
	g_dst_image3 = g_src_image.clone();

	namedWindow("0.ԭͼ����", 1);
	imshow("0.ԭͼ����", g_src_image);

	namedWindow("1.�����˲�", 1);
	createTrackbar("�ں�ֵ��", "1.�����˲�", &g_box_filter_value, 40, on_box_filter);
	on_box_filter(g_box_filter_value, nullptr);

	namedWindow("2.��ֵ�˲�", 1);
	createTrackbar("�ں�ֵ��", "2.��ֵ�˲�", &g_mean_blur_value, 40, on_mean_blur);
	on_mean_blur(g_mean_blur_value, nullptr);

	namedWindow("3.��˹�˲�", 1);
	createTrackbar("�ں�ֵ��", "3.��˹�˲�", &g_gaussian_blur_value, 40, on_gaussian_blur);
	on_gaussian_blur(g_gaussian_blur_value, nullptr);

	//���һЩ������Ϣ
	std::cout << std::endl << "\t���гɹ���������������۲�ͼ��Ч��~\n\n"
		<< "\t���¡�q����ʱ�������˳���\n";

	//���¡�q����ʱ�������˳�
	while (char(waitKey(1)) != 'q') {}
	return 0;
}

void on_box_filter(int, void*)
{
	boxFilter(g_src_image, 
		g_dst_image1, 
		-1, 
		Size(g_box_filter_value + 1, g_box_filter_value + 1));
	imshow("1.�����˲�", g_dst_image1);
}

void on_mean_blur(int, void*)
{
	blur(g_src_image, 
		g_dst_image2, 
		Size(g_mean_blur_value + 1, g_mean_blur_value + 1));
	imshow("2.��ֵ�˲�", g_dst_image2);
}

void on_gaussian_blur(int, void*)
{
	GaussianBlur(g_src_image, 
		g_dst_image3, 
		Size(g_gaussian_blur_value * 2 + 1, g_gaussian_blur_value * 2 + 1), 
		0, 
		0);
	imshow("3.��˹�˲�", g_dst_image3);
}


