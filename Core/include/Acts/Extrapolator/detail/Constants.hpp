// This file is part of the Acts project.
//
// Copyright (C) 2018 Acts project team
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <cmath>
#include "Acts/Utilities/Units.hpp"

namespace Acts {

namespace constants {

  // @todo change to constexpr

  // See (1) table 32.1
  // K/A*Z = 0.5 * 30.7075MeV/(g/mm2) * Z/A * rho[g/mm3]
  const double ka_BetheBloch
      = 30.7075 * (units::_MeV * units::_mm * units::_mm);

  /// Ionisation potential
  /// Ionization - Bethe-Bloch
  /// See ATL-SOFT-PUB-2008-003 equation (4)
  /// 16 eV * Z**0.9
  const double eionisation = 16 * units::_eV;

  /// Plasma energy [ eV ]
  const double eplasma = 28.816 * units::_eV;

  /// Fine structure constexprant
  constexpr double alpha = 1. / 137.;

  /// Multiple scattering parameters for MIPS [ in MeV]
  const double main_RutherfordScott = 13.6 * units::_MeV;
  const double log_RutherfordScott  = 0.038;

  /// Multiple scattering parameters for electrons [ in MeV ]
  const double main_RossiGreisen = 17.5 * units::_MeV;
  const double log_RossiGreisen  = 0.125;

  /// Electron mass [ in MeV ]
  const double me = 0.51099891 * units::_MeV;

}  // end of namespace constants

}  // enf of namespace Acts