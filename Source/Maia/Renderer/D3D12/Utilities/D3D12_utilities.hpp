#ifndef MAIA_RENDERER_D3D12UTILITIES_H_INCLUDED
#define MAIA_RENDERER_D3D12UTILITIES_H_INCLUDED

#include <stdexcept>

#include <gsl/span>

#include <winrt/base.h>

#include <Eigen/Core>

#include <d3d12.h>
#include <dxgi1_6.h>

#include <Maia/Renderer/D3D12/Utilities/Mapped_memory.hpp>

namespace Maia::Renderer::D3D12
{
	[[nodiscard]] winrt::com_ptr<IDXGIFactory6> create_factory(UINT flags);
	[[nodiscard]] winrt::com_ptr<IDXGIAdapter4> select_adapter(IDXGIFactory6& factory, bool select_WARP_adapter);
	[[nodiscard]] winrt::com_ptr<ID3D12Device5> create_device(IDXGIAdapter& adapter, D3D_FEATURE_LEVEL minimum_feature_level);
	[[nodiscard]] winrt::com_ptr<ID3D12CommandQueue> create_command_queue(ID3D12Device& device, D3D12_COMMAND_LIST_TYPE type, INT priority, D3D12_COMMAND_QUEUE_FLAGS flags, UINT node_mask);
	[[nodiscard]] winrt::com_ptr<ID3D12CommandAllocator> create_command_allocator(ID3D12Device& device, D3D12_COMMAND_LIST_TYPE type);
	[[nodiscard]] std::vector<winrt::com_ptr<ID3D12CommandAllocator>> create_command_allocators(ID3D12Device& device, D3D12_COMMAND_LIST_TYPE type, std::size_t count);
	[[nodiscard]] winrt::com_ptr<ID3D12GraphicsCommandList> create_opened_graphics_command_list(ID3D12Device& device, UINT node_mask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator& command_allocator, ID3D12PipelineState* initial_state = nullptr);
	[[nodiscard]] winrt::com_ptr<ID3D12GraphicsCommandList> create_closed_graphics_command_list(ID3D12Device& device, UINT node_mask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator& command_allocator, ID3D12PipelineState* initial_state = nullptr);
	[[nodiscard]] winrt::com_ptr<ID3D12DescriptorHeap> create_descriptor_heap(ID3D12Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT num_descriptors, D3D12_DESCRIPTOR_HEAP_FLAGS flags, UINT node_mask);
	[[nodiscard]] winrt::com_ptr<ID3D12Fence> create_fence(ID3D12Device& device, UINT64 initial_value, D3D12_FENCE_FLAGS flags);

	[[nodiscard]] winrt::com_ptr<IDXGISwapChain4> create_swap_chain(IDXGIFactory6& factory, IUnknown& direct_command_queue, IUnknown& window, DXGI_FORMAT format, UINT buffer_count);
	[[nodiscard]] winrt::com_ptr<IDXGISwapChain4> create_swap_chain_and_rtvs(IDXGIFactory6& factory, IUnknown& direct_command_queue, IUnknown& window, UINT buffer_count, ID3D12Device& device, D3D12_CPU_DESCRIPTOR_HANDLE destination_descriptor);

	void resize_swap_chain_buffers_and_recreate_rtvs(IDXGISwapChain4& swap_chain, gsl::span<UINT> create_node_masks, gsl::span<IUnknown*> command_queues, Eigen::Vector2i dimensions, ID3D12Device& device, D3D12_CPU_DESCRIPTOR_HANDLE start_destination_descriptor);

	[[nodiscard]] winrt::com_ptr<ID3D12RootSignature> create_root_signature(
		ID3D12Device5& device,
		gsl::span<D3D12_ROOT_PARAMETER1 const> root_parameters,
		gsl::span<D3D12_STATIC_SAMPLER_DESC const> static_samplers,
		UINT node_mask,
		D3D12_ROOT_SIGNATURE_FLAGS flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT
	);

	[[nodiscard]] winrt::com_ptr<ID3D12Heap> create_upload_heap(ID3D12Device& device, UINT64 size_in_bytes);
	[[nodiscard]] winrt::com_ptr<ID3D12Heap> create_buffer_heap(ID3D12Device& device, UINT64 size_in_bytes);
	[[nodiscard]] winrt::com_ptr<ID3D12Resource> create_buffer(ID3D12Device& device, ID3D12Heap& heap, UINT64 heap_offset, UINT64 width, D3D12_RESOURCE_STATES initial_state = D3D12_RESOURCE_STATE_COPY_DEST);

	template <class T>
	void upload_buffer_data(
		ID3D12GraphicsCommandList& command_list,
		ID3D12Resource& destination_buffer, UINT64 destination_buffer_offset,
		ID3D12Resource& upload_buffer, UINT64 upload_buffer_offset,
		gsl::span<T> data
	)
	{
		Maia::Renderer::D3D12::Mapped_memory mapped_memory{ upload_buffer, 0, {} };
		mapped_memory.write(data.data(), data.size_bytes(), upload_buffer_offset);

		command_list.CopyBufferRegion(
			&destination_buffer,
			destination_buffer_offset,
			&upload_buffer,
			upload_buffer_offset,
			data.size_bytes()
		);
	}

	template <class T>
	void upload_buffer_data(
		Maia::Renderer::D3D12::Mapped_memory& mapped_memory,
		ID3D12GraphicsCommandList& command_list,
		ID3D12Resource& destination_buffer, UINT64 destination_buffer_offset,
		ID3D12Resource& upload_buffer, UINT64 upload_buffer_offset,
		gsl::span<T> data
	)
	{
		mapped_memory.write(data.data(), data.size_bytes(), upload_buffer_offset);

		command_list.CopyBufferRegion(
			&destination_buffer,
			destination_buffer_offset,
			&upload_buffer,
			upload_buffer_offset,
			data.size_bytes()
		);
	}

	void wait(
		ID3D12CommandQueue& command_queue,
		ID3D12Fence& fence,
		HANDLE fence_event,
		UINT64 event_value_to_wait,
		DWORD maximum_time_to_wait = INFINITE
	);
	void signal_and_wait(
		ID3D12CommandQueue& command_queue,
		ID3D12Fence& fence,
		HANDLE fence_event,
		UINT64 event_value_to_signal_and_wait,
		DWORD maximum_time_to_wait = INFINITE
	);
}

#endif
