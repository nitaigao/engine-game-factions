#include "precompiled.h"

#include "InputFacade.h"

#include "System/SystemType.hpp"

using namespace luabind;

#include "System/AnyType.hpp"
#include "Service/IService.hpp"
using namespace Services;

namespace Script
{
  luabind::scope InputFacade::RegisterFunctions()
  {
    return (
      class_< InputFacade >( "InputFacade" )
        .def( "getTextForMessage", &InputFacade::GetTextForMessage )
        .def( "setMessageBinding", &InputFacade::SetMessageBinding )
        .def( "setDefaultMessageBinding", &InputFacade::SetDefaultMessageBinding )
      );
  }

  std::string InputFacade::GetTextForMessage( const System::MessageType& message )
  {
    IService* inputService = m_serviceManager->FindService( System::Types::INPUT );

    AnyType::AnyTypeMap parameters;
    parameters[ System::Attributes::Message ] = message;

    return inputService->ProcessMessage( System::Messages::Input::GetTextForMessage, parameters )[ "result" ].As< std::string >( );
  }


  void InputFacade::SetMessageBinding( const System::MessageType& message, const std::string& binding )
  {
    IService* inputService = m_serviceManager->FindService( System::Types::INPUT );

    AnyType::AnyTypeMap parameters;
    parameters[ System::Attributes::Message ] = message;
    parameters[ System::Parameters::Binding ] = binding;

    inputService->ProcessMessage( System::Messages::SetBindingForMessage, parameters );
  }

  void InputFacade::SetDefaultMessageBinding( const System::MessageType& message, const std::string& binding )
  {
    IService* inputService = m_serviceManager->FindService( System::Types::INPUT );

    AnyType::AnyTypeMap parameters;
    parameters[ System::Attributes::Message ] = message;
    parameters[ System::Parameters::Binding ] = binding;

    inputService->ProcessMessage( System::Messages::Input::SetDefaultBindingForMessage, parameters );
  }
}