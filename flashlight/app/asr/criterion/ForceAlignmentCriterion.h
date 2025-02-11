/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "flashlight/fl/flashlight.h"

#include "flashlight/app/asr/criterion/CriterionUtils.h"
#include "flashlight/app/asr/criterion/Defines.h"

using fl::lib::seq::CriterionScaleMode;

namespace fl {
namespace app {
namespace asr {

class ForceAlignmentCriterion : public fl::BinaryModule {
 public:
  explicit ForceAlignmentCriterion(
      int N,
      CriterionScaleMode scalemode = CriterionScaleMode::NONE);

  fl::Variable forward(const fl::Variable& input, const fl::Variable& target)
      override;

  af::array viterbiPath(const af::array& input, const af::array& target);

  std::string prettyString() const override;

 private:
  friend class AutoSegmentationCriterion;
  ForceAlignmentCriterion() = default;

  int N_;
  CriterionScaleMode scaleMode_;

  FL_SAVE_LOAD_WITH_BASE(
      fl::BinaryModule,
      fl::serializeAs<int64_t>(N_),
      scaleMode_)
};

typedef ForceAlignmentCriterion FACLoss;
} // namespace asr
} // namespace app
} // namespace fl

CEREAL_REGISTER_TYPE(fl::app::asr::ForceAlignmentCriterion)
