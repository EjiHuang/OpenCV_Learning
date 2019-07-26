#include <opencv2/opencv.hpp>
using namespace cv;

bool roi_linear_blending()
{
	const auto src_image = imread("..\\_images\\dota_pa.jpg", 1);
	const auto logo_image = imread("..\\_images\\dota_logo.jpg");

	if (!src_image.data)
	{
		std::cout << "��ȡ'..\\_images\\dota_pa.jpg'����\n";
		return false;
	}
	if (!logo_image.data)
	{
		std::cout << "��ȡ'..\\_images\\dota_logo.jpg'����\n";
		return false;
	}

	// ����һ��Mat���Ͳ������趨ROI����
	auto image_roi = src_image(Rect(200, 250, logo_image.cols, logo_image.rows));
	// ����2
	// auto image_roi = src_image(Range(250, 250 + logo_image.rows), Range(200, 200 + logo_image.cols));

	// ��logo�ӵ�ԭͼ��
	addWeighted(image_roi, 0.5, logo_image, 0.3, 0., image_roi);

	// ��ʾ���
	imshow("��������ͼ����ʾ������", src_image);

	return true;
}

int main() {
	roi_linear_blending();

	waitKey(0);
	return 0;
}