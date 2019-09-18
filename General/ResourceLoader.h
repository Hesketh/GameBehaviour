#pragma once
#include "ResourceContainer.h"
#include <string>

namespace Hesketh
{
	class ResourceLoader
	{
	public:
		ResourceLoader()	{ /**/ };
		~ResourceLoader()	{ /**/ };

		virtual void	LoadResource(std::string type, std::string filepath)	= 0;
		virtual void*	GetResource(std::string type, std::string filepath)		= 0;
	};
}

