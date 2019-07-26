#include <opencv2/opencv.hpp>
using namespace cv;

int main() {
	system("color 6F");

	// ��ʼ��
	FileStorage fs("..\\_files\\test.yaml", FileStorage::READ);
	// ��һ�ַ�������FileNode����
	const auto frame_count = static_cast<int>(fs["frameCount"]);

	String date;
	// �ڶ��ַ�����ʹ��FileNode�����>>
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

	// ʹ��FileNodeIterator��������
	for (; it_begin != it_end; ++it_begin, idx++)
	{
		std::cout << "feature #"<<idx<<": ";
		std::cout << "x="<<static_cast<int>((*it_begin)["x"])<<", y="<<(int)(*it_begin)["y"]<<", lbp:(";
		// ����Ҳ����ʹ��filenode >> std::vector�����������׵Ķ���ֵ����
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