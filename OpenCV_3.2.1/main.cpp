#include <opencv2/opencv.hpp>
using namespace cv;

constexpr auto WINDOW_NAME = "�������Ĵ���&���Ի��ʾ��";
constexpr int g_nMaxAlphaValue = 100;

int g_nAlphaValueSlider;
double g_dAlphaValue;
double g_dBetaValue;

// �����洢ͼ��ı���
Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

void on_Trackbar(int, void*) {
	// �����ǰalphaֵ��������ֵ�ı���
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
	// ��betaֵΪ1��ȥalphaֵ
	g_dBetaValue = (1.0 - g_dAlphaValue);

	// ����alpha��betaֵ�������л��
	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);

	// ��ʾЧ��ͼ
	imshow(WINDOW_NAME, g_dstImage);
}

int main() {
	// ����ͼ����ͼ��ĳߴ�����ͬ��
	g_srcImage1 = imread("..\\_images\\11.jpg");
	g_srcImage2 = imread("..\\_images\\22.jpg");
	if (!g_srcImage1.data) { printf("��ȡ��һ��ͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ��ͼƬ����~��\n"); return -1; }
	if (!g_srcImage2.data) { printf("��ȡ�ڶ���ͼƬ������ȷ��Ŀ¼���Ƿ���imread����ָ��ͼƬ����~��\n"); return -1; }
	
	// ���ù�������ʼֵΪ70
	g_nAlphaValueSlider = 70;

	// ��������
	namedWindow(WINDOW_NAME, 1);

	// �ٴ����Ĵ����д���һ���������ؼ�
	char TrackbarName[50];
	sprintf_s(TrackbarName, "͸����%d ", g_nMaxAlphaValue);

	createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	// ����ٻص���������ʾ
	on_Trackbar(g_nAlphaValueSlider, 0);

	waitKey(0);

	return 0;
}