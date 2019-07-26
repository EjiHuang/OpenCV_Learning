#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	const auto image = imread("..\\_images\\1.jpg");
	namedWindow("��ֵ�˲�&˫���˲�->ԭͼ");
	namedWindow("��ֵ�˲�->Ч��ͼ");
	namedWindow("˫���˲�->Ч��ͼ");

	imshow("��ֵ�˲�&˫���˲�->ԭͼ", image);

	Mat out;
	medianBlur(image, out, 7);
	imshow("��ֵ�˲�->Ч��ͼ", out);

	bilateralFilter(image, out, 25, 25 * 2, 25 / 2);
	imshow("˫���˲�->Ч��ͼ", out);

	waitKey(0);
	return 0;
}