#include <gtest/gtest.h>

#include <Maia/Renderer/D3D12/Utilities/D3D12_utilities.h>

using namespace Maia::Renderer;

namespace Maia::Renderer::D3D12::UnitTest
{
	class DXUtilitiesTest : public ::testing::Test
	{
	};

	TEST_F(DXUtilitiesTest, CreateFactory_ShouldSucceed)
	{
		ASSERT_NO_FATAL_FAILURE(
			{
				auto factory = D3D12::CreateFactory({});
				EXPECT_TRUE(factory);
			}
		);
	}

	class SelectAdapterTest : public DXUtilitiesTest, public ::testing::WithParamInterface<bool>
	{
	};
	TEST_P(SelectAdapterTest, SelectAdapter_ShouldSucceed_WhenSelectWarpAdapterIsTrue)
	{
		auto factory = D3D12::CreateFactory(0);
		const auto selectWarpAdapter = GetParam();

		ASSERT_NO_FATAL_FAILURE(
			{
				auto adapter = D3D12::SelectAdapter(*factory.Get(), selectWarpAdapter);
				EXPECT_TRUE(adapter);
			}
		);
	}
	INSTANTIATE_TEST_CASE_P(DXUtilitiesTest, SelectAdapterTest,
		::testing::Values(true, false)
	);

	TEST_F(DXUtilitiesTest, SelectAdapter_ShouldSelectWarpAdapter_WhenSelectWarpAdapterIsTrue)
	{
		auto factory = D3D12::CreateFactory(0);
		auto adapter = D3D12::SelectAdapter(*factory.Get(), true);
		DXGI_ADAPTER_DESC1 description;
		adapter->GetDesc1(&description);

		EXPECT_TRUE(description.Flags & DXGI_ADAPTER_FLAG_SOFTWARE);
	}
	TEST_F(DXUtilitiesTest, SelectAdapter_ShouldSelectHardwareAdapter_WhenSelectWarpAdapterIsFalse)
	{
		auto factory = D3D12::CreateFactory(0);
		auto adapter = D3D12::SelectAdapter(*factory.Get(), false);
		DXGI_ADAPTER_DESC1 description;
		adapter->GetDesc1(&description);

		EXPECT_FALSE(description.Flags & DXGI_ADAPTER_FLAG_SOFTWARE);
	}

	TEST_F(DXUtilitiesTest, CreateD3DDevice_ShouldSucceed)
	{
		auto factory = D3D12::CreateFactory(0);
		auto adapter = D3D12::SelectAdapter(*factory.Get(), true);

		ASSERT_NO_FATAL_FAILURE(
			{
				auto d3dDevice = D3D12::CreateD3DDevice(*adapter.Get(), D3D_FEATURE_LEVEL_11_0);
				EXPECT_TRUE(d3dDevice);
			}
		);
	}

	TEST_F(DXUtilitiesTest, CreateCommandAllocator_ShouldSucceed)
	{
		auto factory = D3D12::CreateFactory(0);
		auto adapter = D3D12::SelectAdapter(*factory.Get(), true);
		auto d3dDevice = D3D12::CreateD3DDevice(*adapter.Get(), D3D_FEATURE_LEVEL_11_0);

		ASSERT_NO_FATAL_FAILURE(
			{
				auto commandAllocator = D3D12::CreateCommandAllocator(*d3dDevice.Get(), D3D12_COMMAND_LIST_TYPE_DIRECT);
				EXPECT_TRUE(commandAllocator);
			}
		);
	}
	
	TEST_F(DXUtilitiesTest, CreateOpenedCommandList_ShouldSucceed)
	{
		auto factory = D3D12::CreateFactory(0);
		auto adapter = D3D12::SelectAdapter(*factory.Get(), true);
		auto d3dDevice = D3D12::CreateD3DDevice(*adapter.Get(), D3D_FEATURE_LEVEL_11_0);
		auto commandAllocator = D3D12::CreateCommandAllocator(*d3dDevice.Get(), D3D12_COMMAND_LIST_TYPE_DIRECT);

		ASSERT_NO_FATAL_FAILURE(
			{
				auto commandList = D3D12::CreateOpenedGraphicsCommandList(*d3dDevice.Get(), 0, D3D12_COMMAND_LIST_TYPE_DIRECT, *commandAllocator.Get(), nullptr);
				EXPECT_TRUE(commandList);
			}
		);
	}
	TEST_F(DXUtilitiesTest, CreateOpenedCommandList_ShouldCreateOpenedCommandList)
	{
		auto factory = D3D12::CreateFactory(0);
		auto adapter = D3D12::SelectAdapter(*factory.Get(), true);
		auto d3dDevice = D3D12::CreateD3DDevice(*adapter.Get(), D3D_FEATURE_LEVEL_11_0);
		auto commandAllocator = D3D12::CreateCommandAllocator(*d3dDevice.Get(), D3D12_COMMAND_LIST_TYPE_DIRECT);

		auto commandList = D3D12::CreateOpenedGraphicsCommandList(*d3dDevice.Get(), 0, D3D12_COMMAND_LIST_TYPE_DIRECT, *commandAllocator.Get(), nullptr);

		EXPECT_EQ(S_OK, commandList->Close());
	}

	TEST_F(DXUtilitiesTest, CreateClosedCommandList_ShouldSucceed)
	{
		auto factory = D3D12::CreateFactory(0);
		auto adapter = D3D12::SelectAdapter(*factory.Get(), true);
		auto d3dDevice = D3D12::CreateD3DDevice(*adapter.Get(), D3D_FEATURE_LEVEL_11_0);
		auto commandAllocator = D3D12::CreateCommandAllocator(*d3dDevice.Get(), D3D12_COMMAND_LIST_TYPE_DIRECT);

		ASSERT_NO_FATAL_FAILURE(
			{
				auto commandList = D3D12::CreateClosedGraphicsCommandList(*d3dDevice.Get(), 0, D3D12_COMMAND_LIST_TYPE_DIRECT, *commandAllocator.Get(), nullptr);
				EXPECT_TRUE(commandList);
			}
		);
	}
	TEST_F(DXUtilitiesTest, CreateClosedCommandList_ShouldCreateClosedCommandList)
	{
		auto factory = D3D12::CreateFactory(0);
		auto adapter = D3D12::SelectAdapter(*factory.Get(), true);
		auto d3dDevice = D3D12::CreateD3DDevice(*adapter.Get(), D3D_FEATURE_LEVEL_11_0);
		auto commandAllocator = D3D12::CreateCommandAllocator(*d3dDevice.Get(), D3D12_COMMAND_LIST_TYPE_DIRECT);

		auto commandList = D3D12::CreateClosedGraphicsCommandList(*d3dDevice.Get(), 0, D3D12_COMMAND_LIST_TYPE_DIRECT, *commandAllocator.Get(), nullptr);

		EXPECT_EQ(E_FAIL, commandList->Close());
	}
}
