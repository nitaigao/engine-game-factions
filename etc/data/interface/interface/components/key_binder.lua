----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

KeyBinder = { }
message = ''

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------
----------------------------------------------------------------
-- KeyBinder Functions
----------------------------------------------------------------

function KeyBinder.initialize( )

	script:registerEventHandler( 'UI_SHOW_PANE', KeyBinder.onEvent )
	
	local widget = ux:findWidget( 'key_binder' )
	widget:setVisible( false )
	
	ux:scriptWidget( widget, 'onKeyUp', KeyBinder.onKeyUp )
	ux:scriptWidget( widget, 'onClick', KeyBinder.onClick )
	
end

function KeyBinder.onEvent( eventName, var1, var2 )

	if ( eventName == 'UI_SHOW_PANE' ) then
	
		if ( var1:getParam1( ) == 'UI_KEYBINDER' )  then
		
			local widget = ux:findWidget( 'key_binder' )
	
			widget:setVisible( true )
			widget:setFocus( true )
		
			message = var1:getParam2( )
	
		end
	
	end

end

function KeyBinder.onHide( )

	local widget = ux:findWidget( 'key_binder' )

	widget:setVisible( false )

end

function KeyBinder.onKeyUp( keyCode )

	local widget = ux:findWidget( 'key_binder' )

	if ( widget:isVisible( ) ) then

		if ( keyCode ~= 27 ) then -- Cancel on the Escape Key
		
			input:setMessageBinding( message, 'k_' .. keyCode )
		
			--script:sendEvent( 'UI_MAPPINGBOUND', '', '' )
		
		end
		
		KeyBinder.onHide( )
	
	end

end

function KeyBinder.onClick( mouseId )

	local widget = ux:findWidget( 'key_binder' )

	if ( widget:isVisible( ) ) then
		
		input:setMessageBinding( message, 'm_' .. mouseId )
		
		script:sendEvent( 'UI_MAPPINGBOUND', '', '' )
		
		KeyBinder.onHide( )
		
	end

end

KeyBinder.initialize( )