#include "D3D12_utilities.h"

namespace Maia::Renderer::D3D12
{
	winrt::com_ptr<IDXGIFactory6> create_factory(UINT flags)
	{
		winrt::com_ptr<IDXGIFactory6> factory;
		CreateDXGIFactory2(flags, __uuidof(factory), factory.put_void());
		return factory;
	}
	winrt::com_ptr<IDXGIAdapter4> select_adapter(IDXGIFactory6& factory, bool select_WARP_adapter)
	{
		if (select_WARP_adapter)
		{
			winrt::com_ptr<IDXGIAdapter4> warp_adapter;
			winrt::check_hresult(
				factory.EnumWarpAdapter(__uuidof(warp_adapter), warp_adapter.put_void()));

			return warp_adapter;
		}

		else
		{
			winrt::com_ptr<IDXGIAdapter4> hardware_adapter;
			winrt::check_hresult(
				factory.EnumAdapterByGpuPreference(0, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, __uuidof(hardware_adapter), hardware_adapter.put_void()));

			return hardware_adapter;
		}
	}
	winrt::com_ptr<ID3D12Device4> create_device(IDXGIAdapter& adapter, D3D_FEATURE_LEVEL minimum_feature_level)
	{
		winrt::com_ptr<ID3D12Device4> device;
		winrt::check_hresult(
			D3D12CreateDevice(&adapter, minimum_feature_level, __uuidof(device), device.put_void()));

		return device;
	}
	winrt::com_ptr<ID3D12CommandAllocator> create_commandA_allocator(ID3D12Device& device, D3D12_COMMAND_LIST_TYPE type)
	{
		winrt::com_ptr<ID3D12CommandAllocator> command_allocator;
		winrt::check_hresult(
			device.CreateCommandAllocator(type, __uuidof(command_allocator), command_allocator.put_void()));

		return command_allocator;
	}
	winrt::com_ptr<ID3D12GraphicsCommandList> create_opened_graphics_command_list(
		ID3D12Device& device, UINT node_mask, D3D12_COMMAND_LIST_TYPE type, 
		ID3D12CommandAllocator& command_allocator, ID3D12PipelineState* initial_state
	)
	{
		winrt::com_ptr<ID3D12GraphicsCommandList> command_list;
		winrt::check_hresult(
			device.CreateCommandList(node_mask, type, &command_allocator, initial_state, __uuidof(command_list), command_list.put_void()));

		return command_list;
	}
	winrt::com_ptr<ID3D12GraphicsCommandList> create_closed_graphics_command_list(
		ID3D12Device& device, UINT node_mask, D3D12_COMMAND_LIST_TYPE type,
		ID3D12CommandAllocator& command_allocator, ID3D12PipelineState* initial_state
	)
	{
		auto const command_list = create_opened_graphics_command_list(device, node_mask, type, command_allocator, initial_state);
		winrt::check_hresult(
			command_list->Close());

		return command_list;
	}
}
