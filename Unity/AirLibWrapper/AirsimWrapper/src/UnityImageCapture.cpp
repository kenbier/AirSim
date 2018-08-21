#include "UnityImageCapture.h"
#include <chrono>
#include "PInvokeWrapper.h"


namespace AirSimUnity
{
	UnityImageCapture::UnityImageCapture(int VId)
	{
		vehicleID = VId;
	}

	UnityImageCapture::~UnityImageCapture()
	{

	}

	// overrides getImages() method in the ImageCaptureBase class.
	void UnityImageCapture::getImages(const std::vector<msr::airlib::ImageCaptureBase::ImageRequest>& requests,
		std::vector<msr::airlib::ImageCaptureBase::ImageResponse>& responses)
	{
		if (requests.size() > 0)
		{
			for (int i = 0; i < requests.size(); i++)
			{
				ImageResponse airsim_response;
				responses.push_back(airsim_response);
				AirSimImageRequest request = ConverttoUnityRequest(requests[i]);
				AirSimImageResponse response = GetSimImages(request, vehicleID);  //Into Unity
				ConverttoAirsimResponse(response, responses[i]);
			}
		}
	}

	// converts AirLib ImageRequest to Unity ImageRequest which can be passed to the PInvoke method
	AirSimImageRequest UnityImageCapture::ConverttoUnityRequest(const msr::airlib::ImageCaptureBase::ImageRequest &request)
	{
		AirSimImageRequest airsim_request;
		airsim_request.camera_id = request.camera_id;
		airsim_request.compress = request.compress;
		airsim_request.image_type = request.image_type;
		airsim_request.pixels_as_float = airsim_request.pixels_as_float;
		return airsim_request;
	}

	//Converts Unity ImageResponse to AirLib ImageResponse
	void UnityImageCapture::ConverttoAirsimResponse(AirSimImageResponse &src, msr::airlib::ImageCaptureBase::ImageResponse &dest)
	{
		dest.camera_id = src.camera_id;
		dest.camera_position.x() = src.camera_position.x;
		dest.camera_position.y() = src.camera_position.y;
		dest.camera_position.z() = src.camera_position.z;
		dest.camera_orientation.x() = src.camera_orientation.x;
		dest.camera_orientation.y() = src.camera_orientation.y;
		dest.camera_orientation.z() = src.camera_orientation.z;
		dest.camera_orientation.w() = src.camera_orientation.w;
		dest.time_stamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		if (src.image_uint_len == 0 && src.image_float_len)
		{
			dest.message = "no image capture";
		}
		else
		{
			dest.message = "success";
		}
		dest.pixels_as_float = src.pixels_as_float;
		dest.compress = src.compress;
		dest.width = src.width;
		dest.height = src.height;
		dest.image_type = src.image_type;
		dest.image_data_float.clear();
		dest.image_data_uint8.clear();
		for (int i = 0; i < src.image_uint_len; i++)
		{
			dest.image_data_uint8.push_back(static_cast<unsigned char>(src.image_data_uint[i]));
		}
		for (int i = 0; i < src.image_float_len; i++)
		{
			dest.image_data_float.push_back(src.image_data_float[i]);
		}
	}
}