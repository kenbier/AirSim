#pragma once

#include "common/ImageCaptureBase.hpp"
#include "AirSimStructs.hpp"

using namespace AirSimUnity;

/*
* Implementation of ImageCaptureBase(defined in AirLib) that is used  by vehicles to capture images.
*/

namespace AirSimUnity
{
	class UnityImageCapture : public msr::airlib::ImageCaptureBase
	{
	private:
		int vehicleID;   //vehicle index
	public:
		typedef msr::airlib::ImageCaptureBase::ImageType ImageType;
		UnityImageCapture(int VId);
		virtual ~UnityImageCapture();
		virtual void getImages(const std::vector<ImageRequest>& requests, std::vector<ImageResponse>& responses) override;
		virtual AirSimImageRequest ConverttoUnityRequest(const msr::airlib::ImageCaptureBase::ImageRequest &request);
		virtual void ConverttoAirsimResponse(AirSimImageResponse &src, msr::airlib::ImageCaptureBase::ImageResponse &dest);
	};
}