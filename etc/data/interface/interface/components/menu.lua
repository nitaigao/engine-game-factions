----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

Menu = {

}

menu_ingame = false

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------
----------------------------------------------------------------
-- Menu Functions
----------------------------------------------------------------

function Menu.initialize( )

	script:registerEventHandler( 'INPUT_KEY_UP', Menu.onEvent )
	script:registerEventHandler( 'GAME_ENDED', Menu.onEvent )
	script:registerEventHandler( 'UI_SHOW_PANE', Menu.onEvent )
	script:registerEventHandler( 'MAIN_MENU', Menu.onEvent )
	script:registerEventHandler( 'WORLD_LOADING_STARTED', Menu.onEvent )
	script:registerEventHandler( 'GRAPHICS_SETTINGS_CHANGED', Menu.onEvent )

	Menu.onHideMenu( )
	
	local quitButton = ux:findWidget( 'button_quit' )
	ux:scriptWidget( quitButton, 'onRelease', Menu.onQuitReleased )
	
	local optionsButton = ux:findWidget( 'button_options' )
	ux:scriptWidget( optionsButton, 'onRelease', Menu.onOptionsReleased )
	
	local playButton = ux:findWidget( 'button_play' )
	ux:scriptWidget( playButton, 'onRelease', Menu.onPlayReleased )
	
	local createButton = ux:findWidget( 'button_create' )
	ux:scriptWidget( createButton, 'onRelease', Menu.onCreateReleased )
	
	local resumeButton = ux:findWidget( 'button_resume' )
	ux:scriptWidget( resumeButton, 'onRelease', Menu.onResumeReleased )
	
	local endGameButton = ux:findWidget( 'button_endgame' )
	ux:scriptWidget( endGameButton, 'onRelease', Menu.onEndGameReleased )

	Menu.updatePosition( )
	
end

function Menu.onEvent( eventName, eventData )
	
	if ( eventName == 'INPUT_KEY_UP' ) then 

		Menu.onKeyUp( eventData:getKeyCode( ) )
	
	end
	
	if ( eventName == 'GAME_ENDED' ) then
		
		Menu.endGame( )
	
	end
	
	if ( eventName == 'UI_SHOW_PANE' ) then
	
		if ( eventData:getParam1( ) == Screens.MENU )  then
	
			Menu.onShowMenu( )
	
		end
	
	end
	
	if ( eventName == 'WORLD_LOADING_STARTED' ) then
	
		Menu.onHideMenu( )
		ux:hideMouse( )
		menu_ingame = true
		
	end
	
	if ( eventName == 'GRAPHICS_SETTINGS_CHANGED' ) then
	
		Menu.updatePosition( )
	
	end

end

function Menu.updatePosition( )

	local menu = ux:findWidget( 'menubox' )
	
	local menuX = ux:getScreenWidth( ) / 20
	
	local halfScreenHeight = ( ux:getScreenHeight( ) - menu:getDimensions( ).height ) / 2
	local offsetY = halfScreenHeight / 2
	local menuY = halfScreenHeight + offsetY
	
	menu:setPosition( menuX, menuY )

end

function Menu.onShowMenu( )

	local menu = ux:findWidget( 'menu' )
	menu:setVisible( true ) 
	menu:setAlpha( 0 )
	
	script:registerUpdateHandler( Menu.onInGameMenuShowUpdate )

end

function Menu.onHideMenu( )

	local menu = ux:findWidget( 'menu' )
	menu:setVisible( false )
	ux:hideMouse( )

end

function Menu.onKeyUp( keyCode )

	if ( keyCode == 1 and menu_ingame ) then
	
		Menu.ToggleInGameMenu( )
	
	end
	
end

function Menu.ToggleInGameMenu( )
	
	local menu = ux:findWidget( 'menu' )
	
	if ( menu:isVisible( ) ) then 
	
		local playButton = ux:findWidget( 'button_play' )
		playButton:setVisible( true )
		
		local createButton = ux:findWidget( 'button_create' )
		createButton:setVisible( true )
		
		local resumeButton = ux:findWidget( 'button_resume' )
		resumeButton:setVisible( false )
		
		local quitButton = ux:findWidget( 'button_quit' )
		quitButton:setVisible( true )
		
		local seperatorButton = ux:findWidget( 'button_seperator1' )
		seperatorButton:setVisible( true )
		
		local endGameButton = ux:findWidget( 'button_endgame' )
		endGameButton:setVisible( false )
		
		local titleBackground = ux:findWidget( 'background_title' )
		titleBackground:setVisible( true )
	
		ux:setInputAllowed( true )
		Menu.onHideMenu( )
		
	else
	
		local playButton = ux:findWidget( 'button_play' )
		playButton:setVisible( false )
		
		local createButton = ux:findWidget( 'button_create' )
		createButton:setVisible( false )
		
		local resumeButton = ux:findWidget( 'button_resume' )
		resumeButton:setVisible( true )
		
		local quitButton = ux:findWidget( 'button_quit' )
		quitButton:setVisible( false )
		
		local seperatorButton = ux:findWidget( 'button_seperator1' )
		seperatorButton:setVisible( false )
		
		local endGameButton = ux:findWidget( 'button_endgame' )
		endGameButton:setVisible( true )
		
		local titleBackground = ux:findWidget( 'background_title' )
		titleBackground:setVisible( false )
	
		ux:setInputAllowed( false )
		Menu.onShowMenu( )
	
	end

end

function Menu.onInGameMenuShowUpdate( )

	local menu = ux:findWidget( 'menu' )
	local menuAlpha = menu:getAlpha( )
	
	if ( menuAlpha < 1 ) then
	
		menu:setAlpha( menuAlpha + 0.2 )
	else
	
		ux:showMouse( )
		script:unregisterUpdateHandler( Menu.onInGameMenuShowUpdate )
	
	end

end

function Menu.onQuitReleased( )

	system:quit( )

end

function Menu.onOptionsReleased( )

	ux:showScreen( Screens.OPTIONS )

end

function Menu.onPlayReleased( )

	ux:showScreen( Screens.SERVERS )

end

function Menu.onCreateReleased( )
	
		ux:showScreen( Screens.CREATE )

end

function Menu.onResumeReleased( )

	Menu.ToggleInGameMenu( )

end

function Menu.onEndGameReleased( )

	network:disconnect( )
	Menu.ToggleInGameMenu( )
	Menu.endGame( )
	system:endGame( )

end

function Menu.endGame( )

	menu_ingame = false
	Menu.onShowMenu( )
	ux:setInputAllowed( false )

end

Menu.initialize( )