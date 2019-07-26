#include <opencv2/opencv.hpp>
using namespace cv;

Mat g_src_image, g_dst_image, g_gray_image, g_mask_image;
int g_fill_mode = 1;		// ��ˮ����ģʽ
int g_low_difference = 20;	// �������ֵ
int g_up_difference = 20;	// �������ֵ
int g_connectivity = 4;		// ��ʾfloodFill������ʶ���Ͱ�λ����ֵͨ
bool g_is_color = true;		// �Ƿ�Ϊ��ɫͼ�ı�ʶ������ֵ
bool g_is_use_mask = false;	// �Ƿ���ʾ��Ĥ���ڵĲ���ֵ
int g_new_mask_val = 255;	// �µ��ػ����Ĥ������ֵ

static void show_help_text();
static void on_mouse(int event, int x, int y, int, void*);

int main() {
	system("color 2F");

	g_src_image = imread("..\\_images\\5.jpg", 1);
	if (!g_src_image.data)
	{
		std::cout << "Oh��no����ȡsrcImage����~�� \n";
		return 0;
	}
	// ��ʾ�����ļ�
	show_help_text();

	g_src_image.copyTo(g_dst_image);
	cvtColor(g_src_image, g_gray_image, COLOR_BGR2GRAY);	// ת����ͨ����image0���Ҷ�ͼ
	g_mask_image.create(g_src_image.rows + 2, g_src_image.cols + 2, CV_8UC1);// ����image0�ĳߴ�����ʼ����Ĥmask

	// �˾�����OpenCV2�汾Ϊ��
	// namedWindow("Ч��ͼ", CV_WINDOW_AUTOSIZE);
	// �˾�����OpenCV3�汾Ϊ��
	namedWindow("Ч��ͼ", WINDOW_AUTOSIZE);

	// ����Trackbar
	createTrackbar("�������ֵ", "Ч��ͼ", &g_low_difference, 255, nullptr);
	createTrackbar("�������ֵ", "Ч��ͼ", &g_up_difference, 255, nullptr);

	// ���ص�����
	setMouseCallback("Ч��ͼ", on_mouse, nullptr);

	// ѭ����ѯ����
	while (true)
	{
		// ����ʾЧ��ͼ
		imshow("Ч��ͼ", g_is_color ? g_dst_image : g_gray_image);

		// ��ȡ���̰���
		const auto key = waitKey(0);
		//�ж�ESC�Ƿ��£������±��˳�
		if (27 == (255 & key))
		{
			std::cout << "�����˳�...........\n";
			break;
		}

		// ���ݰ�����ͬ��ִ�и��ֲ���
		switch (static_cast<char>(key))
		{
			// ������̡�1�������£�Ч��ͼ�ڻҶ�ͼ�Ͳ�ɫͼ֮���л�
		case '1':
			if (g_is_color)	// ��ԭ��Ϊ��ɫ��תΪ�Ҷ�ͼ�����ҽ���Ĥmask����Ԫ������Ϊ0
			{
				std::cout << "���̡�1�������£��л���ɫ/�Ҷ�ģʽ����ǰ����Ϊ������ɫģʽ���л�Ϊ���Ҷ�ģʽ��\n";
				cvtColor(g_src_image, g_gray_image, COLOR_BGR2GRAY);
				g_mask_image = Scalar::all(0);	// ��mask����Ԫ������Ϊ0
				g_is_color = false;	// ����ʶ������Ϊfalse����ʾ��ǰͼ��Ϊ��ɫ�����ǻҶ�
			}
			else // ��ԭ��Ϊ�Ҷ�ͼ���㽫ԭ���Ĳ�ͼimage0�ٴο�����image�����ҽ���Ĥmask����Ԫ������Ϊ0
			{
				std::cout << "���̡�1�������£��л���ɫ/�Ҷ�ģʽ����ǰ����Ϊ������ɫģʽ���л�Ϊ���Ҷ�ģʽ��\n";
				g_src_image.copyTo(g_dst_image);
				g_mask_image = Scalar::all(0);
				g_is_color = true;	// ����ʶ������Ϊtrue����ʾ��ǰͼ��ģʽΪ��ɫ
			}
			break;
			// ������̰�����2�������£���ʾ/������Ĥ����
		case '2':
			if (g_is_use_mask)
			{
				destroyWindow("mask");
				g_is_use_mask = false;
			}
			else
			{
				namedWindow("mask", 0);
				g_mask_image = Scalar::all(0);
				imshow("mask", g_mask_image);
				g_is_use_mask = true;
			}
			break;
			// ������̰�����3�������£��ָ�ԭʼͼ��
		case '3':
			std::cout << "������3�������£��ָ�ԭʼͼ��\n";
			g_src_image.copyTo(g_dst_image);
			cvtColor(g_dst_image, g_gray_image, COLOR_BGR2GRAY);
			g_mask_image = Scalar::all(0);
			break;
			//������̰�����4�������£�ʹ�ÿշ�Χ����ˮ���
		case '4':
			std::cout << "������4�������£�ʹ�ÿշ�Χ����ˮ���\n";
			g_fill_mode = 0;
			break;
			//������̰�����5�������£�ʹ�ý��䡢�̶���Χ����ˮ���
		case '5':
			std::cout << "������5�������£�ʹ�ý��䡢�̶���Χ����ˮ���\n";
			g_fill_mode = 1;
			break;
			//������̰�����6�������£�ʹ�ý��䡢������Χ����ˮ���
		case '6':
			std::cout << "������6�������£�ʹ�ý��䡢������Χ����ˮ���\n";
			g_fill_mode = 2;
			break;
			//������̰�����7�������£�������־���ĵͰ�λʹ��4λ������ģʽ
		case '7':
			std::cout << "������7�������£�������־���ĵͰ�λʹ��4λ������ģʽ\n";
			g_connectivity = 4;
			break;
			//������̰�����8�������£�������־���ĵͰ�λʹ��8λ������ģʽ
		case '8':
			std::cout << "������8�������£�������־���ĵͰ�λʹ��8λ������ģʽ\n";
			g_connectivity = 8;
			break;
		default:
			break;
		}
	}
	return 0;
}

void show_help_text()
{
	//���һЩ������Ϣ  
	printf("\n\n\t��ӭ������ˮ���ʾ������~");
	printf("\n\n\t��ʾ���������ѡȡ�ĵ�����ͼ������֮��ɫ����ĵ㣬���ò�ͬ��ɫ��ע��");

	printf("\n\n\t��������˵��: \n\n"
		"\t\t�����ͼ������- ������ˮ������\n"
		"\t\t���̰�����ESC��- �˳�����\n"
		"\t\t���̰�����1��-  �л���ɫͼ/�Ҷ�ͼģʽ\n"
		"\t\t���̰�����2��- ��ʾ/������Ĥ����\n"
		"\t\t���̰�����3��- �ָ�ԭʼͼ��\n"
		"\t\t���̰�����4��- ʹ�ÿշ�Χ����ˮ���\n"
		"\t\t���̰�����5��- ʹ�ý��䡢�̶���Χ����ˮ���\n"
		"\t\t���̰�����6��- ʹ�ý��䡢������Χ����ˮ���\n"
		"\t\t���̰�����7��- ������־���ĵͰ�λʹ��4λ������ģʽ\n"
		"\t\t���̰�����8��- ������־���ĵͰ�λʹ��8λ������ģʽ\n\n");
}

void on_mouse(const int event, const int x, const int y, int, void*)
{
	// ��������û�а��£��㷵��
	// �˾�����OpenCV2�汾Ϊ��
	// if (event != CV_EVENT_LBUTTONDOWN)
	// �˾�����OpenCV3�汾Ϊ��
	if (EVENT_LBUTTONDOWN != event)
		return;

	// -------------------��<1>����floodFill����֮ǰ�Ĳ���׼�����֡�---------------
	// ����floodFill����֮ǰ�Ĳ���׼������
	const auto seed = Point(x, y);
	// �շ�Χ����ˮ��䣬��ֵ��Ϊ0��������Ϊȫ�ֵ�g_low_difference
	auto low_difference = g_fill_mode == 0 ? 0 : g_low_difference;
	// �շ�Χ����ˮ��䣬��ֵ��Ϊ0��������Ϊȫ�ֵ�g_up_difference
	const auto up_difference = g_fill_mode == 0 ? 0 : g_up_difference;

	// ��ʶ����0~7λΪg_nConnectivity��8~15λΪg_nNewMaskVal����8λ��ֵ��16~23λΪCV_FLOODFILL_FIXED_RANGE����0��
	// �˾�����OpenCV2�汾Ϊ��
	// auto flags = g_connectivity + (g_new_mask_val << 8) + (g_fill_mode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);
	// �˾�����OpenCV3�汾Ϊ��
	const auto flags = g_connectivity + (g_new_mask_val << 8) + (g_fill_mode == 1 ? CV_FLOODFILL_FIXED_RANGE : 0);

	// �������bgrֵ
	const int b = 255 & static_cast<unsigned>(theRNG());	// �������һ��0~255֮���ֵ
	const int g = 255 & static_cast<unsigned>(theRNG());
	const int r = 255 & static_cast<unsigned>(theRNG());
	Rect ccomp;	// �����ػ��������С�߽��������

	// ���ػ��������ص���ֵ�����ǲ�ɫͼģʽ��ȡScalar(b, g, r)��
	// ���ǻҶ�ͼģʽ��ȡScalar(r*0.299 + g*0.587 + b*0.114)
	const auto new_val = g_is_color ? Scalar(b, g, r) : Scalar(r * 0.299 + g * 0.587 + b * 0.114);

	auto dst = g_is_color ? g_dst_image : g_gray_image;	// Ŀ��ͼ�ĸ�ֵ
	int area;

	// --------------------��<2>��ʽ����floodFill������-----------------------------
	if (g_is_use_mask)
	{
		// �˾�����OpenCV2�汾Ϊ��
		// threshold(g_mask_image, g_mask_image, 1, 128, CV_THRESH_BINARY);
		// �˾�����OpenCV3�汾Ϊ��
		threshold(g_mask_image, g_mask_image, 1, 128, THRESH_BINARY);
		area = floodFill(dst, g_mask_image, seed, new_val, &ccomp,
			Scalar(low_difference, low_difference, low_difference),
			Scalar(up_difference, up_difference, up_difference),
			flags);
		imshow("mask", g_mask_image);
	}
	else
	{
		area = floodFill(dst, seed, new_val, &ccomp,
			Scalar(low_difference, low_difference, low_difference),
			Scalar(up_difference, up_difference, up_difference),
			flags);
	}

	imshow("Ч��ͼ", dst);
	std::cout << area << " �����ر��ػ�\n";
}