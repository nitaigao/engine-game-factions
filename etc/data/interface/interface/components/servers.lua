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

	script:registerEventHandler( 'UI_SHOW_PANE', Servers.onShowPane )
	script:registerEventHandler( 'NETWORK_SERVER_DISCOVERED', Servers.onServerDiscovered )
	
	local refreshButton = ux:findWidget( 'servers_refresh_button' ):asButton( )
	ux:scriptWidget( refreshButton, 'onRelease', Servers.onRefresh )
	
	local connectButton = ux:findWidget( 'servers_connect_button' ):asButton( )
	ux:scriptWidget( connectButton, 'onRelease', Servers.onConnectClicked )
	
	local serverList = ux:findWidget( 'servers_serverlist' ):asMultiList( )
	ux:scriptWidget( serverList, 'onListSelectAccept', Servers.onServerListDoubleClick )
	
	serverList:removeAllItems( )
	
	serverList:addColumn( 'Description', 300 )
	serverList:addColumn( 'Players', 100 )
	serverList:addColumn( 'Map', 100 )
	serverList:addColumn( 'Ping', 100 )
	serverList:addColumn( 'Address', 0 )
	serverList:addColumn( 'Port', 0 )
	
	Servers.onResized( )
	
end

function Servers.onShowPane( eventName, val1, val2 )

	if ( eventName == 'UI_SHOW_PANE' ) then
	
		if ( val1:getParam1( ) == Screens.SERVERS )  then
	
			Servers.onShowServers( )
	
		end
	
	end
	
end

function Servers.onRefresh( )

	local serverList = ux:findWidget( 'servers_serverlist' ):asMultiList( )
	serverList:removeAllItems( )
	
	network:findServers( )

end

function Servers.onServerListDoubleClick( index )

	local serverList = ux:findWidget( 'servers_serverlist' ):asMultiList( )
	
	local serverAddress = serverList:getSubItemName( 4, index )
	local serverPort = serverList:getSubItemName( 5, index )
	
	Servers.Connect( serverAddress )

end

function Servers.onConnectClicked( )

	local serverList = ux:findWidget( 'servers_serverlist' ):asMultiList( )

	local serverAddress = serverList:getSubItemName( 4, serverList:getSelectedIndex( ) )
	local serverPort = serverList:getSubItemName( 5, serverList:getSelectedIndex( ) )
	
	Servers.Connect( serverAddress )

end

function Servers.Connect( serverAddress )

	network:connect( serverAddress )
	Servers.onHideServers( )

end

function Servers.onServerDiscovered( event, data )

	local serverList = ux:findWidget( 'servers_serverlist' ):asMultiList( )
	serverList:addItem( '' )
	
	local serverIndex = serverList:getItemCount( ) - 1
	
	serverList:setSubItemName( 0, serverIndex, '' .. data:getServerName( ) )
	serverList:setSubItemName( 1, serverIndex, '' .. data:getNumPlayers( ) .. '/' .. data:getMaxPlayers( ) )
	serverList:setSubItemName( 2, serverIndex, '' .. data:getMapName( ) )
	serverList:setSubItemName( 3, serverIndex, '' .. data:getPing( ) .. 'ms' )
	serverList:setSubItemName( 4, serverIndex, '' .. data:getAddress( ) )

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