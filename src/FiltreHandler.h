#pragma once
#include "ofMain.h"
#include "ConvolutionKernel.h"

class FiltreHandler
{
private:
	FiltreHandler();
	~FiltreHandler();

	ConvolutionKernel kernelType;
	string kernelName;
	FiltreHandler(FiltreHandler const&) = delete;
	void operator=(FiltreHandler const&) = delete;

public:
	static FiltreHandler* instance;
	FiltreHandler* getInstance();
	void deleteInstance();

	void setKernelType(ConvolutionKernel kernelType);
	ConvolutionKernel getKernelType();

	void setKernelName(string kernelName);
	string getKernelName();
};

FiltreHandler* FiltreHandler::instance = nullptr;