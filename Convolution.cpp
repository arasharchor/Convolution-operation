#include <iostream>
#include <opencv2\highgui.hpp>

using namespace std;
using namespace cv;

void Conv(int inImgWidth, uchar* inImage, int kernelWidth, int kernelHeight, float* Kernel, int outImgWidth, int outImgHeight, uchar* outImage)
{
	for (int i = 0; i < outImgWidth; ++i)
	{
		int k = i + (kernelWidth - 1);
		for (int j = 0; j < outImgHeight; ++j)
		{
			int l = j + (kernelHeight - 1);
			for (int m = 0; m < kernelWidth; ++m)
			{
				for (int n = 0; n < kernelHeight; ++n)
				{
					for (int channel = 0; channel < 3; ++channel)
						outImage[3 * (i + outImgWidth * j) + channel] += uchar(inImage[3 * ((k - m) + inImgWidth * (l - n)) + channel] * Kernel[m + kernelWidth * n]);
				}
			}
		}
	}
}

int main(int argc, char* argv[])
{
	Mat inImage = imread("C:/Users/Dmitry/Documents/baboon.jpg", 1);
	if (inImage.empty())
		return 1;

	int inImgWidth = inImage.size().width, inImgHeight = inImage.size().height;

	int kernelWidth = 5, kernelHeight = 3;

	float* Kernel = new float[kernelWidth * kernelHeight];
	
	for (int i = 0; i < kernelWidth; ++i)
		for (int j = 0; j < kernelHeight; ++j)
			Kernel[i + kernelWidth * j] = 0.1f;

	int outImgWidth = inImgWidth - (kernelWidth - 1), outImgHeigth = inImgHeight - (kernelHeight - 1);

	Mat outImage = Mat::zeros(Size(outImgWidth, outImgHeigth), CV_8UC3);

	Conv(inImgWidth, inImage.data, kernelWidth, kernelHeight, Kernel, outImgWidth, outImgHeigth, outImage.data);

	imshow("", outImage); cvWaitKey();

	delete[]Kernel;

	return 0;
}