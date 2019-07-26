#include <opencv2/opencv.hpp>
using namespace cv;

Mat g_src_image, g_dst_image;
int g_track_bar_number = 0;		// 0��ʾ��ʴerode��1��ʾ����dilate
int g_struct_element_size = 3;	// �ṹԪ�أ��ں˾��󣩵ĳߴ�

void process();	// ���ͺ͸�ʴ�Ĵ�����
void on_track_bar_num_change(int, void*);
void on_element_size_change(int, void*);

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

	// ���г��θ�ʴ��������ʾЧ��ͼ
	namedWindow("Ч��ͼ");
	// ��ȡ�Զ����
	const auto element = getStructuringElement(MORPH_RECT, 
		Size(2 * g_struct_element_size + 1, 2 * g_struct_element_size + 1), 
		Point(g_struct_element_size, g_struct_element_size));
	erode(g_src_image, g_dst_image, element);
	imshow("Ч��ͼ", g_dst_image);

	// �����켣��
	createTrackbar("��ʴ/����", "Ч��ͼ", &g_track_bar_number, 1, on_track_bar_num_change);
	createTrackbar("�ں˳ߴ�", "Ч��ͼ", &g_struct_element_size, 21, on_element_size_change);

	// ���һЩ������Ϣ
	std::cout << std::endl << "\t���гɹ���������������۲�ͼ��Ч��~\n\n"
		<< "\t���¡�q����ʱ�������˳���\n";

	//���¡�q����ʱ�������˳�
	while (char(waitKey(1)) != 'q') {}
	return 0;
}

void process()
{
	// ��ȡ�Զ����
	auto element = getStructuringElement(MORPH_RECT, 
		Size(2 * g_struct_element_size + 1, 2 * g_struct_element_size + 1), 
		Point(g_struct_element_size, g_struct_element_size));

	// ���и�ʴ�����Ͳ���
	if (g_track_bar_number == 0)
	{
		erode(g_src_image, g_dst_image, element);
	}
	else { dilate(g_src_image, g_dst_image, element); }

	// ��ʾЧ��ͼ
	imshow("Ч��ͼ", g_dst_image);
}

void on_element_size_change(int, void*)
{
	// �ں˳ߴ��Ѹı䣬�ص��������������һ��Process������ʹ�ı���Ч ��������Ч����ʾ����
	process();
}

void on_track_bar_num_change(int, void*)
{
	//��ʴ������֮��Ч���Ѿ��л����ص��������������һ��Process������ʹ�ı���Ч��������Ч����ʾ����
	process();
}


