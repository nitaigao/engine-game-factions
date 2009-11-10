/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   InputEventData.hpp
*  @date   2009/07/16
*/
#pragma once
#ifndef INPUTEVENTDATA_HPP
#define INPUTEVENTDATA_HPP

namespace Events
{
	/*! 
	*  Contains Key information for use with Key Events
	*/
	class KeyEventData : public IEventData
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~KeyEventData( ) { };


		/*! Default Constructor
		*
		*  @param[in] const OIS::KeyCode & keyCode
		*  @param[in] const std::string keyText
		*  @return ()
		*/
		KeyEventData( int keyCode, const std::string keyText )
			: m_keyCode( keyCode )
			, m_keyText( keyText )
		{

		};


		/*! Returns the Key Code of the key pressed in the Event
		*
		*  @return (OIS::KeyCode)
		*/
		inline int GetKeyCode( ) { return m_keyCode; };


		/*! Returns the text of the key pressed in the Event
		*
		*  @return (std::string)
		*/
		inline std::string GetKeyText( ) { return m_keyText; };

	private:

		int m_keyCode;
		std::string m_keyText;

		KeyEventData( ) { };
		KeyEventData( const KeyEventData & copy ) { };
		KeyEventData & operator = ( const KeyEventData & copy ) { return *this; };

	};

	/*!
	Contains MouseState information for use with Mouse Events
	*/
	class MouseEventData : public IEventData
	{

	public:

		/*! Default Destructor
		*
		*  @return ()
		*/
		~MouseEventData( ) { };


		/*! Default Constructor
		*
		*  @param[in] const OIS::MouseState & mouseState
		*  @param[in] const OIS::MouseButtonID & mouseButtonId
		*  @return ()
		*/
		MouseEventData( int x, int y, int z, int mouseButtonId )
			: m_x( x )
			, m_y( y )
			, m_z( z )
			, m_mouseButtonId( mouseButtonId )
		{

		};


		/*! Returns the X Position of the Mouse
		 *
		 * @return ( int )
		 */
		inline int GetX( ) const { return m_x; };


		/*! Returns the Y Position of the Mouse
		*
		* @return ( int )
		*/
		inline int GetY( ) const { return m_y; };


		/*! Returns the Z Position of the Mouse
		*
		* @return ( int )
		*/
		inline int GetZ( ) const { return m_z; };


		/*! Returns the Mouse Button associated with the Event
		*
		*  @return (int)
		*/
		inline int GetMouseButtonId( ) const { return m_mouseButtonId; };

	private:

		int m_x;
		int m_y;
		int m_z;
		int m_mouseButtonId;

		MouseEventData( ) { };
		MouseEventData( const MouseEventData & copy ) { };
		MouseEventData & operator = ( const MouseEventData & copy ) { return *this; };

	};
};

#endif
