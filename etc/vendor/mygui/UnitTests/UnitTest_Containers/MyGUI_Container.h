/*!
	@file
	@author		Alexander Ptakhin
	@date		02/2009
	@module
*/
#ifndef __MYGUI_CONTAINER_H__
#define __MYGUI_CONTAINER_H__

#include "MyGUI_Prerequest.h"
#include "MyGUI_SizeDescription.h"
#include "MyGUI_Spacer.h"

namespace MyGUI
{
	/** Abstract container class
	*/
	class /*MYGUI_EXPORT*/ Container : public Widget
	{
	protected:
		Container( WidgetStyle _style, const IntCoord& _coord, Align _align, const WidgetSkinInfoPtr _info, WidgetPtr _parent, ICroppedRectangle * _croppedParent, IWidgetCreator * _creator, const std::string & _name );

		WidgetPtr baseCreateWidget( WidgetStyle _style, const std::string & _type, const std::string & _skin, const IntCoord& _coord, Align _align, const std::string & _layer, const std::string & _name );

		//virtual void

		virtual void add( WidgetPtr widget ) = 0;

		virtual void remove( WidgetPtr widget ) = 0;

		virtual void update() = 0;

		//! @copydoc Widget::setSize(const IntSize& _size)
		void setSize(const IntSize& _size);

		//! @copydoc setCoord(const IntCoord& _coord)
		void setCoord(const IntCoord& _coord);

	public:	
		
		struct BaseWidgetInfo
		{
			WidgetPtr widget;

			BaseWidgetInfo( WidgetPtr _widget ) : widget( _widget ){}
		};
	};
} // namespace MyGUI

#endif // __MYGUI_CONTAINER_H__
