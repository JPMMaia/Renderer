#include <stdexcept>

#include <winrt/base.h>

#include <d3d12.h>
#include <dxgi1_6.h>

namespace Maia::Renderer::D3D12
{
	[[nodiscard]] winrt::com_ptr<IDXGIFactory6> create_factory(UINT flags);
	[[nodiscard]] winrt::com_ptr<IDXGIAdapter4> select_adapter(IDXGIFactory6& factory, bool select_WARP_adapter);
	[[nodiscard]] winrt::com_ptr<ID3D12Device4> create_device(IDXGIAdapter& adapter, D3D_FEATURE_LEVEL minimum_feature_level);
	[[nodiscard]] winrt::com_ptr<ID3D12CommandQueue> create_command_queue(ID3D12Device& device, D3D12_COMMAND_LIST_TYPE type, INT priority, D3D12_COMMAND_QUEUE_FLAGS flags, UINT node_mask);
	[[nodiscard]] winrt::com_ptr<ID3D12CommandAllocator> create_command_allocator(ID3D12Device& device, D3D12_COMMAND_LIST_TYPE type);
	[[nodiscard]] winrt::com_ptr<ID3D12GraphicsCommandList> create_opened_graphics_command_list(ID3D12Device& device, UINT node_mask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator& command_allocator, ID3D12PipelineState* initial_state = nullptr);
	[[nodiscard]] winrt::com_ptr<ID3D12GraphicsCommandList> create_closed_graphics_command_list(ID3D12Device& device, UINT node_mask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator& command_allocator, ID3D12PipelineState* initial_state = nullptr);
	[[nodiscard]] winrt::com_ptr<ID3D12DescriptorHeap> create_descriptor_heap(ID3D12Device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT num_descriptors, D3D12_DESCRIPTOR_HEAP_FLAGS flags, UINT node_mask);
	[[nodiscard]] winrt::com_ptr<ID3D12Fence> create_fence(ID3D12Device& device, UINT64 initial_value, D3D12_FENCE_FLAGS flags);
}
