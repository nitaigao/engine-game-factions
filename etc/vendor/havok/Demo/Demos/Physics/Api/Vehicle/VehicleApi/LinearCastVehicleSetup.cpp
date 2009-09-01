/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2009 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

#include <Demos/demos.h>
#include <Demos/Physics/Api/Vehicle/VehicleApi/LinearCastVehicleSetup.h>

void LinearCastVehicleSetup::buildVehicle( const hkpWorld* world, hkpVehicleInstance& vehicle )
{
	//
	// All memory allocations are made here.
	//

	vehicle.m_data				= new hkpVehicleData;
	vehicle.m_driverInput		= new hkpVehicleDefaultAnalogDriverInput;
	vehicle.m_steering			= new hkpVehicleDefaultSteering;
	vehicle.m_engine			= new hkpVehicleDefaultEngine;
	vehicle.m_transmission		= new hkpVehicleDefaultTransmission;
	vehicle.m_brake				= new hkpVehicleDefaultBrake;
	vehicle.m_suspension		= new hkpVehicleDefaultSuspension;
	vehicle.m_aerodynamics		= new hkpVehicleDefaultAerodynamics;
	vehicle.m_velocityDamper	= new hkpVehicleDefaultVelocityDamper;

	vehicle.m_wheelCollide		= new hkpVehicleLinearCastWheelCollide;

	setupVehicleData( world, *vehicle.m_data );

	// initialise the tyremarks controller with 128 tyremark points.
	vehicle.m_tyreMarks		= new hkpTyremarksInfo( *vehicle.m_data, 128 );

	setupComponent( *vehicle.m_data, *static_cast< hkpVehicleDefaultAnalogDriverInput* >(vehicle.m_driverInput) );
	setupComponent( *vehicle.m_data, *static_cast< hkpVehicleDefaultSteering*>(vehicle.m_steering));
	setupComponent( *vehicle.m_data, *static_cast< hkpVehicleDefaultEngine*>(vehicle.m_engine) );
	setupComponent( *vehicle.m_data, *static_cast< hkpVehicleDefaultTransmission*>(vehicle.m_transmission) );
	setupComponent( *vehicle.m_data, *static_cast< hkpVehicleDefaultBrake*>(vehicle.m_brake) );
	setupComponent( *vehicle.m_data, *static_cast< hkpVehicleDefaultSuspension*>(vehicle.m_suspension) );
	setupComponent( *vehicle.m_data, *static_cast< hkpVehicleDefaultAerodynamics*>(vehicle.m_aerodynamics) );
	setupComponent( *vehicle.m_data, *static_cast< hkpVehicleDefaultVelocityDamper*>(vehicle.m_velocityDamper) );


	// The wheel collide component performs collision detection. To do this, it needs to create an 
	// aabbPhantom from the vehicle information that has been set here already.
	setupWheelCollide( world, vehicle, *static_cast< hkpVehicleLinearCastWheelCollide*>(vehicle.m_wheelCollide) );

	setupTyremarks( *vehicle.m_data, *static_cast< hkpTyremarksInfo*>(vehicle.m_tyreMarks) );

	//
	// Check that all components are present.
	//
	HK_ASSERT(0x0, vehicle.m_data );
	HK_ASSERT(0x7708674a,  vehicle.m_driverInput );
	HK_ASSERT(0x5a324a2d,  vehicle.m_steering );
	HK_ASSERT(0x7bcb2aff,  vehicle.m_engine );
	HK_ASSERT(0x29bddb50,  vehicle.m_transmission );
	HK_ASSERT(0x2b0323a2,  vehicle.m_brake );
	HK_ASSERT(0x7a7ade23,  vehicle.m_suspension );
	HK_ASSERT(0x6ec4d0ed,  vehicle.m_aerodynamics );
	HK_ASSERT(0x67161206,  vehicle.m_wheelCollide );
	HK_ASSERT(0x295015f1,  vehicle.m_tyreMarks );

	//
	// Set up any variables that store cached data.
	//


	// Give driver input default values so that the vehicle (if this input is a default for non
	// player cars) will drive, even if it is in circles!

	// Accelerate.
	vehicle.m_deviceStatus = new hkpVehicleDriverInputAnalogStatus;
	hkpVehicleDriverInputAnalogStatus* deviceStatus = (hkpVehicleDriverInputAnalogStatus*)vehicle.m_deviceStatus;
	deviceStatus->m_positionY = -0.4f;

	// Turn.
	deviceStatus->m_positionX = 0.3f;

	// Defaults
	deviceStatus->m_handbrakeButtonPressed = false;
	deviceStatus->m_reverseButtonPressed = false;


	//
	// Don't forget to call init! (This function is necessary to set up derived data)
	//
	vehicle.init();
}

void LinearCastVehicleSetup::setupWheelCollide( const hkpWorld* world, const hkpVehicleInstance& vehicle, hkpVehicleLinearCastWheelCollide& wheelCollide )
{
	// Set the wheels to have the same collision filter info as the chassis.
	wheelCollide.m_wheelCollisionFilterInfo = vehicle.getChassis()->getCollisionFilterInfo();
}

/*
* Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20090704)
* 
* Confidential Information of Havok.  (C) Copyright 1999-2009
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
* 
* Use of this software for evaluation purposes is subject to and indicates
* acceptance of the End User licence Agreement for this product. A copy of
* the license is included with this software and is also available at www.havok.com/tryhavok.
* 
*/
