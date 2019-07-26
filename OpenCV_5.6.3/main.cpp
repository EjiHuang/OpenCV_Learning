#include <opencv2/opencv.hpp>
using namespace cv;

constexpr auto time_max = 32;

int main() {
	system("color 5F");

	// 初始化
	FileStorage fs("..\\_files\\test.yaml", FileStorage::WRITE);
	// 开始文件写入
	fs << "frameCount" << 5;

	time_t raw_time;
	struct tm time_info{};
	char temp_chars[time_max];
	time(&raw_time);	// 获取时间
	localtime_s(&time_info, &raw_time);
	asctime_s(temp_chars, time_max, &time_info);
	fs << "calibration data" << temp_chars;

	const Mat camera_matrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
	const Mat dist_coeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);
	fs << "camera_matrix" << camera_matrix << "dist_coeffs" << dist_coeffs;

	fs << "features" << "[";
	for (auto i = 0; i < 3; ++i)
	{
		auto x = rand() % 640;
		auto y = rand() % 480;
		const uchar lbp = rand() % 256;

		fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";
		for (auto j = 0; j < 8; j++)
			fs << (lbp >> j & 1);
		fs << "]" << "}";
	}
	fs << "]";
	fs.release();

	printf("\n文件读写完毕，请在工程目录下查看生成的文件~");
	waitKey(0);
	return 0;
}