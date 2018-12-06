#include <iostream>

#include <winrt/base.h>

#include <d3dcompiler.h>

#include "Shader.hpp"

namespace Maia::Renderer::D3D12
{
	namespace
	{
		winrt::com_ptr<ID3DBlob> create_shader_blob(std::filesystem::path const& shader_path, std::string_view entry_point, std::string_view target)
		{
			winrt::com_ptr<ID3DBlob> shader_blob;
			winrt::com_ptr<ID3DBlob> error_messages_blob;

			HRESULT const result =
				D3DCompileFromFile(
					shader_path.c_str(),
					nullptr,
					D3D_COMPILE_STANDARD_FILE_INCLUDE,
					entry_point.data(),
					target.data(),
					D3DCOMPILE_DEBUG,
					0,
					shader_blob.put(),
					error_messages_blob.put()
				);

			if (FAILED(result))
			{
				std::wstring_view error_messages
				{ 
					reinterpret_cast<wchar_t*>(error_messages_blob->GetBufferPointer()), 
					static_cast<std::size_t>(error_messages_blob->GetBufferSize())
				};
				
				std::cerr << error_messages.data();

				winrt::check_hresult(result);
			}

			return shader_blob;
		}
	}

	Shader::Shader(std::filesystem::path const& shader_path, std::string_view entry_point, std::string_view target) :
		shader_blob{ create_shader_blob(shader_path, entry_point, target) }
	{
	}

	D3D12_SHADER_BYTECODE Shader::bytecode() const
	{
		return
		{
			shader_blob->GetBufferPointer(),
			shader_blob->GetBufferSize()
		};
	}
}