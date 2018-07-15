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
	Microsoft::WRL::ComPtr<ID3D12Device4> CreateD3DDevice(IDXGIAdapter& adapter, D3D_FEATURE_LEVEL minimumFeatureLevel);
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(ID3D12Device& d3dDevice, D3D12_COMMAND_LIST_TYPE type);
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CreateOpenedGraphicsCommandList(ID3D12Device& d3dDevice, UINT nodeMask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator& commandAllocator, ID3D12PipelineState* initialState = nullptr);
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CreateClosedGraphicsCommandList(ID3D12Device& d3dDevice, UINT nodeMask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator& commandAllocator, ID3D12PipelineState* initialState = nullptr);
}