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
	Microsoft::WRL::ComPtr<ID3D12Device4> CreateDevice(IDXGIAdapter& adapter, D3D_FEATURE_LEVEL minimumFeatureLevel)
	{
		Microsoft::WRL::ComPtr<ID3D12Device4> device;
		D3D12::ThrowIfFailed(D3D12CreateDevice(&adapter, minimumFeatureLevel, IID_PPV_ARGS(&device)));
		return device;
	}
}