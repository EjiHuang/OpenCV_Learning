#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	// 1.�ԻҶ�ģʽ��ȡԭʼͼ����ʾ
	auto src_image = imread("..\\_images\\1.jpg", 0);
	if (!src_image.data) { printf("��ȡͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ��ͼƬ����~�� \n"); return false; }
	imshow("ԭʼͼ��", src_image);

	// 2.������ͼ����������ѵĳߴ磬�߽���0����
	auto m = getOptimalDFTSize(src_image.rows);
	auto n = getOptimalDFTSize(src_image.cols);

	// ����ӵ����س�ʼ��Ϊ0
	Mat padded;
	copyMakeBorder(src_image, 
		padded, 
		0, 
		m - src_image.rows, 
		0, 
		n - src_image.cols, 
		BORDER_CONSTANT, 
		Scalar::all(0));
	// 3.Ϊ����Ҷ�任�Ľ����ʵ�����鲿������洢�ռ䡣
	// ��planes������Ϻϲ���һ����ͨ��������complexI
	Mat planes[] = { Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);
	// 4.���о͵���ɢ����Ҷ�任
	dft(complexI, complexI);
	// 5.������ת��Ϊ��ֵ����=> log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes);	// ����ͨ������complexI����ɼ�����ͨ�����飬planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);
	auto magnitude_image = planes[0];
	// 6.���ж����߶ȣ�logarithmic scale������
	magnitude_image += Scalar::all(1);
	log(magnitude_image, magnitude_image);
	// 7.���к��طֲ�����ͼ����
	// ���������л������У�����Ƶ�ײü�
	magnitude_image = magnitude_image(Rect(0, 0, magnitude_image.cols & -2, magnitude_image.rows & -2));
	// �������и���Ҷͼ���е����ޣ��ǵ�ԭ��λ��ͼ������
	auto cx = magnitude_image.cols / 2;
	auto cy = magnitude_image.rows / 2;
	Mat q0(magnitude_image, Rect(0, 0, cx, cy));		// ROI���������
	Mat q1(magnitude_image, Rect(cx, 0, cx, cy));		// ROI���������
	Mat q2(magnitude_image, Rect(0, cy, cx, cy));		// ROI���������
	Mat q3(magnitude_image, Rect(cx, cy, cx, cy));	// ROI���������
	// �������ޣ����Ϻ����½��н�����
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	// �������ޣ����Ϻ����½��н�����
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	// 8.��һ������0��1֮��ĸ�����ֵ������任Ϊ���ӵ�ͼ���ʽ
	// OpenCV2 version:
	// normalize(magnitude_image, magnitude_image, 0, 1, CV_MINMAX);
	// OpenCV3 version:
	normalize(magnitude_image, magnitude_image, 0, 1, NORM_MINMAX);

	// 9.��ʾЧ��ͼ
	imshow("Ƶ�׷�ֵ", magnitude_image);
	waitKey();

	waitKey(6000);
}