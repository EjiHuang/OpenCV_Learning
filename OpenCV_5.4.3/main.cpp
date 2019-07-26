#include <opencv2/opencv.hpp>
using namespace cv;

static void contrast_and_bright(int, void*);
int g_contrast_value;	// �Աȶ�
int g_bright_value;		// ����ֵ
Mat g_src_image, g_dst_image;

int main() {
	system("color 2F");

	// �����û��ṩ��ͼ��
	g_src_image = imread("..\\_images\\1.jpg");
	if (!g_src_image.data)
	{
		std::cout << "��ȡg_srcImageͼƬ����~�� \n";
		return false;
	}
	g_dst_image = Mat::zeros(g_src_image.size(), g_src_image.type());

	// �趨�ԱȶȺ����ȵĳ�ֵ
	g_contrast_value = 80;
	g_bright_value = 80;

	// ��������
	namedWindow("[Ч��ͼ����]", 1);

	// �����켣��
	createTrackbar("�Աȶȣ�", "[Ч��ͼ����]", &g_contrast_value, 300, contrast_and_bright);
	createTrackbar("��  �ȣ�", "[Ч��ͼ����]", &g_bright_value, 200, contrast_and_bright);

	// ���ûص�����
	contrast_and_bright(g_contrast_value, nullptr);
	contrast_and_bright(g_bright_value, nullptr);

	std::cout 
		<< "\t���гɹ���������������۲�ͼ��Ч��\n\n"
		<< "\t���¡�q����ʱ�������˳�\n";

	while (char(waitKey(1))!='q'){}
	return  0;
}

void contrast_and_bright(int, void*)
{
	// ��������
	namedWindow("[ԭʼͼ����]", 1);
	// ����forѭ����ִ������g_dst_image(i,j) = a * g_src_image(i,j) + b
	for (auto y = 0; y < g_src_image.rows; ++y)
	{
		for (auto x = 0; x < g_src_image.cols; ++x)
		{
			for (auto c = 0; c < 3; ++c)
			{
				g_dst_image.at<Vec3b>(y, x)[c] = 
					saturate_cast<uchar>((g_contrast_value * 0.01) * (g_src_image.at<Vec3b>(y, x)[c]) + g_bright_value);
			}
		}
	}

	// ��ʾͼ��
	imshow("[ԭʼͼ����]", g_src_image);
	imshow("[Ч��ͼ����]", g_dst_image);
}
