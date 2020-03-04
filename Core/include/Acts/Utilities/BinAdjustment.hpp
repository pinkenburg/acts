// This file is part of the Acts project.
//
// Copyright (C) 2019 CERN for the benefit of the Acts project
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

///////////////////////////////////////////////////////////////////
// BinAdjustment.hpp, Acts project
///////////////////////////////////////////////////////////////////

#pragma once

#include <stdexcept>
#include "Acts/Geometry/CuboidVolumeBounds.hpp"
#include "Acts/Geometry/CylinderVolumeBounds.hpp"
#include "Acts/Geometry/Volume.hpp"
#include "Acts/Surfaces/CylinderBounds.hpp"
#include "Acts/Surfaces/RadialBounds.hpp"
#include "Acts/Surfaces/Surface.hpp"
#include "Acts/Utilities/BinUtility.hpp"

namespace Acts {

/// @brief adjust the BinUtility bu to the dimensions of cylinder volume bounds
///
/// @param bu BinUtility at source
/// @param cBounds the Cylinder volume bounds to adjust to
///
/// @return new updated BinUtiltiy
BinUtility adjustBinUtility(const BinUtility& bu,
                            const CylinderVolumeBounds& cBounds) {
  // Default constructor
  BinUtility uBinUtil;
  // The parameters from the cylinder bounds
  double minR = cBounds.innerRadius();
  double maxR = cBounds.outerRadius();
  double minPhi = -cBounds.halfPhiSector();
  double maxPhi = cBounds.halfPhiSector();
  double minZ = -cBounds.halflengthZ();
  double maxZ = cBounds.halflengthZ();
  // Retrieve the binning data
  const std::vector<BinningData>& bData = bu.binningData();
  // Loop over the binning data and adjust the dimensions
  for (auto& bd : bData) {
    // The binning value
    BinningValue bval = bd.binvalue;
    // Throw exceptions is stuff doesn't make sense:
    // - not the right binning value
    // - not equidistant
    if (bd.type == arbitrary) {
      throw std::invalid_argument("Arbirary binning can not be adjusted.");
    } else if (bval != binR and bval != binPhi and bval != binZ) {
      throw std::invalid_argument("Cylinder volume binning must be: phi, r, z");
    }
    float min, max = 0.;
    // Perform the value adjustment
    if (bval == binPhi) {
      min = minPhi;
      max = maxPhi;
    } else if (bval == binR) {
      min = minR;
      max = maxR;
    } else if (bval == binZ) {
      min = minZ;
      max = maxZ;
    }
    // Create the updated BinningData
    BinningData uBinData(bd.option, bval, bd.bins(), min, max);
    uBinUtil += BinUtility(uBinData);
  }
  return uBinUtil;
}

/// @brief adjust the BinUtility bu to the dimensions of cuboid volume bounds
///
/// @param bu BinUtility at source
/// @param cBounds the Cuboid volume bounds to adjust to
///
/// @return new updated BinUtiltiy
BinUtility adjustBinUtility(const BinUtility& bu,
                            const CuboidVolumeBounds& cBounds) {
  // Default constructor
  BinUtility uBinUtil;
  // The parameters from the cylinder bounds
  double minX = -cBounds.halflengthX();
  double maxX = cBounds.halflengthX();
  double minY = -cBounds.halflengthY();
  double maxY = cBounds.halflengthY();
  double minZ = -cBounds.halflengthZ();
  double maxZ = cBounds.halflengthZ();
  // Retrieve the binning data
  const std::vector<BinningData>& bData = bu.binningData();
  // Loop over the binning data and adjust the dimensions
  for (auto& bd : bData) {
    // The binning value
    BinningValue bval = bd.binvalue;
    // Throw exceptions is stuff doesn't make sense:
    // - not the right binning value
    // - not equidistant
    if (bd.type == arbitrary) {
      throw std::invalid_argument("Arbirary binning can not be adjusted.");
    } else if (bval != binX and bval != binY and bval != binZ) {
      throw std::invalid_argument("Cylinder volume binning must be: x, y, z");
    }
    float min, max = 0.;
    // Perform the value adjustment
    if (bval == binX) {
      min = minX;
      max = maxX;
    } else if (bval == binY) {
      min = minY;
      max = maxY;
    } else if (bval == binZ) {
      min = minZ;
      max = maxZ;
    }
    // Create the updated BinningData
    BinningData uBinData(bd.option, bval, bd.bins(), min, max);
    uBinUtil += BinUtility(uBinData);
  }
  return uBinUtil;
}

/// @brief adjust the BinUtility bu to the dimensions of radial bounds
///
/// @param bu BinUtility at source
/// @param rBounds the Radial bounds to adjust to
///
/// @return new updated BinUtiltiy
BinUtility adjustBinUtility(const BinUtility& bu, const RadialBounds& rBounds) {
  // Default constructor
  BinUtility uBinUtil;
  // The parameters from the cylinder bounds
  double minR = rBounds.rMin();
  double maxR = rBounds.rMax();
  double minPhi = rBounds.averagePhi() - rBounds.halfPhiSector();
  double maxPhi = rBounds.averagePhi() + rBounds.halfPhiSector();
  // Retrieve the binning data
  const std::vector<BinningData>& bData = bu.binningData();
  // Loop over the binning data and adjust the dimensions
  for (auto& bd : bData) {
    // The binning value
    BinningValue bval = bd.binvalue;
    // Throw exceptions is stuff doesn't make sense:
    // - not the right binning value
    // - not equidistant
    if (bd.type == arbitrary) {
      throw std::invalid_argument("Arbirary binning can not be adjusted.");
    } else if (bval != binR and bval != binPhi) {
      throw std::invalid_argument("Disc binning must be: phi, r");
    }
    float min, max = 0.;
    // Perform the value adjustment
    if (bval == binPhi) {
      min = minPhi;
      max = maxPhi;
    } else {
      min = minR;
      max = maxR;
    }
    // Create the updated BinningData
    BinningData uBinData(bd.option, bval, bd.bins(), min, max);
    uBinUtil += BinUtility(uBinData);
  }
  return uBinUtil;
}

/// @brief adjust the BinUtility bu to the dimensions of cylinder bounds
///
/// @param bu BinUtility at source
/// @param cBounds the Cylinder bounds to adjust to
///
/// @return new updated BinUtiltiy
BinUtility adjustBinUtility(const BinUtility& bu,
                            const CylinderBounds& cBounds) {
  // Default constructor
  BinUtility uBinUtil;
  // The parameters from the cylinder bounds
  double cR = cBounds.r();
  double cHz = cBounds.halflengthZ();
  double minPhi = cBounds.averagePhi() - cBounds.halfPhiSector();
  double maxPhi = cBounds.averagePhi() + cBounds.halfPhiSector();
  // Retrieve the binning data
  const std::vector<BinningData>& bData = bu.binningData();
  // Loop over the binning data and adjust the dimensions
  for (auto& bd : bData) {
    // The binning value
    BinningValue bval = bd.binvalue;
    // Throw exceptions if stuff doesn't make sense:
    // - not the right binning value
    // - not equidistant
    if (bd.type == arbitrary) {
      throw std::invalid_argument("Arbitrary binning can not be adjusted.");
    } else if (bval != binRPhi and bval != binPhi and bval != binZ) {
      throw std::invalid_argument("Cylinder binning must be: rphi, phi, z");
    }
    float min, max = 0.;
    // Perform the value adjustment
    if (bval == binPhi) {
      min = minPhi;
      max = maxPhi;
    } else if (bval == binRPhi) {
      min = cR * minPhi;
      max = cR * maxPhi;
    } else {
      min = -cHz;
      max = cHz;
    }
    // Create the updated BinningData
    BinningData uBinData(bd.option, bval, bd.bins(), min, max);
    uBinUtil += BinUtility(uBinData);
  }
  return uBinUtil;
}

/// @brief adjust the BinUtility bu to a surface
///
/// @param bu BinUtility at source
/// @param Surface to which the adjustment is being done
///
/// @return new updated BinUtiltiy
BinUtility adjustBinUtility(const BinUtility& bu, const Surface& surface) {
  // The surface type is a cylinder
  if (surface.type() == Surface::Cylinder) {
    // Cast to Cylinder bounds and return
    auto cBounds = dynamic_cast<const CylinderBounds*>(&(surface.bounds()));
    // Return specific adjustment
    return adjustBinUtility(bu, *cBounds);

  } else if (surface.type() == Surface::Disc) {
    // Cast to Cylinder bounds and return
    auto rBounds = dynamic_cast<const RadialBounds*>(&(surface.bounds()));
    // Return specific adjustment
    return adjustBinUtility(bu, *rBounds);
  }

  throw std::invalid_argument(
      "Bin adjustment not implemented for this surface yet!");

  return BinUtility();
}

/// @brief adjust the BinUtility bu to a volume
///
/// @param bu BinUtility at source
/// @param Volume to which the adjustment is being done
///
/// @return new updated BinUtiltiy
BinUtility adjustBinUtility(const BinUtility& bu, const Volume& volume) {
  auto cyBounds =
      dynamic_cast<const CylinderVolumeBounds*>(&(volume.volumeBounds()));
  auto cuBounds =
      dynamic_cast<const CuboidVolumeBounds*>(&(volume.volumeBounds()));

  if (cyBounds != nullptr) {
    // Cylinder bounds
    return adjustBinUtility(bu, *cyBounds);

  } else if (cuBounds != nullptr) {
    // Cylinder bounds
    return adjustBinUtility(bu, *cuBounds);
  }

  throw std::invalid_argument(
      "Bin adjustment not implemented for this volume yet!");

  return BinUtility();
}

}  // namespace Acts
