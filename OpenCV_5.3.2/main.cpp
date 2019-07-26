#include <opencv2/opencv.hpp>
using namespace cv;

bool multi_channel_blending();

int main() {
	system("color 9F");

	if (multi_channel_blending())
	{
		std::cout << "\n���гɹ����ó�����Ҫ��ͼ��~! ";
	}

	waitKey(0);
	return 0;
}

bool multi_channel_blending()
{
	std::vector<Mat> channels;
	//=================����ɫͨ�����֡�=================
	//	��������ͨ�����-��ɫ��������
	//============================================

	// ����ͼƬ
	auto logo_image = imread("..\\_images\\dota_logo.jpg", 0);
	auto src_image = imread("..\\_images\\dota_jugg.jpg");

	if (!src_image.data)
	{
		std::cout << "��ȡ'..\\_images\\dota_jugg.jpg'����\n";
		return false;
	}
	if (!logo_image.data)
	{
		std::cout << "��ȡ'..\\_images\\dota_logo.jpg'����\n";
		return false;
	}

	// ��һ��3ͨ��ͼ��ת����3����ͨ��ͼ��
	split(src_image, channels);

	// ��ԭͼ����ɫͨ�����÷��ظ�image_blue_channel��ע�������ã��൱�����ߵȼۣ��޸�����һ����һ�����ű�
	const auto image_blue_channel = channels.at(0);
	// ��ԭͼ����ɫͨ���ģ�500��250�����괦���·���һ�������logoͼ���м�Ȩ���������õ��Ļ�Ͻ���浽imageBlueChannel��
	addWeighted(image_blue_channel(Rect(500, 250, logo_image.cols, logo_image.rows)), 
		1.0,
		logo_image, 
		0.5, 
		0., 
		image_blue_channel(Rect(500, 250, logo_image.cols, logo_image.rows)));

	// ��3����ͨ�����ºϲ���һ����ͨ��
	merge(channels, src_image);

	// ��ʾЧ��ͼ
	namedWindow(" <1>��Ϸԭ��+logo��ɫͨ��");
	imshow(" <1>��Ϸԭ��+logo��ɫͨ��", src_image);


	//=================����ɫͨ�����֡�=================
	//	��������ͨ�����-��ɫ��������
	//============================================

	// ���¶���ͼƬ
	logo_image = imread("..\\_images\\dota_logo.jpg", 0);
	src_image = imread("..\\_images\\dota_jugg.jpg");

	if (!src_image.data)
	{
		std::cout << "��ȡ'..\\_images\\dota_jugg.jpg'����\n";
		return false;
	}
	if (!logo_image.data)
	{
		std::cout << "��ȡ'..\\_images\\dota_logo.jpg'����\n";
		return false;
	}

	split(src_image, channels);
	const auto image_green_channel = channels.at(1);
	addWeighted(image_green_channel(Rect(500, 250, logo_image.cols, logo_image.rows)),
		1.0,
		logo_image,
		0.5,
		0.,
		image_green_channel(Rect(500, 250, logo_image.cols, logo_image.rows)));

	// ��3����ͨ�����ºϲ���һ����ͨ��
	merge(channels, src_image);

	// ��ʾЧ��ͼ
	namedWindow("<2>��Ϸԭ��+logo��ɫͨ��");
	imshow("<2>��Ϸԭ��+logo��ɫͨ��", src_image);


	//=================����ɫͨ�����֡�=================
	//	��������ͨ�����-��ɫ��������
	//============================================

	// ���¶���ͼƬ
	logo_image = imread("..\\_images\\dota_logo.jpg", 0);
	src_image = imread("..\\_images\\dota_jugg.jpg");

	if (!src_image.data)
	{
		std::cout << "��ȡ'..\\_images\\dota_jugg.jpg'����\n";
		return false;
	}
	if (!logo_image.data)
	{
		std::cout << "��ȡ'..\\_images\\dota_logo.jpg'����\n";
		return false;
	}

	split(src_image, channels);
	const auto image_red_channel = channels.at(2);
	addWeighted(image_red_channel(Rect(500, 250, logo_image.cols, logo_image.rows)),
		1.0,
		logo_image,
		0.5,
		0.,
		image_red_channel(Rect(500, 250, logo_image.cols, logo_image.rows)));
	merge(channels, src_image);
	// ��ʾЧ��ͼ
	namedWindow("<3>��Ϸԭ��+logo��ɫͨ�� ");
	imshow("<3>��Ϸԭ��+logo��ɫͨ�� ", src_image);

	return true;
}
