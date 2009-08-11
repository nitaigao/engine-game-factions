----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

Disconnected = {}

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------
----------------------------------------------------------------
-- Disconnected Functions
----------------------------------------------------------------

function Disconnected.initialize( )
	
	Disconnected.hide( )

	script:registerEventHandler( Disconnected.onEvent )
	
end

function Disconnected.onEvent( eventName, val1, val2 )

	if ( eventName == 'SERVER_DISCONNECTED' ) then 
	
		Disconnected.show( )
	
	end

end

function Disconnected.hide( )

	local disconnected = ux:findWidget( 'disconnected' )
	disconnected:setVisible( false )

end

function Disconnected.show( )

	local disconnected = ux:findWidget( 'disconnected' )
	disconnected:setVisible( true )

end

Disconnected.initialize( )