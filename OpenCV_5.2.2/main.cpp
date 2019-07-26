#include <opencv2/opencv.hpp>
using namespace cv;

bool linear_blending()
{
	// ����һЩ�ֲ�����
	const auto alpha_value = 0.5;
	double beta_value;
	Mat dst_image;
	const auto src_image2 = imread("..\\_images\\mogu.jpg");
	const auto src_image3 = imread("..\\_images\\rain.jpg");

	if (!src_image2.data)
	{
		std::cout << "��ȡ'..\\_images\\mogu.jpg'����\n";
		return false;
	}
	if (!src_image3.data)
	{
		std::cout << "��ȡ'..\\_images\\rain.jpg'����\n";
		return false;
	}

	// ����ͼ���ϼ�Ȩ����
	beta_value = (1.0 - alpha_value);
	addWeighted(src_image2, alpha_value, src_image3, beta_value, 0.0, dst_image);

	// ��ʾ
	imshow("<2>���Ի��ʾ�����ڡ�ԭͼ��", src_image2);
	imshow("<3>���Ի��ʾ�����ڡ�Ч��ͼ��", dst_image);

	return true;
}

int main() {
	linear_blending();

	waitKey(0);
	return  0;
}