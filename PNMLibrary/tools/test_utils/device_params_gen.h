#ifndef DEVICE_TEST_UTILS_H
#define DEVICE_TEST_UTILS_H

#include "secure/plain/device/trivial_cpu.h"
#include "secure/plain/device/untrusted_sls.h"

#include "pnmlib/secure/base_device.h"
#include "pnmlib/secure/untrusted_sls_params.h"

#include "pnmlib/common/views.h"

#include <linux/sls_resources.h>

#include <cstddef>
#include <cstdint>
#include <vector>

namespace sls::tests {

// These creepy classes are required only for tests.
// Maybe we should rewrite some tests to get rid of this classes

template <typename T> struct SimpleDeviceParamsGenerator {};

template <typename T>
struct SimpleDeviceParamsGenerator<secure::UntrustedDevice<T>> {
  static auto generate_params(pnm::common_view<const uint32_t> rows,
                              uint64_t sparse_feature_size, bool with_tag,
                              bool multiprocess = false) {
    const sls::secure::UntrustedDeviceParams device_params{
        .rows = rows,
        .sparse_feature_size = sparse_feature_size,
        .with_tag = with_tag,
        .preference = (multiprocess) ? SLS_ALLOC_REPLICATE_ALL
                                     : SLS_ALLOC_DISTRIBUTE_ALL};
    return sls::secure::DeviceArguments(device_params);
  }
};

template <typename T>
struct SimpleDeviceParamsGenerator<secure::TrivialCPU<T>> {
  static auto generate_params(pnm::common_view<const uint32_t> rows,
                              uint64_t sparse_feature_size, bool with_tag,
                              [[maybe_unused]] bool multiprocess = false) {
    return sls::secure::DeviceArguments(
        sls::secure::TrivialCPUArgs{rows, sparse_feature_size, with_tag});
  }
};

template <typename T> struct GroupedParameterGenerator {
public:
  static auto generate_params(pnm::common_view<const uint32_t> rows,
                              uint64_t sparse_feature_size, size_t nchildren,
                              bool with_tag) {
    std::vector<sls::secure::DeviceArguments> params;
    for (size_t i = 0; i < nchildren; ++i) {
      params.emplace_back(SimpleDeviceParamsGenerator<T>::generate_params(
          rows, sparse_feature_size, with_tag, true));
    }

    return params;
  }
};

} // namespace sls::tests

#endif // SLS_UTILS_H
