// Copyright (C) 2020 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include <vector>

#include "low_precision_transformations/squeeze_transformation.hpp"
#include "common_test_utils/test_constants.hpp"

using namespace LayerTestsDefinitions;
using namespace ngraph::pass::low_precision;

namespace {
    const std::vector<InferenceEngine::Precision> precisions = {
        InferenceEngine::Precision::FP32,
    };


    const std::vector<LayerTransformation::Params> trasformationParamValues = {
        LayerTestsUtils::LayerTransformationParamsFactory::createParamsU8I8(),
        LayerTestsUtils::LayerTransformationParamsFactory::createParamsI8I8().setUpdatePrecisions(false),
        LayerTestsUtils::LayerTransformationParamsFactory::createParamsI8I8().setUpdatePrecisions(true),
    };

    const std::vector<LayerTestsDefinitions::SqueezeTransformationParam> params = {
        {
            { 256ul, ngraph::Shape { 1, 1, 1, 1 }, { 0.f }, { 255.f }, { -128.f }, { 127.f } },
            { 0.0, 3.0 },
            { 1, 3, 5, 1}
        },
        {
            { 256ul, ngraph::Shape { 1, 1, 1, 1 }, { 0.f }, { 255.f }, { -128.f }, { 127.f } },
            { 0.0, 1.0, 2.0 },
            { 1, 1, 1, 1 }
        },
        {
            { 256ul, ngraph::Shape { 1, 1, 1, 1 }, { 0.f }, { 255.f }, { -128.f }, { 127.f } },
            { 0.0, 3.0 },
            { 1, 64, 32, 1 }
        },
        {
            { 256ul, ngraph::Shape { 1, 1, 1, 1 }, { 0.f }, { 255.f }, { -128.f }, { 127.f } },
            { 0.0, 2.0, 3.0 },
            { 1, 32, 1, 1 }
        }
    };

    INSTANTIATE_TEST_CASE_P(smoke_LPT, SqueezeTransformation,
        ::testing::Combine(
            ::testing::ValuesIn(precisions),
            ::testing::Values(CommonTestUtils::DEVICE_GPU),
            ::testing::ValuesIn(trasformationParamValues),
            ::testing::ValuesIn(params)),
        SqueezeTransformation::getTestCaseName);
}  // namespace
