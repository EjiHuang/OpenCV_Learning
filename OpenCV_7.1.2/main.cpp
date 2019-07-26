#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	const auto src_image = imread("..\\_images\\10.jpg");
	const auto src_image1 = src_image.clone();

	imshow("��ԭʼͼ��Canny��Ե���", src_image);

	//----------------------------------------------------------------------------------
	//	һ����򵥵�canny�÷����õ�ԭͼ��ֱ���á�
	//	ע�⣺�˷�����OpenCV2�п��ã���OpenCV3����ʧЧ
	//----------------------------------------------------------------------------------
	//Canny( srcImage, srcImage, 150, 100,3 );
	//imshow("��Ч��ͼ��Canny��Ե���", srcImage); 

	//----------------------------------------------------------------------------------
	//	�����߽׵�canny�÷���ת�ɻҶ�ͼ�����룬��canny����󽫵õ��ı�Ե��Ϊ���룬����ԭͼ��Ч��ͼ�ϣ�
	//  �õ���ɫ�ı�Եͼ
	//----------------------------------------------------------------------------------
	Mat dst_image, edge, gray_image;

	// 1.������srcͬ���ͺʹ�С�ľ���dst��
	dst_image.create(src_image1.size(), src_image1.type());
	// 2.��ԭͼ��ת��λ�Ҷ�ͼ��
	cvtColor(src_image1, gray_image, COLOR_BGR2GRAY);
	// 3.��ʹ�� 3x3�ں�������
	blur(gray_image, edge, Size(3, 3));
	// 4.����Canny����
	Canny(edge, edge, 3, 9, 3);
	// 5.��g_dst_image�ڵ�����Ԫ������
	dst_image = Scalar::all(0);
	// 6.ʹ��Canny��������ı�Եͼg_canny_detected_edges��Ϊ���룬
	//   ����ԭͼg_src_image������Ŀ��ͼg_dst_image��
	src_image1.copyTo(dst_image, edge);
	// 7.��ʾЧ��ͼ
	imshow("��Ч��ͼ��Canny��Ե���2", dst_image);

	waitKey(0);
	return 0;
}