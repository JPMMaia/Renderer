#include "D3D12_utilities.hpp"

namespace Maia::Renderer::D3D12
{
	winrt::com_ptr<IDXGIFactory6> create_factory(UINT flags)
	{
		winrt::com_ptr<IDXGIFactory6> factory;
		winrt::check_hresult(
			CreateDXGIFactory2(flags, __uuidof(factory), factory.put_void()));
		return factory;
	}
	winrt::com_ptr<IDXGIAdapter4> select_adapter(IDXGIFactory6& factory, bool const select_WARP_adapter)
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
	winrt::com_ptr<IDXGISwapChain4> create_swap_chain(IDXGIFactory6& factory, IUnknown& device, IUnknown& window, DXGI_FORMAT format, UINT buffer_count)
	{
		DXGI_SWAP_CHAIN_DESC1 description{};
		description.Stereo = true;
		description.Format = format;
		description.SampleDesc.Count = 1;
		description.SampleDesc.Quality = 0;
		description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		description.BufferCount = buffer_count;
		description.Scaling = DXGI_SCALING_NONE;
		description.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		winrt::com_ptr<IDXGISwapChain1> swap_chain;
		winrt::check_hresult(
			factory.CreateSwapChainForCoreWindow(&device, &window, &description, nullptr, swap_chain.put()));

		winrt::com_ptr<IDXGISwapChain4> swap_chain_4;
		swap_chain->QueryInterface(swap_chain_4.put());
		return swap_chain_4;
	}

	winrt::com_ptr<ID3D12Device5> create_device(IDXGIAdapter& adapter, D3D_FEATURE_LEVEL const minimum_feature_level)
	{
		winrt::com_ptr<ID3D12Device5> device;
		winrt::check_hresult(
			D3D12CreateDevice(&adapter, minimum_feature_level, __uuidof(device), device.put_void()));

		return device;
	}
	winrt::com_ptr<ID3D12CommandQueue> create_command_queue(ID3D12Device& device, D3D12_COMMAND_LIST_TYPE const type, INT const priority, D3D12_COMMAND_QUEUE_FLAGS const flags, UINT const node_mask)
	{
		D3D12_COMMAND_QUEUE_DESC description;
		description.Type = type;
		description.Priority = priority;
		description.Flags = flags;
		description.NodeMask = node_mask;

		winrt::com_ptr<ID3D12CommandQueue> command_queue;
		device.CreateCommandQueue(&description, __uuidof(command_queue), command_queue.put_void());

		return command_queue;
	}
	winrt::com_ptr<ID3D12CommandAllocator> create_command_allocator(ID3D12Device& device, D3D12_COMMAND_LIST_TYPE const type)
	{
		winrt::com_ptr<ID3D12CommandAllocator> command_allocator;
		winrt::check_hresult(
			device.CreateCommandAllocator(type, __uuidof(command_allocator), command_allocator.put_void()));

		return command_allocator;
	}
	std::vector<winrt::com_ptr<ID3D12CommandAllocator>> create_command_allocators(ID3D12Device& device, D3D12_COMMAND_LIST_TYPE type, std::size_t count)
	{
		std::vector<winrt::com_ptr<ID3D12CommandAllocator>> command_allocators;
		command_allocators.reserve(count);

		for (std::size_t i = 0; i < count; ++i)
			command_allocators.emplace_back(create_command_allocator(device, type));

		return command_allocators;
	}
	winrt::com_ptr<ID3D12GraphicsCommandList> create_opened_graphics_command_list(
		ID3D12Device& device, UINT const node_mask, D3D12_COMMAND_LIST_TYPE const type, 
		ID3D12CommandAllocator& command_allocator, ID3D12PipelineState* const initial_state
	)
	{
		winrt::com_ptr<ID3D12GraphicsCommandList> command_list;
		winrt::check_hresult(
			device.CreateCommandList(node_mask, type, &command_allocator, initial_state, __uuidof(command_list), command_list.put_void()));

		return command_list;
	}
	winrt::com_ptr<ID3D12GraphicsCommandList> create_closed_graphics_command_list(
		ID3D12Device& device, UINT const node_mask, D3D12_COMMAND_LIST_TYPE const type,
		ID3D12CommandAllocator& command_allocator, ID3D12PipelineState* const initial_state
	)
	{
		auto const command_list = create_opened_graphics_command_list(device, node_mask, type, command_allocator, initial_state);
		winrt::check_hresult(
			command_list->Close());

		return command_list;
	}
	winrt::com_ptr<ID3D12DescriptorHeap> create_descriptor_heap(ID3D12Device& device, D3D12_DESCRIPTOR_HEAP_TYPE const type, UINT const num_descriptors, D3D12_DESCRIPTOR_HEAP_FLAGS const flags, UINT const node_mask)
	{
		D3D12_DESCRIPTOR_HEAP_DESC description;
		description.Type = type;
		description.NumDescriptors = num_descriptors;
		description.Flags = flags;
		description.NodeMask = node_mask;

		winrt::com_ptr<ID3D12DescriptorHeap> descriptor_heap;
		winrt::check_hresult(
			device.CreateDescriptorHeap(&description, __uuidof(descriptor_heap), descriptor_heap.put_void()));
		
		return descriptor_heap;
	}
	winrt::com_ptr<ID3D12Fence> create_fence(ID3D12Device& device, UINT64 const initial_value, D3D12_FENCE_FLAGS const flags)
	{
		winrt::com_ptr<ID3D12Fence> fence;
		winrt::check_hresult(
			device.CreateFence(initial_value, flags, __uuidof(fence), fence.put_void()));

		return fence;
	}
}
