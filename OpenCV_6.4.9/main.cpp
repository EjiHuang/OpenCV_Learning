#include <opencv2/opencv.hpp>
using namespace cv;

Mat g_src_image, g_dst_image;
int g_element_shape = MORPH_RECT;

int g_max_iteration_num = 10;
int g_open_close_num = 0;
int g_erode_dilate_num = 0;
int g_top_black_hat_num = 0;

static void on_open_close(int, void*);
static void on_erode_dilate(int, void*);
static void on_top_black_hat(int, void*);

int main() {
	system("color 2F");

	g_src_image = imread("..\\_images\\3.jpg");
	if (!g_src_image.data)
	{
		std::cout << "Oh��no����ȡsrcImage����~�� \n";
		return 0;
	}
	namedWindow("ԭͼ����", 1);
	imshow("ԭͼ����", g_src_image);

	namedWindow("��������/�����㡿", 1);
	namedWindow("����ʴ/���͡�", 1);
	namedWindow("����ñ/��ñ��", 1);

	g_open_close_num = 9;
	g_erode_dilate_num = 9;
	g_top_black_hat_num = 2;

	createTrackbar("����ֵ",
		"��������/�����㡿",
		&g_open_close_num,
		g_max_iteration_num * 2 + 1,
		on_open_close);
	createTrackbar("����ֵ",
		"����ʴ/���͡�",
		&g_erode_dilate_num,
		g_max_iteration_num * 2 + 1,
		on_erode_dilate);
	createTrackbar("����ֵ",
		"����ñ/��ñ��",
		&g_top_black_hat_num,
		g_max_iteration_num * 2 + 1,
		on_top_black_hat);

	while (true)
	{
		on_open_close(g_open_close_num, nullptr);
		on_erode_dilate(g_erode_dilate_num, nullptr);
		on_top_black_hat(g_top_black_hat_num, nullptr);

		const auto key = waitKey(0);
		// ���¼��̰���Q����ESC�������˳�
		if (static_cast<char>(key) == 'q' || static_cast<char>(key) == 27)
			break;
		// ���¼��̰���1��ʹ����Բ��Elliptic���ṹԪ��MORPH_ELLIPSE
		if (static_cast<char>(key) == 49)
			g_element_shape = MORPH_ELLIPSE;
		// ���¼��̰���2��ʹ�þ��Σ�Rectangle���ṹԪ��MORPH_RECT
		else if (static_cast<char>(key) == 50)
			g_element_shape = MORPH_RECT;
		// ���¼��̰���3��ʹ��ʮ���Σ�Cross-shaped���ṹԪ��MORPH_CROSS
		else if (static_cast<char>(key) == 51)
			g_element_shape = MORPH_CROSS;
		// ���¼��̰���space���ھ��Ρ���Բ��ʮ���νṹԪ����ѭ��
		else if (static_cast<char>(key) == ' ')
			g_element_shape = (g_element_shape + 1 % 3);
	}

	return 0;
}

void on_open_close(int, void*)
{
	// ƫ�����Ķ���
	const auto offset = g_open_close_num - g_max_iteration_num;	// ƫ����
	const auto absolute_offset = offset > 0 ? offset : -offset;	// ƫ��������ֵ
	// �Զ����
	const auto element = getStructuringElement(g_element_shape,
		Size(absolute_offset * 2 + 1, absolute_offset * 2 + 1),
		Point(absolute_offset, absolute_offset));
	// ���в���
	if (0 > offset)
	{
		// OpenCV2 version��
		// morphologyEx(g_src_image, g_dst_image, CV_MOP_OPEN, element);
		// OpenCV3 version:
		morphologyEx(g_src_image, g_dst_image, MORPH_OPEN, element);
	}
	else
	{
		// OpenCV2 version��
		// morphologyEx(g_src_image, g_dst_image, CV_MOP_CLOSE, element);
		// OpenCV3 version:
		morphologyEx(g_src_image, g_dst_image, MORPH_CLOSE, element);
	}

	imshow("��������/�����㡿", g_dst_image);
}

void on_erode_dilate(int, void*)
{
	// ƫ�����Ķ���
	const auto offset = g_erode_dilate_num - g_max_iteration_num;	// ƫ����
	const auto absolute_offset = offset > 0 ? offset : -offset;	// ƫ��������ֵ
	// �Զ����
	const auto element = getStructuringElement(g_element_shape,
		Size(absolute_offset * 2 + 1, absolute_offset * 2 + 1),
		Point(absolute_offset, absolute_offset));
	// ���в���
	if (0 > offset)
		erode(g_src_image, g_dst_image, element);
	else
		dilate(g_src_image, g_dst_image, element);
	// ��ʾͼ��
	imshow("����ʴ/���͡�", g_dst_image);
}

void on_top_black_hat(int, void*)
{
	// ƫ�����Ķ���
	const auto offset = g_top_black_hat_num - g_max_iteration_num;	// ƫ����
	const auto absolute_offset = offset > 0 ? offset : -offset;		// ƫ�����ľ���ֵ
	// �Զ����
	const auto element = getStructuringElement(g_element_shape,
		Size(absolute_offset * 2 + 1, absolute_offset * 2 + 1),
		Point(absolute_offset, absolute_offset));
	// ���в���
	if (0 > offset)
		morphologyEx(g_src_image, g_dst_image, MORPH_TOPHAT, element);
	else
		morphologyEx(g_src_image, g_dst_image, MORPH_BLACKHAT, element);
	// ��ʾͼ��
	imshow("����ñ/��ñ��", g_dst_image);
}


