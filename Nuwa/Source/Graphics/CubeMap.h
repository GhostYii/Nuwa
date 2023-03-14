#pragma once
#include "IBindable.h"

namespace Nuwa
{
	class CubeMap : public IBindable
	{
	public:
		CubeMap();
		virtual ~CubeMap();

		// Inherited via IBindable
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void Clear() override;

		void Load(std::string& path);
	private:

	};


}