#include "precompiled.h"

#include "AnimationFacade.h"

using namespace luabind;

#include "Logging/Logger.h"
using namespace Logging;

namespace Script
{
  scope AnimationFacade::RegisterFunctions()
  {
    return
      class_< AnimationFacade >("AnimationFacade")
        .def(constructor< ISystemComponent* >())
        .def("startAnimation", &AnimationFacade::StartAnimation)
        .def("stopAnimation", &AnimationFacade::StopAnimation);
  }

  void AnimationFacade::StartAnimation(const std::string& animationName, bool loop)
  {
    AnyType::AnyTypeMap parameters;
    parameters[ System::Parameters::AnimationName ] = animationName;
    parameters[ System::Parameters::LoopAnimation ] = loop;

    m_component->PushMessage(System::Messages::StartAnimation, parameters);
  }

  void AnimationFacade::StopAnimation(const std::string& animationName)
  {
    AnyType::AnyTypeMap parameters;
    parameters[ System::Parameters::AnimationName ] = animationName;

    m_component->PushMessage(System::Messages::StopAnimation, parameters);
  }
}