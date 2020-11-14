/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
// Copyright (C) 2000-2008, Intel Corporation, all rights reserved.
// Copyright (C) 2009, Willow Garage Inc., all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Copyright (c) 2020 RedPower(redpower2004@21cn.com), all rights reserved.
// RGB to Bayer is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
// 		 http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details.
//
//M*/


#include <iostream>
#include <opencv2/opencv.hpp>


//  Convert RGB image To Bayer image
//  in param: rgb: RGB image
//  out param: bayerbg Bayer BG image
void RGB2BayerBG(cv::Mat& rgb, cv::Mat& bayerbg)
{
	if (bayerbg.empty() || bayerbg.rows != rgb.rows || bayerbg.cols != rgb.cols)
		bayerbg = cv::Mat(rgb.rows, rgb.cols, CV_8UC1);

	for (int height = 0; height < rgb.rows; height++)
	{
		for (int width = 0; width < rgb.cols; width++)
		{
			cv::Vec3b pix = rgb.at<cv::Vec3b>(height, width);
			if ((height % 2 == 1) && (width % 2 == 1))
				bayerbg.at<uchar>(height, width) = pix[2];
			else if (((height % 2 == 1) && (width % 2 == 0)) ||
				((height % 2 == 0) && (width % 2 == 1)))
				bayerbg.at<uchar>(height, width) = pix[1];
			else
				bayerbg.at<uchar>(height, width) = pix[0];
		}
	}
}


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Usage:" << argv[0] << " <input RGB image> <output Bayer image>" << std::endl;
		return 1;
	}
	std::cout << "BayerBG To RGB sample" << std::endl;
	cv::Mat img = cv::imread(argv[1]);
	if (img.empty())
	{
		std::cout << "Error: Input file " << argv[1] << "is error" << std::endl;
		return 2;
	}
	cv::Mat out_bayer;
	cv::Mat out_rgb;
	RGB2BayerBG(img, out_bayer);
	cv::imwrite(argv[2], out_bayer);
	cv::imshow("in", img);
	cv::imshow("out_bayer", out_bayer);
	//cv::cvtColor(out_bayer, out_rgb, cv::COLOR_BayerBG2RGB); //Check
	//cv::imshow("out_rgb", out_rgb);
	cv::waitKey(-1);
	return 0;
}

