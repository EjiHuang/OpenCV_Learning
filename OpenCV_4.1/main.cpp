#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	//���һЩ������Ϣ
	printf("\n\n\n\t��ӭ����������ͼ������-Mat�ࡿʾ������~\n\n");
	printf("\n\n\t����˵����\n\n\t��ʾ������������ʾMat��ĸ�ʽ��������ܣ��������Ϊ��");
	printf("\n\n\n\t��1��OpenCVĬ�Ϸ��");
	printf("\n\n\t��2��Python���");
	printf("\n\n\t��3�����ŷָ����");
	printf("\n\n\t��4��Numpy���");
	printf("\n\n\t��5��C���Է��\n\n");
	printf("\n  --------------------------------------------------------------------------\n");

	// Matlabʽ�ĳ�ʼ��
	Mat I = Mat::eye(4, 4, CV_64F);
	I.at<double>(1, 1) = CV_PI;
	std::cout << "\nI = " << I << ";\n" << std::endl;

	Mat r = Mat(10, 3, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));

	//�˶δ����OpenCV2��Ϊ��
	//std::cout << "r (OpenCVĬ�Ϸ��) = " << r << ";" << std::endl << std::endl;
	//std::cout << "r (Python���) = " << format(r,"python") << ";" << std::endl << std::endl;
	//std::cout << "r (Numpy���) = " << format(r,"numpy") << ";" << std::endl << std::endl;
	//std::cout << "r (���ŷָ����) = " << format(r,"csv") << ";" << std::endl<< std::endl;
	//std::cout << "r (C���Է��) = " << format(r,"C") << ";" << std::endl << std::endl;
	//�˶δ����OpenCV3��Ϊ��
	std::cout << "r (OpenCVĬ�Ϸ��) = " << r << ";" << std::endl << std::endl;
	std::cout << "r (Python���) = " << format(r, Formatter::FMT_PYTHON) << ";" << std::endl << std::endl;
	std::cout << "r (Numpy���) = " << format(r, Formatter::FMT_NUMPY) << ";" << std::endl << std::endl;
	std::cout << "r (���ŷָ����) = " << format(r, Formatter::FMT_CSV) << ";" << std::endl << std::endl;
	std::cout << "r (C���Է��) = " << format(r, Formatter::FMT_C) << ";" << std::endl << std::endl;

	Point2f p(6, 2);
	std::cout << "��2ά�㡿p = " << p << ";\n" << std::endl;

	Point3f p3f(8, 2, 0);
	std::cout << "��3ά�㡿p3f = " << p3f << ";\n" << std::endl;

	std::vector<float> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);

	std::cout << "������Mat��vector��shortvec = " << Mat(v) << ";\n" << std::endl;

	std::vector<Point2f> points(20);
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i] = Point2f((float)(i * 5), (float)(i % 7));
	}
	std::cout << "����ά��������points = " << points << ";";

	getchar();

	return 0;
}