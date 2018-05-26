#include <gtest/gtest.h>

#include <D3D12/Utilities/DXUtilities.h>

using namespace Maia::Renderer;

namespace Maia::Renderer::D3D12::UnitTest
{
	class DXUtilitiesTest : public ::testing::Test
	{
	};

	TEST_F(DXUtilitiesTest, ShouldSucceed_WhenCreateFactory)
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
	TEST_P(SelectAdapterTest, ShouldSucceed_WhenSelectWarpAdapter)
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

	TEST_F(DXUtilitiesTest, ShouldSelectWarpAdapter_WhenSelectWarpAdapterIsTrue)
	{
		auto factory = D3D12::CreateFactory(0);
		auto adapter = D3D12::SelectAdapter(*factory.Get(), true);
		DXGI_ADAPTER_DESC1 description;
		adapter->GetDesc1(&description);

		EXPECT_TRUE(description.Flags & DXGI_ADAPTER_FLAG_SOFTWARE);
	}
	TEST_F(DXUtilitiesTest, ShouldSelectHardwareAdapter_WhenSelectWarpAdapterIsFalse)
	{
		auto factory = D3D12::CreateFactory(0);
		auto adapter = D3D12::SelectAdapter(*factory.Get(), false);
		DXGI_ADAPTER_DESC1 description;
		adapter->GetDesc1(&description);

		EXPECT_FALSE(description.Flags & DXGI_ADAPTER_FLAG_SOFTWARE);
	}

	TEST_F(DXUtilitiesTest, ShouldSucceed_WhenCreateDevice)
	{
		auto factory = D3D12::CreateFactory(0);
		auto adapter = D3D12::SelectAdapter(*factory.Get(), true);

		ASSERT_NO_FATAL_FAILURE(
			{
				auto device = D3D12::CreateDevice(*adapter.Get(), D3D_FEATURE_LEVEL_11_0);
				EXPECT_TRUE(device);
			}
		);
	}
}
