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

	local servers = ux:findWidget( 'servers' ):asWindow( )
	servers:setVisible( false )
	ux:scriptWidget( servers, 'onWindowButtonPressed', Servers.onClosePressed )
	ux:scriptWidget( servers, 'onWindowChangeCoord', Servers.onResized )

	script:registerEventHandler( Servers.onEvent )
	
	local serverList = ux:findWidget( 'servers_serverlist' ):asMultiList( )
	serverList:removeAllItems( )
	
	serverList:addColumn( 'Description', 300 )
	serverList:addColumn( 'Players', 100 )
	serverList:addColumn( 'Map', 100 )
	serverList:addColumn( 'Ping', 100 )
	
	Servers.onResized( )
	
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

function Servers.onResized( )

	local serverList = ux:findWidget( 'servers_serverlist' ):asMultiList( )
	
	local existingColumnsWidth = 0
	
	for i = serverList:getColumnCount( ) - 1, 0, -1 do
	
		if ( i ~= 0 ) then
	
			existingColumnsWidth = existingColumnsWidth + serverList:getColumnWidthAt( i )
			
		else
		
			local excessWidth = serverList:getDimensions( ).width - existingColumnsWidth
			serverList:setColumnWidthAt( i, excessWidth )
		
		end
	
	end

end

Servers.initialize( )