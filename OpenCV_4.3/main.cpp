#include <opencv2/opencv.hpp>
using namespace cv;

constexpr auto window_width = 600;
constexpr auto window_name1 = "【绘制图1】";
constexpr auto window_name2 = "【绘制图2】";

void draw_ellipse(Mat img, double angle);
void draw_filled_circle(Mat img, const Point& center);
void draw_polygon(Mat img);
void draw_line(Mat img, const Point& start, const Point& end);

int main() {
	// 创建空白的Mat图像
	const Mat atom_image = Mat::zeros(window_width, window_width, CV_8UC3);
	Mat rook_image = Mat::zeros(window_width, window_width, CV_8UC3);

	// 【1.1】绘制4个椭圆
	draw_ellipse(atom_image, 90);
	draw_ellipse(atom_image, 0);
	draw_ellipse(atom_image, 45);
	draw_ellipse(atom_image, -45);

	// 【1.2】绘制圆心
	draw_filled_circle(atom_image, Point(window_width / 2, window_width / 2));

	// 【2.1】绘制多边形
	draw_polygon(rook_image);

	// 【2.2】绘制矩形
	rectangle(rook_image,
		Point(0, 7 * window_width / 8),
		Point(window_width, window_width),
		Scalar(0, 255, 255),
		-1,
		8);

	// 【2.3】绘制一些线段
	draw_line(rook_image,
		Point(0, 15 * window_width / 16),
		Point(window_width, 15 * window_width / 16));
	draw_line(rook_image,
		Point(window_width / 4, 7 * window_width / 8),
		Point(window_width / 4, window_width));
	draw_line(rook_image,
		Point(window_width / 2, 7 * window_width / 8),
		Point(window_width / 2, window_width));
	draw_line(rook_image,
		Point(3 * window_width / 4, 7 * window_width / 8),
		Point(3 * window_width / 4, window_width));

	// 显示绘制出来的图像
	imshow(window_name1, atom_image);
	moveWindow(window_name1, 0, 200);
	imshow(window_name2, rook_image);
	moveWindow(window_name2, window_width, 200);

	waitKey(0);
	return 0;
}

void draw_ellipse(Mat img, double angle)
{
	const auto thickness = 2;
	const auto line_type = 8;

	ellipse(img,
		Point(window_width / 2, window_width / 2),
		Size(window_width / 4, window_width / 16),
		angle,
		0,
		360,
		Scalar(255, 129, 0),
		thickness,
		line_type);
}

void draw_filled_circle(Mat img, const Point& center)
{
	const auto thickness = -1;
	const auto line_type = 8;

	circle(img,
		center,
		window_width / 32,
		Scalar(0, 0, 255),
		thickness,
		line_type);
}

// 凹四边形的绘制
void draw_polygon(Mat img)
{
	const auto line_type = 8;

	// 创建一些点
	Point rook_points[1][20];
	rook_points[0][0] = Point(window_width / 4, 7 * window_width / 8);
	rook_points[0][1] = Point(3 * window_width / 4, 7 * window_width / 8);
	rook_points[0][2] = Point(3 * window_width / 4, 13 * window_width / 16);
	rook_points[0][3] = Point(11 * window_width / 16, 13 * window_width / 16);
	rook_points[0][4] = Point(19 * window_width / 32, 3 * window_width / 8);
	rook_points[0][5] = Point(3 * window_width / 4, 3 * window_width / 8);
	rook_points[0][6] = Point(3 * window_width / 4, window_width / 8);
	rook_points[0][7] = Point(26 * window_width / 40, window_width / 8);
	rook_points[0][8] = Point(26 * window_width / 40, window_width / 4);
	rook_points[0][9] = Point(22 * window_width / 40, window_width / 4);
	rook_points[0][10] = Point(22 * window_width / 40, window_width / 8);
	rook_points[0][11] = Point(18 * window_width / 40, window_width / 8);
	rook_points[0][12] = Point(18 * window_width / 40, window_width / 4);
	rook_points[0][13] = Point(14 * window_width / 40, window_width / 4);
	rook_points[0][14] = Point(14 * window_width / 40, window_width / 8);
	rook_points[0][15] = Point(window_width / 4, window_width / 8);
	rook_points[0][16] = Point(window_width / 4, 3 * window_width / 8);
	rook_points[0][17] = Point(13 * window_width / 32, 3 * window_width / 8);
	rook_points[0][18] = Point(5 * window_width / 16, 13 * window_width / 16);
	rook_points[0][19] = Point(window_width / 4, 13 * window_width / 16);

	const Point* ppt[1] = { rook_points[0] };
	int npt[] = { 20 };

	fillPoly(img, ppt, npt, 1, Scalar(255, 255, 255), line_type);
}

void draw_line(Mat img, const Point& start, const Point& end)
{
	const auto thickness = 2;
	const auto line_type = 8;
	line(img, start, end, Scalar(0, 0, 0), thickness, line_type);
}
