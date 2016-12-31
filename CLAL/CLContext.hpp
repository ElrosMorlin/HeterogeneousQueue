
#ifndef _CLAL_CLCONTEXT_HPP_
#define _CLAL_CLCONTEXT_HPP_

#include <vector>

#include "CLReferenceCount.hpp"
#include "CLDevice.hpp"
//#include "CLCommandQueue.hpp"

#include "CLEvent.hpp"
#include "CLProgram.hpp"
#include "CLBuffer.hpp"

namespace CLAL {

	class CLCommandQueue;

	class CLContext : public ReferenceCount<cl_context, clRetainContext, clReleaseContext> {



	public:

		// KAOCC: need to setup proper parameter

		// For single device
		static CLContext create(CLDevice device, cl_context_properties* props = nullptr);

		// For multiple device
		static CLContext create(const std::vector<CLDevice>& devices, cl_context_properties* props = nullptr);

		// For OpenCL primitive function
		static CLContext create(cl_context context, cl_device_id* primDevices, cl_command_queue* primCQs, size_t numDevices);

		// KAOCC: do we need public ctor with no parameter?
		// CLContext();


		size_t getDeviceCount() const;
		CLDevice getDevice(size_t index) const;


		// For Buffer

		// KAOCC: setup parameter
		CLBuffer createBuffer();

		// KAOCC: write / read  buffers ?



		// For program and execution

		CLProgram createProgram(const std::vector<char>& sourceCode, char const* buildOpts = nullptr);
		CLEvent execute1D(unsigned int idx, size_t globalSize, size_t localSize, cl_kernel kernel);
		CLEvent execute1D(unsigned int idx, size_t globalSize, size_t localSize, cl_kernel kernel, CLEvent depEvent);


		// For C.Q.
		void finish(size_t index);
		void flush(size_t index);
		CLCommandQueue getCommandQueue(size_t index);





		virtual ~CLContext();



	private:

		// KAOCC: check the parameters

		// private ctors
		// wrap cl_context
		CLContext(cl_context context, const std::vector<CLDevice>& devices, const std::vector<CLCommandQueue>& cqs);

		// Pass by value ! Let the compiler decides.
		CLContext(cl_context context, std::vector<CLDevice> devices);

		//CLContext(cl_context context, const std::vector<CLDevice>& devices);


		// Create C.Q. for each devices
		void createCQs();

		std::vector<CLDevice> devices;
		std::vector<CLCommandQueue> commandQueues;

	};


}




#endif

