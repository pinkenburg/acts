///////////////////////////////////////////////////////////////////
// IMagneticFieldSvc.h, ACTS project
///////////////////////////////////////////////////////////////////

#ifndef ACTS_MAGNETICFIELDINTERFACES_IMAGFIELDSVC_H
#define ACTS_MAGNETICFIELDINTERFACES_IMAGFIELDSVC_H 1

#ifdef ACTS_MAGNETICFIELDINTERFACE_PLUGIN
#include ACTS_MAGNETICFIELDINTERFACE_PLUGIN
#else 

// Framework includes
#include "GaudiKernel/IInterface.h"

/** Declaration of the interface ID ( interface id, major version, minor version) */
static const InterfaceID IID_IMagneticFieldSvc("IMagneticFieldSvc", 1, 0);

namespace Acts {

/** @ class IMagneticFieldSvc

    @ author Andreas.Salzburger -at- cern.ch
 */
    class IMagneticFieldSvc: virtual public IInterface {

    ///////////////////////////////////////////////////////////////////
    // Public methods:
    ///////////////////////////////////////////////////////////////////
    public:
        /** constructor */
        IMagneticFieldSvc();

        /** Retrieve interface ID */
        static const InterfaceID& interfaceID() { return IID_IMagneticFieldSvc;}

        /** get B field value at given position */
        /** xyz[3] is in mm, bxyz[3] is in kT */
        /** if deriv[9] is given, field derivatives are returned in kT/mm */
        virtual void getField(const double *xyz, double *bxyz, double *deriv = 0) = 0;

        /** get B field value on the z-r plane at given position */
        /** works only inside the solenoid; otherwise calls getField() above */
        /** xyz[3] is in mm, bxyz[3] is in kT */
        /** if deriv[9] is given, field derivatives are returned in kT/mm */
        virtual void getFieldZR(const double *xyz, double *bxyz, double *deriv = 0) = 0;

    };
}

#endif // ACTS_MAGNETICFIELDINTERFACE_PLUGIN

#endif //> ! ACTS_MAGNETICFIELDINTERFACES_IMAGFIELDSVC_H