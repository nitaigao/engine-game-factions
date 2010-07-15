/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   IGUI.hpp
*  @date   2009/09/02
*/
#pragma once
#ifndef IGUI_HPP
#define IGUI_HPP

#include <string>
#include <map>
#include <luabind/luabind.hpp>

#include <MyGUI.h>

#include "Export.hpp"

namespace UX
{
  /*! 
   *  The interface to the GUI System
   */
  class GAMEAPI IGUI
  {

  public:

    typedef std::map<std::string, luabind::object*> WidgetUserData;

    /*! Default Destructor
     *
     *  @return ()
     */
    virtual ~IGUI() { };


    /*! Returns the ViewPort Width
     *
     * @return (int)
     */
    virtual int GetViewWidth() const = 0;


    /*! Returns the ViewPort Height
    *
    * @return (int)
    */
    virtual int GetViewHeight() const = 0;


    /*! Finds a widget within the GUI
     *
     * @param[in] const std::string & widgetName
     * @return (MyGUI::WidgetPtr)
     */
    virtual MyGUI::WidgetPtr FindWidget(const std::string& widgetName) const = 0;


    /*! Shows the mouse on the Screen
     *
     * @return (void)
     */
    virtual void ShowMouse() const = 0;


    /*! Hides the mouse on the Screen
    *
    * @return (void)
    */
    virtual void HideMouse() const = 0;


    /*! Instructs the GUI that the window has been resized
     *
     * @return (void)
     */
    virtual void WindowResized() const = 0;


    /*! Initializes the GUI
     *
     * @param[in] const std::string & skinPath
     * @return (void)
     */
    virtual void Initialize(const std::string& skinPath) = 0;


    /*! Destroys the GUI
     *
     * @return (void)
     */
    virtual void Destroy() = 0;


    /*! Informs the GUI that the mouse has been moved
     *
     * @param[in] int x
     * @param[in] int y
     * @param[in] int z
     * @return (void)
     */
    virtual void MouseMoved(int x, int y, int z) = 0;


    /*! Informs the GUI that a mouse button has been pressed
     *
     * @param[in] int x
     * @param[in] int y
     * @param[in] int mouseButtonID
     * @return (void)
     */
    virtual void MousePressed(int x, int y, int mouseButtonID) = 0;


    /*! Informs the GUI that a mouse button has been released
    *
    * @param[in] int x
    * @param[in] int y
    * @param[in] int mouseButtonID
    * @return (void)
    */
    virtual void MouseReleased(int x, int y, int mouseButtonID) = 0;



    /*! Informs the GUI that a key has been released
     *
     * @param[in] int keyCode
     * @return (void)
     */
    virtual void KeyReleased(int keyCode) = 0;


    /*! Informs the GUI that a key has been pressed
    *
    * @param[in] int keyCode
    * @return (void)
    */
    virtual void KeyPressed(int keyCode) = 0;


    /*! Loads a layout from the file system
     *
     * @param[in] const std::string & layoutPath
     * @return (void)
     */
    virtual void LoadLayout(const std::string& layoutPath) = 0;


    /*! Updates the GUI
     *
     * @param[in] float deltaMilliseconds
     * @return (void)
     */
    virtual void Update(float deltaMilliseconds) = 0;


    /*! Clears the Scene of All Widgets
     *
     * @return (void)
     */
    virtual void ClearScene() = 0;
    
  };
};

#endif