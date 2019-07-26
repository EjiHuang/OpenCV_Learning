#include <opencv2/opencv.hpp>
using namespace cv;

bool roi_add_image()
{
	const auto scr_image_1 = imread("..\\_images\\dota_pa.jpg");
	const auto logo_image = imread("..\\_images\\dota_logo.jpg");
	if (!scr_image_1.data)
	{
		std::cout << "��ȡ '..\\_images\\dota_pa.jpg' ����" << std::endl;
		return false;
	}
	if (!logo_image.data)
	{
		std::cout << "��ȡ '..\\_images\\dota_logo.jpg' ����" << std::endl;
		return false;
	}

	// ����һ��Mat���Ͳ������趨ROI����
	auto image_roi = scr_image_1(Rect(200, 250, logo_image.cols, logo_image.rows));
	// ������Ĥ�������ǻҶ�ͼ
	const auto mask = imread("..\\_images\\data_logo.jpg", 0);
	// ����Ĥ������ROI
	logo_image.copyTo(image_roi, mask);

	// ��ʾ��nnn��
	namedWindow("<1>����ROIʵ��ͼ�����ʾ������");
	imshow("<1>����ROIʵ��ͼ�����ʾ������", scr_image_1);

	return true;
}

int main() {
	roi_add_image();

	waitKey(0);
	return 0;
}
