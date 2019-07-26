#include <opencv2/opencv.hpp>
using namespace cv;

constexpr auto n_tests = 14;
constexpr auto n_iterations = 20;

/**
 * \brief ����.ptr��[]
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
 * \brief ����.ptr��* ++
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
 * \brief ����.ptr �� * ++ �Լ�ģ����
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
 * \brief ����.ptr �� * ++ �Լ�λ����
 * \param image
 * \param div
 */
void color_reduce3(Mat& image, const int div = 64)
{
	const auto rows = image.rows;
	const auto cols = image.cols * image.channels();
	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// ����ֵ
	const auto mask = 0xff << n; // ����div=16��mask = 0xf0

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
 * \brief ����ָ����������
 * \param image
 * \param div
 */
void color_reduce4(Mat& image, const int div = 64)
{
	const auto rows = image.rows;
	const auto cols = image.cols * image.channels();
	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	const auto step = image.step; // ��Ч���
	// ����ֵ
	const auto mask = 0xff << n; // ����div=16��mask = 0xf0

	// ��ȡֻ��ͼ�񻺳�����ָ��
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
 * \brief ���� .ptr �� * ++�Լ�λ���㡢image.cols * image.channels()
 * \param image
 * \param div
 */
void color_reduce5(Mat& image, const int div = 64)
{
	const auto rows = image.rows;
	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// ����ֵ
	const auto mask = 0xff << n; // ����div=16��mask = 0xf0

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
 * \brief ����.ptr �� * ++ �Լ�λ����(continuous)
 * \param image
 * \param div
 */
void color_reduce6(Mat& image, const int div = 64)
{
	auto rows = image.rows;
	auto cols = image.cols * image.channels();

	if (image.isContinuous())
	{
		// ���������
		cols = cols * rows;
		rows = 1;
	}

	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// ����ֵ
	const auto mask = 0xff << n; // ����div=16��mask = 0xf0

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
 * \brief ���� .ptr �� * ++ �Լ�λ���� (continuous+channels)
 * \param image
 * \param div
 */
void color_reduce7(Mat& image, const int div = 64)
{
	auto rows = image.rows;
	auto cols = image.cols;

	if (image.isContinuous())
	{
		// ���������
		cols = cols * rows;
		rows = 1;
	}

	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// ����ֵ
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
 * \brief ����Mat_ iterator
 * \param image
 * \param div
 */
void color_reduce8(Mat& image, const int div = 64)
{
	// ��ȡ������
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
 * \brief ����Mat_ iterator�Լ�λ����
 * \param image
 * \param div
 */
void color_reduce9(Mat& image, const int div = 64)
{
	// div������2����
	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// ����ֵ
	const uchar mask = 0xff << n;

	// ��ȡ������
	auto it_begin = image.begin<Vec3b>();
	const auto it_end = image.end<Vec3b>();

	// ɨ������Ԫ��
	for (; it_begin != it_end; ++it_begin)
	{
		(*it_begin)[0] = (*it_begin)[0] & mask + div / 2;
		(*it_begin)[1] = (*it_begin)[1] & mask + div / 2;
		(*it_begin)[2] = (*it_begin)[2] & mask + div / 2;
	}
}

/**
 * \brief ����Mat Iterator_
 * \param image
 * \param div
 */
void color_reduce10(Mat& image, const int div = 64)
{
	// ��ȡ������
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
 * \brief ���ö�̬��ַ�������at
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
 * \brief ����ͼ������������
 * \param image ����ͼ��
 * \param result ���ͼ��
 * \param div
 */
void color_reduce12(const Mat& image, Mat& result, const int div = 64)
{
	auto rows = image.rows;
	auto cols = image.cols;

	// ׼���ó�ʼ�����Mat�����ͼ��
	result.create(image.rows, image.cols, image.type());

	// ��������������ͼ��
	cols = cols * rows;
	rows = 1;	// ��ά����

	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// ����ֵ
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
 * \brief ���ò���������
 * \param image
 * \param div
 */
void color_reduce13(Mat& image, const int div = 64)
{
	const auto n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
	// ����ֵ
	const auto mask = 0xff << n;	// e.g. ����div=16, mask= 0xF0

	// ����ɫ�ʻ�ԭ
	image = (image & Scalar(mask, mask, mask)) + Scalar(div / 2, div / 2, div / 2);
}

int main()
{
	waitKey(6000);
}