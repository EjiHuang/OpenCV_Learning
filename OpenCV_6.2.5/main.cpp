#include <opencv2/opencv.hpp>
using namespace cv;

// ȫ�ֱ���
Mat g_src_image, g_dst_image1, g_dst_image2;
int g_median_blur_value = 10;		// ��ֵ�˲�����ֵ
int g_bilateral_filter_value = 10;	// ˫���˲�����ֵ

// ȫ�ֺ���
static void on_median_blur(int, void*);
static void on_bilateral_filter(int, void*);

int main() {
	system("color 5F");

	g_src_image = imread("..\\_images\\1.jpg", 1);
	if (!g_src_image.data)
	{
		std::cout << "Oh��no����ȡsrcImage����~�� \n";
		return 0;
	}

	g_dst_image1 = g_src_image.clone();
	g_dst_image2 = g_src_image.clone();

	namedWindow("0.ԭͼ����", 1);
	imshow("0.ԭͼ����", g_src_image);

	namedWindow("1.��ֵ�˲�", 1);
	createTrackbar("�ں�ֵ��", "1.��ֵ�˲�", &g_median_blur_value, 40, on_median_blur);
	on_median_blur(g_median_blur_value, nullptr);

	namedWindow("2.˫���˲�", 1);
	createTrackbar("�ں�ֵ��", "2.˫���˲�", &g_bilateral_filter_value, 40, on_bilateral_filter);
	on_bilateral_filter(g_bilateral_filter_value, nullptr);

	// ���һЩ������Ϣ
	std::cout << std::endl << "\t���гɹ���������������۲�ͼ��Ч��~\n\n"
		<< "\t���¡�q����ʱ�������˳���\n";

	//���¡�q����ʱ�������˳�
	while (char(waitKey(1)) != 'q') {}
	return 0;
}

void on_median_blur(int, void*)
{
	medianBlur(g_src_image, g_dst_image1, g_median_blur_value * 2 + 1);
	imshow("1.��ֵ�˲�", g_dst_image1);
}


void on_bilateral_filter(int, void*)
{
	bilateralFilter(g_src_image,
		g_dst_image2,
		g_bilateral_filter_value,
		2 * g_bilateral_filter_value,
		g_bilateral_filter_value / 2);
	imshow("2.˫���˲�", g_dst_image2);
}
