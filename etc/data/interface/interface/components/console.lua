----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

Console = {}

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------

console = nil
output = nil
input = nil
console_ingame = false

----------------------------------------------------------------
-- Console Functions
----------------------------------------------------------------

function Console.initialize( )

	script:registerEventHandler( 'UI_SHOW_PANE', Console.onShowPane )
	script:registerEventHandler( 'LOG_MESSAGE_APPENDED', Console.onMessageLogged )
	script:registerEventHandler( 'WORLD_LOADING_FINISHED', Console.onWorldLoadingFinished )
	script:registerEventHandler( 'GAME_ENDED', Console.onGameEnded )
	
	console = ux:findWidget( 'console' )
	console:setVisible( false )
	
	input = ux:findWidget( 'console_input' )
	ux:scriptWidget( input, 'onKeyUp', Console.onKeyUp )
	
	output = ux:findWidget( 'console_output' )
	
end

function Console.onShowPane( eventName, eventData )

	if ( eventData:getParam1( ) == Screens.CONSOLE ) then
	
		Console.onShowConsole( )
	
	end

end

function Console.onMessageLogged( eventName, val1, val2 )
	
	Console.updateConsole( val1:getParam1( ) )

end

function Console.onWorldLoadingFinished( eventName, eventData )

	console_ingame = true

end

function Console.onGameEnded( eventName, eventData )

	console_ingame = false

end

function Console.onShowConsole( )

	if ( Configuration.isConsole ) then
		
		if ( console:isVisible( ) ) then
		
			console:setVisible( false )
			
			local menu = ux:findWidget( 'menu' )
			
			if ( not menu:isVisible( ) ) then
			
				ux:hideMouse( )
				input:setFocus( false )
			
			end
			
			if ( console_ingame ) then
			
				ux:setInputAllowed( true )
				
			end
			
		else
		
			input:setFocus( true )
			console:setVisible( true ) 
			ux:showMouse( )
			ux:setInputAllowed( false )
				
		end
		
	end
	
end

function Console.onKeyUp( keyCode, keyText )

	if ( keyCode == 28 ) then
	
		local input = input:asEditBox( )
	
		local text = input:getText( )
		script:executeString( text )
		
		input:setText( '' )
		
	end
	
	if ( keyCode == 41 ) then
	
		local input = input:asEditBox( )
		
		input:eraseText( input:getLength( ) - 1, 1 )
	
	end

end

function Console.updateConsole( message )

	local output = output:asEditBox( )
	output:addText( message )

end

Console.initialize( )