----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

Servers = { }

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------
----------------------------------------------------------------
-- Servers Functions
----------------------------------------------------------------

function Servers.initialize( )

	local servers = ux:findWidget( 'servers' )
	servers:setVisible( false )

	script:registerEventHandler( Servers.onEvent )
	
	local closeButton = ux:findWidget( 'servers_close_button' )
	ux:scriptWidget( closeButton, 'onRelease', Servers.onClosePressed )
	
	local serverList = ux:findWidget( 'servers_serverlist' ):asMultiList( )
	serverList:removeAllItems( )
	
	serverList:addColumn( '', 0 ) -- stops the list from auto sorting
	serverList:addColumn( 'Description', 300 )
	serverList:addColumn( 'Players', 100 )
	serverList:addColumn( 'Ping', 100 )
	
end

function Servers.onEvent( eventName, val1, val2 )

	if ( eventName == 'UI_SERVERS' ) then
	
		Servers.onShowServers( )
	
	end
	
	if ( eventName == "SERVER_FOUND" ) then
	
		Servers.onServerFound( )
	
	end

end

function Servers.onServerFound( )

	print( 'server found' )

end

function Servers.onShowServers( )
    
    local options = ux:findWidget( 'servers' )
	options:setVisible( true )
	
end

function Servers.onHideServers( )
    
    local options = ux:findWidget( 'servers' )
	options:setVisible( false )
	
end

function Servers.onClosePressed( )

	Servers.onHideServers( )

end

Servers.initialize( )