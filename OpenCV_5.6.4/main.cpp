#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	system("color 6F");

	// 初始化
	FileStorage fs("..\\_files\\test.yaml", FileStorage::READ);
	// 第一种方法，对FileNode操作
	const auto frame_count = static_cast<int>(fs["frameCount"]);

	String date;
	// 第二种方法，使用FileNode运算符>>
	fs["calibration_date"] >> date;

	Mat camera_matrix, dist_coeffs;
	fs["camera_matrix"] >> camera_matrix;
	fs["dist_coeffs"] >> dist_coeffs;

	std::cout << "frame_count: " << frame_count << std::endl
		<< "calibration_data: " << date << std::endl
		<< "camera_matrix: " << camera_matrix << std::endl
		<< "distortion_coeffs" << dist_coeffs << std::endl;

	const auto features = fs["features"];
	auto it_begin = features.begin();
	const auto it_end = features.end();
	auto idx = 0;
	std::vector<uchar> lbpval;

	// 使用FileNodeIterator遍历序列
	for (; it_begin != it_end; ++it_begin, idx++)
	{
		std::cout << "feature #"<<idx<<": ";
		std::cout << "x="<<static_cast<int>((*it_begin)["x"])<<", y="<<(int)(*it_begin)["y"]<<", lbp:(";
		// 我们也可以使用filenode >> std::vector操作符很容易的读数值阵列
		(*it_begin)["lbp"] >> lbpval;
		for (auto i : lbpval)
		{
			std::cout << " "<<static_cast<int>(i);
		}
		std::cout << ")" << std::endl;
	}
	fs.release();

	waitKey(0);
	return 0;
}