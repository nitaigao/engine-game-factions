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
	
	local refreshButton = ux:findWidget( 'servers_refresh_button' ):asButton( )
	ux:scriptWidget( refreshButton, 'onRelease', Servers.onRefresh )
	
	local connectButton = ux:findWidget( 'servers_connect_button' ):asButton( )
	ux:scriptWidget( connectButton, 'onRelease', Servers.onConnect )
	
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
	
	if ( eventName == "SERVER_ADVERTISED" ) then
	
		Servers.onServerAdvertised( val1 )
	
	end

end

function Servers.onRefresh( )

	local serverList = ux:findWidget( 'servers_serverlist' ):asMultiList( )
	serverList:removeAllItems( )
	
	network:findServers( )

end

function Servers.onConnect( )

	print( 'connect clicked' )

end

function Servers.onServerAdvertised( cacheIndex )

	local serverList = ux:findWidget( 'servers_serverlist' ):asMultiList( )
	serverList:addItem( '' )
	
	local serverIndex = serverList:getItemCount( ) - 1
	local serverAd = network:getServerAd( cacheIndex )
	
	for key, value in pairs( serverAd ) do
	
		if ( key == 'serverName' ) then
		
			serverList:setSubItemName( 0, serverIndex, value )
		
		end
		
		if ( key == 'players' ) then
		
			serverList:setSubItemName( 1, serverIndex, value )
		
		end
		
		if ( key == 'levelname' ) then
		
			serverList:setSubItemName( 2, serverIndex, value )
		
		end
		
		if ( key == 'ping' ) then
		
			serverList:setSubItemName( 3, serverIndex, value )
		
		end
	
	end

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