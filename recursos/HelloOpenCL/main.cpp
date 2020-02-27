/*
 * main.cpp
 *
 *  Created on: Sep 7, 2018
 *      Author: jack
 */

#include <CL/cl.h>
#include <CL/cl.hpp>
#include <stdio.h>
#include <stdlib.h>

//https://stackoverflow.com/questions/24326432/convenient-way-to-show-opencl-error-codes
const char *getErrorString(cl_int error)
{
switch(error){
    // run-time and JIT compiler errors
    case 0: return "CL_SUCCESS";
    case -1: return "CL_DEVICE_NOT_FOUND";
    case -2: return "CL_DEVICE_NOT_AVAILABLE";
    case -3: return "CL_COMPILER_NOT_AVAILABLE";
    case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
    case -5: return "CL_OUT_OF_RESOURCES";
    case -6: return "CL_OUT_OF_HOST_MEMORY";
    case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
    case -8: return "CL_MEM_COPY_OVERLAP";
    case -9: return "CL_IMAGE_FORMAT_MISMATCH";
    case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
    case -11: return "CL_BUILD_PROGRAM_FAILURE";
    case -12: return "CL_MAP_FAILURE";
    case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
    case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
    case -15: return "CL_COMPILE_PROGRAM_FAILURE";
    case -16: return "CL_LINKER_NOT_AVAILABLE";
    case -17: return "CL_LINK_PROGRAM_FAILURE";
    case -18: return "CL_DEVICE_PARTITION_FAILED";
    case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

    // compile-time errors
    case -30: return "CL_INVALID_VALUE";
    case -31: return "CL_INVALID_DEVICE_TYPE";
    case -32: return "CL_INVALID_PLATFORM";
    case -33: return "CL_INVALID_DEVICE";
    case -34: return "CL_INVALID_CONTEXT";
    case -35: return "CL_INVALID_QUEUE_PROPERTIES";
    case -36: return "CL_INVALID_COMMAND_QUEUE";
    case -37: return "CL_INVALID_HOST_PTR";
    case -38: return "CL_INVALID_MEM_OBJECT";
    case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
    case -40: return "CL_INVALID_IMAGE_SIZE";
    case -41: return "CL_INVALID_SAMPLER";
    case -42: return "CL_INVALID_BINARY";
    case -43: return "CL_INVALID_BUILD_OPTIONS";
    case -44: return "CL_INVALID_PROGRAM";
    case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
    case -46: return "CL_INVALID_KERNEL_NAME";
    case -47: return "CL_INVALID_KERNEL_DEFINITION";
    case -48: return "CL_INVALID_KERNEL";
    case -49: return "CL_INVALID_ARG_INDEX";
    case -50: return "CL_INVALID_ARG_VALUE";
    case -51: return "CL_INVALID_ARG_SIZE";
    case -52: return "CL_INVALID_KERNEL_ARGS";
    case -53: return "CL_INVALID_WORK_DIMENSION";
    case -54: return "CL_INVALID_WORK_GROUP_SIZE";
    case -55: return "CL_INVALID_WORK_ITEM_SIZE";
    case -56: return "CL_INVALID_GLOBAL_OFFSET";
    case -57: return "CL_INVALID_EVENT_WAIT_LIST";
    case -58: return "CL_INVALID_EVENT";
    case -59: return "CL_INVALID_OPERATION";
    case -60: return "CL_INVALID_GL_OBJECT";
    case -61: return "CL_INVALID_BUFFER_SIZE";
    case -62: return "CL_INVALID_MIP_LEVEL";
    case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
    case -64: return "CL_INVALID_PROPERTY";
    case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
    case -66: return "CL_INVALID_COMPILER_OPTIONS";
    case -67: return "CL_INVALID_LINKER_OPTIONS";
    case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

    // extension errors
    case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
    case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
    case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
    case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
    case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
    case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
    default: return "Unknown OpenCL error";
    }
}

int main(){
	cl_uint result;

	cl_uint platformCount=0;

	//cl.h
	result=clGetPlatformIDs(0,nullptr,&platformCount);
	if(result!=CL_SUCCESS){
		printf("%s\n",getErrorString(result));
		return 1;
	}

	cl_platform_id*platforms=(cl_platform_id*)malloc(platformCount*sizeof(cl_platform_id));
	clGetPlatformIDs(platformCount,platforms,nullptr);

	for(unsigned int i=0;i<platformCount;i++){
		cl_platform_id platform=platforms[i];

		printf("Platform\n");

		size_t nameSize;
		clGetPlatformInfo(platform,CL_PLATFORM_NAME,0,nullptr,&nameSize);
		char*name=(char*)malloc(nameSize);
		clGetPlatformInfo(platform,CL_PLATFORM_NAME,nameSize,name,nullptr);
		printf("Name: %s\n",name);

		size_t vendorSize;
		clGetPlatformInfo(platform,CL_PLATFORM_VENDOR,0,nullptr,&vendorSize);
		char*vendor=(char*)malloc(vendorSize);
		clGetPlatformInfo(platform,CL_PLATFORM_VENDOR,vendorSize,vendor,nullptr);
		printf("Vendor: %s\n",vendor);

		cl_uint deviceCount=0;
		clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,0,nullptr,&deviceCount);

		cl_device_id*devices=(cl_device_id*)malloc(deviceCount*sizeof(cl_device_id));
		clGetDeviceIDs(platform,CL_DEVICE_TYPE_ALL,deviceCount,devices,nullptr);

		for(unsigned int j=0;j<deviceCount;j++){
			cl_device_id device=devices[j];

			size_t nameSize;
			clGetDeviceInfo(device,CL_DEVICE_NAME,0,nullptr,&nameSize);
			char*name=(char*)malloc(nameSize);
			clGetDeviceInfo(device,CL_DEVICE_NAME,nameSize,name,nullptr);
			printf("\tDevice name: %s\n",name);

			size_t vendorSize;
			clGetDeviceInfo(device,CL_DEVICE_VENDOR,0,nullptr,&vendorSize);
			char*vendor=(char*)malloc(vendorSize);
			clGetDeviceInfo(device,CL_DEVICE_VENDOR,vendorSize,vendor,nullptr);
			printf("\tDevice vendor: %s\n",vendor);

			size_t extensionSize;
			clGetDeviceInfo(device,CL_DEVICE_EXTENSIONS,0,nullptr,&extensionSize);
			char* extensions=(char*)malloc(extensionSize);
			clGetDeviceInfo(device,CL_DEVICE_EXTENSIONS,extensionSize,extensions,nullptr);
			printf("\tExtensions: %s\n",extensions);
		}
	}

	printf("\n\n*************************************************\n\n");

	//CL.HPP
	{
		std::vector<cl::Platform> platforms;
		cl::Platform::get(&platforms);

		for(unsigned int i=0;i<platforms.size();i++){
			cl::Platform platform=platforms[i];
			printf("Name .... %s\n",platform.getInfo<CL_PLATFORM_NAME>().c_str());
			printf("Version . %s\n",platform.getInfo<CL_PLATFORM_VERSION>().c_str());
			printf("Vendor .. %s\n",platform.getInfo<CL_PLATFORM_VENDOR>().c_str());

			std::vector<cl::Device> devices;
			platform.getDevices(CL_DEVICE_TYPE_ALL,&devices);

			for(unsigned int j=0;j<devices.size();j++){
				cl::Device device=devices[j];

				printf("\tName .... %s\n",device.getInfo<CL_DEVICE_NAME>().c_str());
				printf("\tVersion . %s\n",device.getInfo<CL_DEVICE_VERSION>().c_str());
				printf("\tVendor .. %s\n",device.getInfo<CL_DEVICE_VENDOR>().c_str());

				int type=device.getInfo<CL_DEVICE_TYPE>();
				printf("\tType .... ");
				switch(type){
				case CL_DEVICE_TYPE_GPU: printf("GPU"); break;
				case CL_DEVICE_TYPE_CPU: printf("CPU"); break;
				case CL_DEVICE_TYPE_ACCELERATOR: printf("Accelerator"); break;
				case CL_DEVICE_TYPE_CUSTOM: printf("Custom"); break;
				}
				printf("\n");

			}

		}
	}

	return 0;
}
