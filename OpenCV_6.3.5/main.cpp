#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	auto image = imread("..\\_images\\22.jpg");
	namedWindow("���Ͳ���&��ʴ����->ԭͼ");
	namedWindow("���Ͳ���->Ч��ͼ");
	namedWindow("��ʴ����->Ч��ͼ");
	imshow("���Ͳ���&��ʴ����->ԭͼ", image);

	const auto element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out;

	// �������Ͳ���
	dilate(image, out, element);
	imshow("���Ͳ���->Ч��ͼ", out);

	// ���и�ʴ����
	erode(image, out, element);
	imshow("��ʴ����->Ч��ͼ", out);

	waitKey(0);
	return 0;
}