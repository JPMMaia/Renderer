#include "DXUtilities.h"

namespace Maia::Renderer::D3D12
{
	Microsoft::WRL::ComPtr<IDXGIFactory6> CreateFactory(UINT flags)
	{
		Microsoft::WRL::ComPtr<IDXGIFactory6> factory;
		CreateDXGIFactory2(flags, IID_PPV_ARGS(&factory));
		return factory;
	}
	Microsoft::WRL::ComPtr<IDXGIAdapter4> SelectAdapter(IDXGIFactory6& factory, bool selectWarpAdapter)
	{
		if (selectWarpAdapter)
		{
			Microsoft::WRL::ComPtr<IDXGIAdapter4> warpAdapter;
			D3D12::ThrowIfFailed(factory.EnumWarpAdapter(IID_PPV_ARGS(&warpAdapter)));
			return warpAdapter;
		}

		else
		{
			Microsoft::WRL::ComPtr<IDXGIAdapter4> hardwareAdapter;
			D3D12::ThrowIfFailed(factory.EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&hardwareAdapter)));
			return hardwareAdapter;
		}
	}
	Microsoft::WRL::ComPtr<ID3D12Device4> CreateD3DDevice(IDXGIAdapter& adapter, D3D_FEATURE_LEVEL minimumFeatureLevel)
	{
		Microsoft::WRL::ComPtr<ID3D12Device4> d3dDevice;
		D3D12::ThrowIfFailed(D3D12CreateDevice(&adapter, minimumFeatureLevel, IID_PPV_ARGS(&d3dDevice)));
		return d3dDevice;
	}
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> CreateCommandAllocator(ID3D12Device& d3dDevice, D3D12_COMMAND_LIST_TYPE type)
	{
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
		D3D12::ThrowIfFailed(d3dDevice.CreateCommandAllocator(type, IID_PPV_ARGS(&commandAllocator)));
		return commandAllocator;
	}
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CreateOpenedGraphicsCommandList(ID3D12Device& d3dDevice, UINT nodeMask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator& commandAllocator, ID3D12PipelineState* initialState)
	{
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
		D3D12::ThrowIfFailed(d3dDevice.CreateCommandList(nodeMask, type, &commandAllocator, initialState, IID_PPV_ARGS(&commandList)));
		return commandList;
	}
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CreateClosedGraphicsCommandList(ID3D12Device& d3dDevice, UINT nodeMask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator& commandAllocator, ID3D12PipelineState* initialState)
	{
		auto commandList = CreateOpenedGraphicsCommandList(d3dDevice, nodeMask, type, commandAllocator, initialState);
		D3D12::ThrowIfFailed(commandList->Close());
		return commandList;
	}
}
