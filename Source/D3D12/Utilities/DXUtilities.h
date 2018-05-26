#include <stdexcept>

#include <comdef.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

namespace Maia::Renderer::D3D12
{
	inline void ThrowIfFailed(HRESULT result)
	{
		if (FAILED(result))
		{
			_com_error error(result);
			throw std::runtime_error(error.ErrorMessage());
		}
	}

	Microsoft::WRL::ComPtr<IDXGIFactory6> CreateFactory(UINT flags);
	Microsoft::WRL::ComPtr<IDXGIAdapter4> SelectAdapter(IDXGIFactory6& factory, bool selectWarpAdapter);
	Microsoft::WRL::ComPtr<ID3D12Device4> CreateDevice(IDXGIAdapter& adapter, D3D_FEATURE_LEVEL minimumFeatureLevel);
}