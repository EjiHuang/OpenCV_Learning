#include <opencv2/opencv.hpp>
using namespace cv;

void color_reduce1(Mat& input_image, Mat& output_image, int div);
void color_reduce2(Mat& input_image, Mat& output_image, int div);
void color_reduce3(Mat& input_image, Mat& output_image, int div);

int main()
{
	auto src_image = imread("..//_images//1.jpg");
	imshow("原始图像", src_image);

	Mat dst_image;
	dst_image.create(src_image.rows, src_image.cols, src_image.type());

	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION);
	printf("\n\n  ----------------------------------------------------------------------------\n");

	// record start time.
	auto time0 = static_cast<double>(getTickCount());

	// start processing image.
	color_reduce3(src_image, dst_image, 32);

	// calculate running time.
	time0 = (static_cast<double>(getTickCount()) - time0) / getTickFrequency();
	std::cout << "\t此方法运行时间为：" << time0 << "秒" << std::endl;

	// 显示效果图
	imshow("效果图", dst_image);

	waitKey(0);
	return 0;
}

// 使用【指针访问：C操作符[]】方法来进行颜色空间缩减
void color_reduce1(Mat& input_image, Mat& output_image, const int div)
{
	output_image = input_image.clone();
	const auto row_number = output_image.rows;
	const auto col_number = output_image.cols * output_image.channels();

	// 双重循环，遍历所有的像素值
	for (auto i = 0; i < row_number; ++i)				// 行循环
	{
		auto data = output_image.ptr<uchar>(i);
		for (auto j = 0; j < col_number; ++j)			// 列循环
		{
			*data++ = *data / div * div + div / 2;
			// 等效于data[j] = data[j] / div * div + div / 2;
		}
	}
}

// 使用【迭代器】方法来进行颜色空间缩减
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

// 使用【动态地址计算】方法来进行颜色空间缩减
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
