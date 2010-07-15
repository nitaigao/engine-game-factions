#include "precompiled.h"

#include "UXSystemScene.h"

using namespace Ogre;
using namespace MyGUI;

#include "Service/IService.hpp"
using namespace Services;

#include "LuaState.h"
#include "SystemFacade.h"
#include "InputFacade.h"
#include "InstrumentationFacade.h"
#include "NetworkFacade.h"
#include "ScriptConfiguration.h"
using namespace Script;

using namespace luabind;

#include "Events/Event.h"
#include "Events/EventType.hpp"
#include "Events/EventData.hpp"
#include "Events/EventListener.h"
#include "Events/InputEventData.hpp"
using namespace Events;

#include "UXSystemComponent.h"

namespace UX
{
  UXSystemScene::~UXSystemScene()
  {
    delete m_masterState;
    delete m_componentFactory;

    if (m_scriptConfiguration != 0)
    {
      delete m_scriptConfiguration;
      m_scriptConfiguration = 0;
    }
  }

  void UXSystemScene::Initialize()
  {
    m_masterState->Initialize();

    AnyType::AnyTypeMap results = m_serviceManager->MessageAll(System::Messages::RegisterScriptFunctions, AnyType::AnyTypeMap());

    for(AnyType::AnyTypeMap::iterator i = results.begin(); i != results.end(); ++i)
    {
      m_masterState->RegisterTypes((*i).second.As<scope>());
    }

    m_masterState->RegisterTypes(SystemFacade::RegisterFunctions());
    m_masterState->RegisterTypes(InputFacade::RegisterFunctions());
    m_masterState->RegisterTypes(InstrumentationFacade::RegisterFunctions());
    m_masterState->RegisterTypes(NetworkFacade::RegisterFunctions());

    m_scriptConfiguration = new ScriptConfiguration(m_configuration);

    if (typeid(*m_masterState) == typeid(LuaState))
    {
      static_cast<LuaState*>(m_masterState)->SetGlobal("ux", this);
      static_cast<LuaState*>(m_masterState)->SetGlobal("Configuration", static_cast<ScriptConfiguration*>(m_scriptConfiguration));
    }

    m_masterState->LoadScript("/data/interface/interface.lua");
    m_masterState->Execute();
  }

  void UXSystemScene::Update(float deltaMilliseconds)
  {
    for (IUXSystemComponent::UXSystemComponentList::iterator i = m_components.begin(); i != m_components.end(); ++i)
    {
      (*i)->Update(deltaMilliseconds);
    }
  }

  void UXSystemScene::Destroy()
  {
    m_gui->ClearScene();

    for (IUXSystemComponent::UXSystemComponentList::iterator i = m_components.begin(); i != m_components.end(); ++i)
    {
      (*i)->Destroy();
      delete (*i);
    }

    m_masterState->Destroy();
  }

  void UXSystemScene::LoadComponent(const std::string componentName)
  {
    IUXSystemComponent* component = m_componentFactory->CreateComponent(componentName);
    component->Initialize();

    m_components.push_back(component);

    m_gui->WindowResized();
  }

  void UXSystemScene::ChangeResolution(int width, int height, bool isFullScreen)
  {
    IService* renderService = m_serviceManager->FindService(System::Types::RENDER);

    AnyType::AnyTypeMap parameters;
    parameters[ System::Parameters::Graphics::Width ] = width;
    parameters[ System::Parameters::Graphics::Height ] = height;
    parameters[ System::Parameters::Graphics::FullScreen ] = isFullScreen;

    renderService->ProcessMessage(System::Messages::Graphics::ChangeResolution, parameters);

    m_gui->WindowResized();
  }

  void UXSystemScene::SetInputAllowed(bool inputAllowed)
  {
    IService* inputService = m_serviceManager->FindService(System::Types::INPUT);

    AnyType::AnyTypeMap parameters;
    parameters[ "inputAllowed" ] = inputAllowed;

    inputService->ProcessMessage("setInputAllowed", parameters);
  }

  void UXSystemScene::UnScriptWidget(MyGUI::Widget* widget, const std::string& eventName, luabind::object function)
  {
    void* userData = widget->getUserData();
    IGUI::WidgetUserData* widgetUserData = static_cast<IGUI::WidgetUserData*>(userData);

    if (0 != widgetUserData)
    {
      for (IGUI::WidgetUserData::iterator i = widgetUserData->begin(); i != widgetUserData->end(); ++i)
      {
        if ((*i).first == eventName)
        {
          if (eventName == "onRelease")
          {
            widget->eventMouseButtonReleased = 0;
          }

          if (eventName == "onClick")
          {
            widget->eventMouseButtonPressed = 0;
          }

          if (eventName == "onKeyUp")
          {
            widget->eventKeyButtonReleased = 0;
          }

          if (eventName == "onListSelectAccept")
          {
            static_cast<MultiList*>(widget)->eventListSelectAccept = 0;
          }

          if(eventName == "onScrollChangePosition")
          {
            static_cast<VScroll*>(widget)->eventScrollChangePosition = 0;
          }

          if (eventName == "onWindowButtonPressed")
          {
            static_cast<Window*>(widget)->eventWindowButtonPressed = 0;
          }

          if (eventName == "onWindowChangeCoord")
          {
            static_cast<Window*>(widget)->eventWindowChangeCoord = 0;
          }

          widgetUserData->erase(i);

          return;
        }
      }
    }
  }

  void UXSystemScene::ScriptWidget(MyGUI::Widget* widget, const std::string eventName, luabind::object function)
  {
    void* userData = widget->getUserData();

    IGUI::WidgetUserData* widgetUserData = static_cast<IGUI::WidgetUserData*>(userData);

    if (widgetUserData == 0)
    {
      widgetUserData = new IGUI::WidgetUserData();
    }

    object* handlerFunctionPtr = new object(function);
    widgetUserData->insert(std::make_pair(eventName, handlerFunctionPtr));

    widget->setUserData(static_cast<void*>(widgetUserData));

    if (eventName == "onRelease")
    {
      widget->eventMouseButtonReleased = newDelegate(&UXSystemScene::OnMouseReleased);
    }

    if (eventName == "onClick")
    {
      widget->eventMouseButtonPressed = newDelegate(&UXSystemScene::OnMousePressed);
    }

    if (eventName == "onKeyUp")
    {
      widget->eventKeyButtonReleased = newDelegate(&UXSystemScene::OnKeyUp);
    }

    if (eventName == "onListSelectAccept")
    {
      static_cast<MultiList*>(widget)->eventListSelectAccept = newDelegate(&UXSystemScene::OnListSelectAccept);
    }

    if(eventName == "onScrollChangePosition")
    {
      static_cast<VScroll*>(widget)->eventScrollChangePosition = newDelegate(&UXSystemScene::OnEventScrollChangePosition);
    }

    if (eventName == "onWindowButtonPressed")
    {
      static_cast<Window*>(widget)->eventWindowButtonPressed = newDelegate(&UXSystemScene::OnWindowButtonPressed);
    }

    if (eventName == "onWindowChangeCoord")
    {
      static_cast<Window*>(widget)->eventWindowChangeCoord = newDelegate(&UXSystemScene::OnWindowChangeCoord);
    }
  }

  void UXSystemScene::OnMouseReleased(MyGUI::WidgetPtr widget, int left, int top, MyGUI::MouseButton id)
  {
    void* userData = widget->getUserData();
    IGUI::WidgetUserData* widgetUserData = static_cast<IGUI::WidgetUserData*>(userData);

    for (IGUI::WidgetUserData::iterator i = widgetUserData->begin(); i != widgetUserData->end(); ++i)
    {
      if ((*i).first == "onRelease")
      {
        object eventHandler = *(*i).second;

        try
        {
          eventHandler(static_cast<int>(id.value), left, top);
        }
        catch(error& e)
        {
          object error_msg(from_stack(e.state() , -1));
          std::stringstream logMessage;
          logMessage <<error_msg;
          Warn(logMessage.str());
        }
      }
    }
  }

  void UXSystemScene::OnMousePressed(MyGUI::WidgetPtr widget, int left, int top, MyGUI::MouseButton id)
  {
    void* userData = widget->getUserData();
    IGUI::WidgetUserData* widgetUserData = static_cast<IGUI::WidgetUserData*>(userData);

    for (IGUI::WidgetUserData::iterator i = widgetUserData->begin(); i != widgetUserData->end(); ++i)
    {
      if ((*i).first == "onClick")
      {
        object eventHandler = *(*i).second;

        try
        {
          eventHandler(static_cast<int>(id.value), left, top);
        }
        catch(error& e)
        {
          object error_msg(from_stack(e.state() , -1));
          std::stringstream logMessage;
          logMessage <<error_msg;
          Warn(logMessage.str());
        }
      }
    }
  }

  void UXSystemScene::OnKeyUp(MyGUI::WidgetPtr widget, MyGUI::KeyCode key)
  {
    void* userData = widget->getUserData();
    IGUI::WidgetUserData* widgetUserData = static_cast<IGUI::WidgetUserData*>(userData);

    for (IGUI::WidgetUserData::iterator i = widgetUserData->begin(); i != widgetUserData->end(); ++i)
    {
      if ((*i).first == "onKeyUp")
      {
        Char keyCode = InputManager::getInstancePtr()->getKeyChar(key, 0);
        char* keyText = (char*) &keyCode;

        object eventHandler = *(*i).second;

        try
        {
          eventHandler(static_cast<int>(key.value), std::string(keyText));
        }
        catch(error& e)
        {
          object error_msg(from_stack(e.state() , -1));
          std::stringstream logMessage;
          logMessage <<error_msg;
          Warn(logMessage.str());
        }
      }
    }
  }

  void UXSystemScene::OnListSelectAccept(MultiListPtr widget, size_t index)
  {
    void* userData = widget->getUserData();
    IGUI::WidgetUserData* widgetUserData = static_cast<IGUI::WidgetUserData*>(userData);

    for (IGUI::WidgetUserData::iterator i = widgetUserData->begin(); i != widgetUserData->end(); ++i)
    {
      if ((*i).first == "onListSelectAccept")
      {
        object eventHandler = *(*i).second;

        try
        {
          eventHandler(index);
        }
        catch(error& e)
        {
          object error_msg(from_stack(e.state() , -1));
          std::stringstream logMessage;
          logMessage <<error_msg;
          Warn(logMessage.str());
        }
      }
    }
  }

  void UXSystemScene::OnEventScrollChangePosition(MyGUI::VScrollPtr widget, size_t position)
  {
    void* userData = widget->getUserData();
    IGUI::WidgetUserData* widgetUserData = static_cast<IGUI::WidgetUserData*>(userData);

    for (IGUI::WidgetUserData::iterator i = widgetUserData->begin(); i != widgetUserData->end(); ++i)
    {
      if ((*i).first == "onScrollChangePosition")
      {
        object eventHandler = *(*i).second;

        try
        {
          eventHandler(static_cast<int>(position));
        }
        catch(error& e)
        {
          object error_msg(from_stack(e.state() , -1));
          std::stringstream logMessage;
          logMessage <<error_msg;
          Warn(logMessage.str());
        }
      }
    }
  }

  void UXSystemScene::OnWindowButtonPressed(MyGUI::WindowPtr widget, const std::string& name)
  {
    void* userData = widget->getUserData();
    IGUI::WidgetUserData* widgetUserData = static_cast<IGUI::WidgetUserData*>(userData);

    for (IGUI::WidgetUserData::iterator i = widgetUserData->begin(); i != widgetUserData->end(); ++i)
    {
      if ((*i).first == "onWindowButtonPressed")
      {
        object eventHandler = *(*i).second;

        try
        {
          eventHandler(name);
        }
        catch(error& e)
        {
          object error_msg(from_stack(e.state() , -1));
          std::stringstream logMessage;
          logMessage <<error_msg;
          Warn(logMessage.str());
        }
      }
    }
  }

  void UXSystemScene::OnWindowChangeCoord(MyGUI::WindowPtr widget)
  {
    void* userData = widget->getUserData();
    IGUI::WidgetUserData* widgetUserData = static_cast<IGUI::WidgetUserData*>(userData);

    for (IGUI::WidgetUserData::iterator i = widgetUserData->begin(); i != widgetUserData->end(); ++i)
    {
      if ((*i).first == "onWindowChangeCoord")
      {
        object eventHandler = *(*i).second;

        try
        {
          eventHandler();
        }
        catch(error& e)
        {
          object error_msg(from_stack(e.state() , -1));
          std::stringstream logMessage;
          logMessage <<error_msg;
          Warn(logMessage.str());
        }
      }
    }
  }

  std::vector<std::string> UXSystemScene::GetSupportedResolutions()
  {
    typedef std::vector<std::string> StringVector;

    IService* renderService = m_serviceManager->FindService(System::Types::RENDER);
    StringVector resolutions = renderService->ProcessMessage("getAvailableVideoModes", AnyType::AnyTypeMap())[ "availableVideoModes" ].As<StringVector>();

    std::multimap<int, std::string> resolutionWidths;

    for(StringVector::iterator i = resolutions.begin(); i != resolutions.end(); ++i)
    {
      std::string resolution = (*i);

      std::stringstream resolutionStream;
      resolutionStream <<resolution.substr(0, resolution.find(" x "));

      int resolutionWidth = 0;
      resolutionStream>> resolutionWidth;
      resolutionWidths.insert(std::make_pair(resolutionWidth, resolution));
    }

    resolutions.clear();

    for(std::multimap<int, std::string>::iterator i = resolutionWidths.begin(); i != resolutionWidths.end(); ++i)
    {
      resolutions.push_back((*i).second);
    }

    return resolutions;
  }

  void UXSystemScene::ShowScreen(const std::string& screenName)
  {
    UIEventData* eventData = new UIEventData(screenName);
    Event* event = new Event(EventTypes::UI_SHOW_PANE, eventData);
    m_eventManager->QueueEvent(event);
  }
}