#include <opencv2/opencv.hpp>
using namespace cv;

constexpr auto g_window_name = "���򴰿�";
Mat g_src_image, g_dst_image, g_tmp_image;

static void show_help_text();

int main() {
	system("color 2F");
	show_help_text();

	g_src_image = imread("..\\_images\\6.jpg", 1);
	if (!g_src_image.data)
	{
		std::cout << "Oh��no����ȡsrcImage����~�� \n";
		return 0;
	}

	// ������ʾ����
	namedWindow(g_window_name, WINDOW_AUTOSIZE);
	imshow(g_window_name, g_src_image);

	// ������ֵ
	g_tmp_image = g_src_image;
	g_dst_image = g_tmp_image;

	auto key = 0;

	while (true)
	{
		key = waitKey(0);
		switch (key)
		{
		case 27:// ����ESC
			return 0;
			break;
		case 'q':// ����Q
			return 0;
			break;
		case 'a':// ����A���£�����pyrUp����
			pyrUp(g_tmp_image, g_dst_image, Size(g_tmp_image.cols * 2, g_tmp_image.rows * 2));
			printf(">��⵽������A�������£���ʼ���л��ڡ�pyrUp��������ͼƬ�Ŵ�ͼƬ�ߴ��2 \n");
			break;
		case 'w':// ����W���£�����resize����
			resize(g_tmp_image, g_dst_image, Size(g_tmp_image.cols * 2, g_tmp_image.rows * 2));
			printf(">��⵽������W�������£���ʼ���л��ڡ�resize��������ͼƬ�Ŵ�ͼƬ�ߴ��2 \n");
			break;
		case '1':// ����1���£�����resize����
			resize(g_tmp_image, g_dst_image, Size(g_tmp_image.cols * 2, g_tmp_image.rows * 2));
			printf(">��⵽������1�������£���ʼ���л��ڡ�resize��������ͼƬ�Ŵ�ͼƬ�ߴ��2 \n");
			break;
		case '3':// ����3���£�����pyrUp����
			pyrUp(g_tmp_image, g_dst_image, Size(g_tmp_image.cols * 2, g_tmp_image.rows * 2));
			printf(">��⵽������3�������£���ʼ���л��ڡ�pyrUp��������ͼƬ�Ŵ�ͼƬ�ߴ��2 \n");
			break;
		case 'd':// ����D���£�����pyrDown����
			pyrDown(g_tmp_image, g_dst_image, Size(g_tmp_image.cols / 2, g_tmp_image.rows / 2));
			printf(">��⵽������D�������£���ʼ���л��ڡ�pyrDown��������ͼƬ��С��ͼƬ�ߴ�/2\n");
			break;
		case 's':// ����S���£�����resize����
			resize(g_tmp_image, g_dst_image, Size(g_tmp_image.cols / 2, g_tmp_image.rows / 2));
			printf(">��⵽������S�������£���ʼ���л��ڡ�resize��������ͼƬ��С��ͼƬ�ߴ�/2\n");
			break;
		case '2':// ����2���£�����resize����
			resize(g_tmp_image, g_dst_image, Size(g_tmp_image.cols / 2, g_tmp_image.rows / 2));
			printf(">��⵽������2�������£���ʼ���л��ڡ�resize��������ͼƬ��С��ͼƬ�ߴ�/2\n");
			break;
		case '4':
			pyrDown(g_tmp_image, g_dst_image, Size(g_tmp_image.cols / 2, g_tmp_image.rows / 2));
			printf(">��⵽������4�������£���ʼ���л��ڡ�pyrDown��������ͼƬ��С��ͼƬ�ߴ�/2\n");
			break;
		default: ;
		}
		// ��ʾ�仯���ͼ
		imshow(g_window_name, g_dst_image);
		// ��g_dst_image����g_tmp_image�������´�ѭ��
		g_tmp_image = g_dst_image;
	}
}

void show_help_text()
{
	//���һЩ������Ϣ
	printf("\n\t��ӭ����OpenCVͼ���������resizeʾ������~\n\n");
	printf("\n\n\t��������˵��: \n\n"
		"\t\t���̰�����ESC�����ߡ�Q��- �˳�����\n"
		"\t\t���̰�����1�����ߡ�W��- ���л��ڡ�resize��������ͼƬ�Ŵ�\n"
		"\t\t���̰�����2�����ߡ�S��- ���л��ڡ�resize��������ͼƬ��С\n"
		"\t\t���̰�����3�����ߡ�A��- ���л��ڡ�pyrUp��������ͼƬ�Ŵ�\n"
		"\t\t���̰�����4�����ߡ�D��- ���л��ڡ�pyrDown��������ͼƬ��С\n"
	);
}
