#include <opencv2/opencv.hpp>
using namespace cv;

constexpr auto n_tests = 14;
constexpr auto n_iterations = 20;

/**
 * \brief 利用.ptr和[]
 * \param image
 * \param div
 */
void color_reduce0(Mat& image, const int div = 64)
{
	const auto rows = image.rows;
	const auto cols = image.cols * image.channels();

	for (auto j = 0; j < rows; ++j)
	{
		const auto data = image.ptr<uchar>(j);
		for (auto i = 0; i < cols; ++i)
		{
			data[i] = data[i] / div * div + div / 2;
		}
	}
}

/**
 * \brief 利用.ptr和* ++
 * \param image
 * \param div
 */
void color_reduce1(Mat& image, const int div = 64)
{
	const auto rows = image.rows;
	const auto cols = image.cols * image.channels();

	for (auto j = 0; j < rows; ++j)
	{
		auto data = image.ptr<uchar>(j);
		for (auto i = 0; i < cols; ++i)
		{
			*data++ = *data / div * div + div / 2;
		}
	}
}

/**
 * \brief 利用.ptr 和 * ++ 以及模操作
 * \param image
 * \param div
 */
void color_reduce2(Mat& image, const int div = 64)
{
	auto rows = image.rows;
	auto cols = image.cols * image.channels();

	for (auto j = 0; j < rows; ++j)
	{
		auto data = image.ptr<uchar>(j);
		for (auto i = 0; i < cols; ++i)
		{
			const auto v = *data;
			*data++ = v - v % div + div / 2;
		}
	}
}

/**
 * \brief 利用.ptr 和 * ++ 以及位操作
 * \param image
 * \param div
 */
void color_reduce3(Mat& image, const int div = 64)
{
	const auto rows = image.rows;
	const auto cols = image.cols * image.channels();
	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// 掩码值
	const auto mask = 0xff << n; // 对于div=16，mask = 0xf0

	for (auto j = 0; j < rows; ++j)
	{
		auto data = image.ptr<uchar>(j);
		for (auto i = 0; i < cols; ++i)
		{
			*data++ = *data & mask + div / 2;
		}
	}
}

/**
 * \brief 利用指针算术运算
 * \param image
 * \param div
 */
void color_reduce4(Mat& image, const int div = 64)
{
	const auto rows = image.rows;
	const auto cols = image.cols * image.channels();
	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	const auto step = image.step; // 有效宽度
	// 掩码值
	const auto mask = 0xff << n; // 对于div=16，mask = 0xf0

	// 获取只想图像缓冲区的指针
	auto data = image.data;

	for (auto j = 0; j < rows; ++j)
	{
		for (auto i = 0; i < cols; ++i)
		{
			*(data + i) = *data & mask + div / 2;
		}
		data += step; // next line.
	}
}

/**
 * \brief 利用 .ptr 和 * ++以及位运算、image.cols * image.channels()
 * \param image
 * \param div
 */
void color_reduce5(Mat& image, const int div = 64)
{
	const auto rows = image.rows;
	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// 掩码值
	const auto mask = 0xff << n; // 对于div=16，mask = 0xf0

	for (auto j = 0; j < rows; ++j)
	{
		auto data = image.ptr<uchar>(j);
		for (auto i = 0; i < image.cols * image.channels(); ++i)
		{
			*data++ = *data & mask + div / 2;
		}
	}
}

/**
 * \brief 利用.ptr 和 * ++ 以及位运算(continuous)
 * \param image
 * \param div
 */
void color_reduce6(Mat& image, const int div = 64)
{
	auto rows = image.rows;
	auto cols = image.cols * image.channels();

	if (image.isContinuous())
	{
		// 无填充像素
		cols = cols * rows;
		rows = 1;
	}

	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// 掩码值
	const auto mask = 0xff << n; // 对于div=16，mask = 0xf0

	for (auto j = 0; j < rows; ++j)
	{
		auto data = image.ptr<uchar>(j);
		for (auto i = 0; i < cols; ++i)
		{
			*data++ = *data & mask + div / 2;
		}
	}
}

/**
 * \brief 利用 .ptr 和 * ++ 以及位运算 (continuous+channels)
 * \param image
 * \param div
 */
void color_reduce7(Mat& image, const int div = 64)
{
	auto rows = image.rows;
	auto cols = image.cols;

	if (image.isContinuous())
	{
		// 无填充像素
		cols = cols * rows;
		rows = 1;
	}

	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// 掩码值
	const uchar mask = 0xff << n;

	for (auto j = 0; j < rows; ++j)
	{
		auto data = image.ptr<uchar>(j);

		for (auto i = 0; i < cols; ++i)
		{
			*data++ = *data & mask + div / 2;
			*data++ = *data & mask + div / 2;
			*data++ = *data & mask + div / 2;
		}
	}
}

/**
 * \brief 利用Mat_ iterator
 * \param image
 * \param div
 */
void color_reduce8(Mat& image, const int div = 64)
{
	// 获取迭代器
	auto it_begin = image.begin<Vec3b>();
	const auto it_end = image.end<Vec3b>();

	for (; it_begin != it_end; ++it_begin)
	{
		(*it_begin)[0] = (*it_begin)[0] / div * div + div / 2;
		(*it_begin)[1] = (*it_begin)[1] / div * div + div / 2;
		(*it_begin)[2] = (*it_begin)[2] / div * div + div / 2;
	}
}

/**
 * \brief 利用Mat_ iterator以及位运算
 * \param image
 * \param div
 */
void color_reduce9(Mat& image, const int div = 64)
{
	// div必须是2的幂
	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// 掩码值
	const uchar mask = 0xff << n;

	// 获取迭代器
	auto it_begin = image.begin<Vec3b>();
	const auto it_end = image.end<Vec3b>();

	// 扫描所有元素
	for (; it_begin != it_end; ++it_begin)
	{
		(*it_begin)[0] = (*it_begin)[0] & mask + div / 2;
		(*it_begin)[1] = (*it_begin)[1] & mask + div / 2;
		(*it_begin)[2] = (*it_begin)[2] & mask + div / 2;
	}
}

/**
 * \brief 利用Mat Iterator_
 * \param image
 * \param div
 */
void color_reduce10(Mat& image, const int div = 64)
{
	// 获取迭代器
	Mat_<Vec3b> cimage = image;
	auto it_begin = cimage.begin();
	const auto it_end = cimage.end();

	for (; it_begin != it_end; ++it_begin)
	{
		(*it_begin)[0] = (*it_begin)[0] / div * div + div / 2;
		(*it_begin)[1] = (*it_begin)[1] / div * div + div / 2;
		(*it_begin)[2] = (*it_begin)[2] / div * div + div / 2;
	}
}

/**
 * \brief 利用动态地址计算配合at
 * \param image
 * \param div
 */
void color_reduce11(Mat& image, const int div = 64)
{
	const auto rows = image.rows;
	const auto cols = image.cols;

	for (auto j = 0; j < rows; ++j)
	{
		for (auto i = 0; i < cols; ++i)
		{
			image.at<Vec3b>(j, i)[0] = image.at<Vec3b>(j, i)[0] / div * div + div / 2;
			image.at<Vec3b>(j, i)[1] = image.at<Vec3b>(j, i)[1] / div * div + div / 2;
			image.at<Vec3b>(j, i)[2] = image.at<Vec3b>(j, i)[2] / div * div + div / 2;
		}
	}
}

/**
 * \brief 利用图像的输入与输出
 * \param image 输入图像
 * \param result 输出图像
 * \param div
 */
void color_reduce12(const Mat& image, Mat& result, const int div = 64)
{
	auto rows = image.rows;
	auto cols = image.cols;

	// 准备好初始化后的Mat给输出图像
	result.create(image.rows, image.cols, image.type());

	// 创建无像素填充的图像
	cols = cols * rows;
	rows = 1;	// 单维数组

	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// 掩码值
	const uchar mask = 0xff << n;

	for (auto j = 0; j < rows; ++j)
	{
		auto data = result.ptr<uchar>(j);
		auto i_data = image.ptr<uchar>(j);

		for (auto i = 0; i < cols; ++i)
		{
			*data++ = (*i_data++) & mask + div / 2;
			*data++ = (*i_data++) & mask + div / 2;
			*data++ = (*i_data++) & mask + div / 2;
		}
	}
}

/**
 * \brief 利用操作符重载
 * \param image
 * \param div
 */
void color_reduce13(Mat& image, const int div = 64)
{
	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// 掩码值
	const auto mask = 0xff << n;	// e.g. 比如div=16, mask= 0xF0

	// 进行色彩还原
	image = (image & Scalar(mask, mask, mask)) + Scalar(div / 2, div / 2, div / 2);
}

int main()
{
	waitKey(6000);
}