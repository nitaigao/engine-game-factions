/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   INetworkSystemComponent.hpp
*  @date   2009/07/06
*/
#pragma once
#ifndef INETWORKSYSTEMCOMPONENT_HPP
#define INETWORKSYSTEMCOMPONENT_HPP

#include "System/ISystemComponent.hpp"
#include "INetworkProvider.hpp"

namespace Network
{
	/*! 
	 *  A Network System Component
	 */
	class GAMEAPI INetworkSystemComponent : public ISystemComponent
	{

	public:

		/*! Default Destructor
		 *
		 *  @return ()
		 */
		virtual ~INetworkSystemComponent( ) { };


		/*! Adds a Network Provider to the Component
		 *
		 * @param[in] INetworkProvider * provider
		 * @return ( void )
		 */
		virtual void AddProvider( INetworkProvider* provider ) = 0;


		/*! Returns the Position of the parent Entity in the scene
		*
		* @return ( Maths::MathVector3& )
		*/
		virtual Maths::MathVector3 GetPosition( ) const = 0;

	};
};

#endif
