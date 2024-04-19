#include "FiltreHandler.h"

FiltreHandler::FiltreHandler()
{
	this->kernelType = ConvolutionKernel::identity;
	this->kernelName = "identité";
}

FiltreHandler::~FiltreHandler()
{
}

void FiltreHandler::setKernelType(ConvolutionKernel kernelType)
{
	this->kernelType = kernelType;
}

ConvolutionKernel FiltreHandler::getKernelType()
{
	return this->kernelType;
}

void FiltreHandler::setKernelName(string kernelName)
{
	this->kernelName = kernelName;
}

string FiltreHandler::getKernelName()
{
	return this->kernelName;
}

FiltreHandler* FiltreHandler::getInstance()
{
	if(!this->instance)
	{
		this->instance = new FiltreHandler();
	}
	return this->instance;
}

void FiltreHandler::deleteInstance()
{
	if(this->instance)
	{
		delete this->instance;
		this->instance = nullptr;
	}
}
