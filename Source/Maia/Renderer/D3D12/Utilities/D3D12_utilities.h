#include <stdexcept>

#include <winrt/base.h>

#include <d3d12.h>
#include <dxgi1_6.h>

namespace Maia::Renderer::D3D12
{
	winrt::com_ptr<IDXGIFactory6> create_factory(UINT flags);
	winrt::com_ptr<IDXGIAdapter4> select_adapter(IDXGIFactory6& factory, bool select_WARP_adapter);
	winrt::com_ptr<ID3D12Device4> create_device(IDXGIAdapter& adapter, D3D_FEATURE_LEVEL minimum_feature_level);
	winrt::com_ptr<ID3D12CommandAllocator> create_commandA_allocator(ID3D12Device& device, D3D12_COMMAND_LIST_TYPE type);
	winrt::com_ptr<ID3D12GraphicsCommandList> create_opened_graphics_command_list(ID3D12Device& device, UINT node_mask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator& command_allocator, ID3D12PipelineState* initial_state = nullptr);
	winrt::com_ptr<ID3D12GraphicsCommandList> create_closed_graphics_command_list(ID3D12Device& device, UINT node_mask, D3D12_COMMAND_LIST_TYPE type, ID3D12CommandAllocator& command_allocator, ID3D12PipelineState* initial_state = nullptr);
}