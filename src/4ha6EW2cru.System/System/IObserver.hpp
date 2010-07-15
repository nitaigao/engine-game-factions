/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IObserver.hpp
*  @date   2009/04/25
*/
#pragma once
#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <deque>
#include "AnyType.hpp"

#include "../System/SystemType.hpp"

#include "../Export.hpp"

class ISubject;

/*! 
 *  Observes a change from an ISubject
 */
class GAMEAPI IObserver
{

public:

	typedef std::multimap<System::MessageType, IObserver*> ObserverMap;
	typedef std::deque<IObserver*> ObserverList;

	/*! Messages the Observer to influence its internal state
	*
	*  @param[in] const std::string & message
	*  @return (AnyType)
	*/
	virtual AnyType Observe(const ISubject* subject, const System::MessageType& message, AnyType::AnyTypeMap parameters) = 0;

};

#endif
