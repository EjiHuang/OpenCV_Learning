#include <opencv2/opencv.hpp>
using namespace cv;

void color_reduce1(Mat& input_image, Mat& output_image, int div);
void color_reduce2(Mat& input_image, Mat& output_image, int div);
void color_reduce3(Mat& input_image, Mat& output_image, int div);

int main()
{
	auto src_image = imread("..//_images//1.jpg");
	imshow("ԭʼͼ��", src_image);

	Mat dst_image;
	dst_image.create(src_image.rows, src_image.cols, src_image.type());

	printf("\n\n\t\t\t   ��ǰʹ�õ�OpenCV�汾Ϊ��" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");

	// record start time.
	auto time0 = static_cast<double>(getTickCount());

	// start processing image.
	color_reduce3(src_image, dst_image, 32);

	// calculate running time.
	time0 = (static_cast<double>(getTickCount()) - time0) / getTickFrequency();
	std::cout << "\t�˷�������ʱ��Ϊ��" << time0 << "��" << std::endl;

	// ��ʾЧ��ͼ
	imshow("Ч��ͼ", dst_image);

	waitKey(0);
	return 0;
}

// ʹ�á�ָ����ʣ�C������[]��������������ɫ�ռ�����
void color_reduce1(Mat& input_image, Mat& output_image, const int div)
{
	output_image = input_image.clone();
	const auto row_number = output_image.rows;
	const auto col_number = output_image.cols * output_image.channels();

	// ˫��ѭ�����������е�����ֵ
	for (auto i = 0; i < row_number; ++i)				// ��ѭ��
	{
		auto data = output_image.ptr<uchar>(i);
		for (auto j = 0; j < col_number; ++j)			// ��ѭ��
		{
			*data++ = *data / div * div + div / 2;
			// ��Ч��data[j] = data[j] / div * div + div / 2;
		}
	}
}

// ʹ�á���������������������ɫ�ռ�����
void color_reduce2(Mat& input_image, Mat& output_image, const int div)
{
	output_image = input_image.clone();
	// get the iterator.
	auto it_begin = output_image.begin<Vec3b>();
	const auto it_end = output_image.end<Vec3b>();

	for (; it_begin != it_end; ++it_begin)
	{
		(*it_begin)[0] = (*it_begin)[0] / div * div + div / 2;
		(*it_begin)[1] = (*it_begin)[1] / div * div + div / 2;
		(*it_begin)[2] = (*it_begin)[2] / div * div + div / 2;
	}
}

// ʹ�á���̬��ַ���㡿������������ɫ�ռ�����
void color_reduce3(Mat& input_image, Mat& output_image, int div)
{
	output_image = input_image.clone();
	const auto row_number = output_image.rows;
	const auto col_number = output_image.cols;

	for (auto i = 0; i < row_number; ++i)
	{
		for (auto j = 0; j < col_number; ++j)
		{
			output_image.at<Vec3b>(i, j)[0] = output_image.at<Vec3b>(i, j)[0] / div * div + div / 2;	// blue.
			output_image.at<Vec3b>(i, j)[1] = output_image.at<Vec3b>(i, j)[1] / div * div + div / 2;	// green.
			output_image.at<Vec3b>(i, j)[2] = output_image.at<Vec3b>(i, j)[2] / div * div + div / 2;	// red.
		}
	}
}
