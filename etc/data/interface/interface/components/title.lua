----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

Title = {

}

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------
----------------------------------------------------------------
-- Title Functions
----------------------------------------------------------------

function Title.initialize( )

	ux:hideMouse( )
	
	script:registerEventHandler( 'INPUT_KEY_UP', Title.onEvent )
	script:registerEventHandler( 'INPUT_MOUSE_RELEASED', Title.onEvent )
	script:registerEventHandler( 'WORLD_LOADING_STARTED', Title.onEvent )

	local logo = ux:findWidget( 'logo' )
	local logoX = ( ux:getScreenWidth( ) - logo:getDimensions( ).width ) / 2
	local logoY = ( ux:getScreenHeight( ) - logo:getDimensions( ).height ) / 2
	logo:setPosition( logoX, logoY )
	
	logo:setAlpha( 0 )
	script:registerUpdateHandler( Title.onShowUpdate )

end

function Title.onShowUpdate( )

	local logo = ux:findWidget( 'logo' )
	local logoAlpha = logo:getAlpha( )
	
	if ( logoAlpha < 1 ) then
	
		logo:setAlpha( logoAlpha + 0.1 )
	else
	
		script:unregisterUpdateHandler( Title.onShowUpdate )
	
	end

end

function Title.onHideUpdate( )

	local logo = ux:findWidget( 'title' )
	local logoAlpha = logo:getAlpha( )
	
	if ( logoAlpha > 0 ) then
	
		logo:setAlpha( logoAlpha - 0.1 )
	
	else
	
		Title.deactivate( )
		script:sendEvent( 'UI_SHOW_PANE', 'MAIN_MENU', '' ) 
	
	end

end

function Title.deactivate( )
	
	script:unregisterUpdateHandler( Title.onHideUpdate )
	script:unregisterUpdateHandler( Title.onShowUpdate )
	
	script:unregisterEventHandler( 'INPUT_KEY_UP', Title.onEvent )
	script:unregisterEventHandler( 'INPUT_MOUSE_RELEASED', Title.onEvent )

	local logo = ux:findWidget( 'title' )
	
	logo:setVisible( false )
	logo:setAlpha( 1 )

end

function Title.onEvent( eventName, val1, val2 )

	if ( eventName == 'INPUT_KEY_UP' ) or ( eventName == 'INPUT_MOUSE_RELEASED' ) then 
	
		script:registerUpdateHandler( Title.onHideUpdate )
	
	end
	
	if( eventName == 'WORLD_LOADING_STARTED' ) then
		
		Title.deactivate( )
	
	end

end

Title.initialize( )