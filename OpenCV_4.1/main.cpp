#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	//输出一些帮助信息
	printf("\n\n\n\t欢迎来到【基本图像容器-Mat类】示例程序~\n\n");
	printf("\n\n\t程序说明：\n\n\t此示例程序用于演示Mat类的格式化输出功能，输出风格可为：");
	printf("\n\n\n\t【1】OpenCV默认风格");
	printf("\n\n\t【2】Python风格");
	printf("\n\n\t【3】逗号分隔风格");
	printf("\n\n\t【4】Numpy风格");
	printf("\n\n\t【5】C语言风格\n\n");
	printf("\n  --------------------------------------------------------------------------\n");

	// Matlab式的初始化
	Mat I = Mat::eye(4, 4, CV_64F);
	I.at<double>(1, 1) = CV_PI;
	std::cout << "\nI = " << I << ";\n" << std::endl;

	Mat r = Mat(10, 3, CV_8UC3);
	randu(r, Scalar::all(0), Scalar::all(255));

	//此段代码的OpenCV2版为：
	//std::cout << "r (OpenCV默认风格) = " << r << ";" << std::endl << std::endl;
	//std::cout << "r (Python风格) = " << format(r,"python") << ";" << std::endl << std::endl;
	//std::cout << "r (Numpy风格) = " << format(r,"numpy") << ";" << std::endl << std::endl;
	//std::cout << "r (逗号分隔风格) = " << format(r,"csv") << ";" << std::endl<< std::endl;
	//std::cout << "r (C语言风格) = " << format(r,"C") << ";" << std::endl << std::endl;
	//此段代码的OpenCV3版为：
	std::cout << "r (OpenCV默认风格) = " << r << ";" << std::endl << std::endl;
	std::cout << "r (Python风格) = " << format(r, Formatter::FMT_PYTHON) << ";" << std::endl << std::endl;
	std::cout << "r (Numpy风格) = " << format(r, Formatter::FMT_NUMPY) << ";" << std::endl << std::endl;
	std::cout << "r (逗号分隔风格) = " << format(r, Formatter::FMT_CSV) << ";" << std::endl << std::endl;
	std::cout << "r (C语言风格) = " << format(r, Formatter::FMT_C) << ";" << std::endl << std::endl;

	Point2f p(6, 2);
	std::cout << "【2维点】p = " << p << ";\n" << std::endl;

	Point3f p3f(8, 2, 0);
	std::cout << "【3维点】p3f = " << p3f << ";\n" << std::endl;

	std::vector<float> v;
	v.push_back(3);
	v.push_back(5);
	v.push_back(7);

	std::cout << "【基于Mat的vector】shortvec = " << Mat(v) << ";\n" << std::endl;

	std::vector<Point2f> points(20);
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i] = Point2f((float)(i * 5), (float)(i % 7));
	}
	std::cout << "【二维点向量】points = " << points << ";";

	getchar();

	return 0;
}