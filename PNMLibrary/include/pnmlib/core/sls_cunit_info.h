/*
 * Copyright (C) 2022 Samsung Electronics Co. LTD
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or
 * distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or
 * computer language in any form
 * by any means, electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung
 * Electronics.
 */

/** @file sls_cunit_info.h
    @brief Utilites for SLS compute unit information exctraction.
*/

#ifndef SLS_CUNIT_INFO_H
#define SLS_CUNIT_INFO_H

#include <cstddef>

/***** SLS APIs for customer *****/

/** @brief Enumeration of sls sysfs compute unit info */
enum class SlsComputeUnitInfo : size_t {
  State = 0,
  AcquisitionCount,
  FreeSize,
  RegionBaseSize,
  RegionBaseOffset,
  RegionInstSize,
  RegionInstOffset,
  RegionCfgrSize,
  RegionCfgrOffset,
  RegionTagsSize,
  RegionTagsOffset,
  RegionPsumSize,
  RegionPsumOffset,
  Max
};

constexpr auto cunit_info_to_index(SlsComputeUnitInfo info) {
  return static_cast<size_t>(info);
}

constexpr auto cunit_info_length = cunit_info_to_index(SlsComputeUnitInfo::Max);

#endif // SLS_CUNIT_INFO_H
