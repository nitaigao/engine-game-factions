----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

Create = { }

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------
----------------------------------------------------------------
-- Servers Functions
----------------------------------------------------------------

function Create.initialize( )

	local create = ux:findWidget( 'create_server' ):asWindow( )
	create:setVisible( false )
	ux:scriptWidget( create, 'onWindowButtonPressed', Create.onClosedPressed )

	script:registerEventHandler( Create.onEvent )
	
	local createButton = ux:findWidget( 'create_submit' ):asButton( )
	ux:scriptWidget( createButton, 'onRelease', Create.onCreateClick )
	
	local mapsList = ux:findWidget( 'create_maps' ):asComboBox( )
	
	local maps = network:getServerMaps( )
	
	for key, value in pairs( maps ) do
	
		mapsList:addItem( value, value )
        
	end
	
	if ( table.getn( maps ) > 0 ) then
	
		mapsList:setSelectedIndex( 0 )
	
	end
	
	local port = ux:findWidget( 'create_port' ):asEditBox( )
	port:setText( tostring( Configuration.serverPort ) )
	
	local botcount = ux:findWidget( 'create_botcount' ):asEditBox( )
	botcount:setText( tostring( Configuration.serverBotCount ) )
	
	local servername = ux:findWidget( 'create_servername' ):asEditBox( )
	servername:setText( Configuration.serverName )
	
	local timelimit = ux:findWidget( 'create_timelimit' ):asEditBox( )
	timelimit:setText( tostring( Configuration.serverTimeLimit ) )
	
	local fraglimit = ux:findWidget( 'create_fraglimit' ):asEditBox( )
	fraglimit:setText( tostring( Configuration.serverFragLimit ) )
	
	local maxplayers = ux:findWidget( 'create_maxplayers' ):asEditBox( )
	maxplayers:setText( tostring( Configuration.serverMaxPlayers ) )
	
end

function Create.onEvent( eventName, val1, val2 )

	if ( eventName == 'UI_SHOW_PANE' ) then
	
		if ( val1 == 'UI_CREATESERVER' )  then
	
			Create.onShowCreate( )
	
		end
	
	end
	
	if ( eventName == 'WORLD_LOADING_STARTED' ) then
	
		Create.onHideCreate( )
		
	end

end

function Create.onCreateClick( )

	local port = ux:findWidget( 'create_port' ):asEditBox( )
	local botcount = ux:findWidget( 'create_botcount' ):asEditBox( )
	local servername = ux:findWidget( 'create_servername' ):asEditBox( )
	local timelimit = ux:findWidget( 'create_timelimit' ):asEditBox( )
	local fraglimit = ux:findWidget( 'create_fraglimit' ):asEditBox( )
	local maxplayers = ux:findWidget( 'create_maxplayers' ):asEditBox( )
	
	local mapsList = ux:findWidget( 'create_maps' ):asComboBox( )
	local selectedIndex = mapsList:getSelectedIndex( )
	local levelName = mapsList:getValueAt( selectedIndex )
	
	network:createServer( 
		levelName,
		tonumber( port:getText( ) ), 
		tonumber( botcount:getText( ) ), 
		servername:getText( ), 
		tonumber( timelimit:getText( ) ), 
		tonumber( fraglimit:getText( ) ), 
		tonumber( maxplayers:getText( ) ) 
		)
		
	network:connect( '127.0.0.1', tonumber( port:getText( ) ) )
	
end

function Create.onClosedPressed( )

	Create.onHideCreate( )

end


function Create.onHideCreate( )

	local create = ux:findWidget( 'create_server' ):asWindow( )
	create:setVisible( false )

end

function Create.onShowCreate( )

	local create = ux:findWidget( 'create_server' ):asWindow( )
	create:setVisible( true )

end

Create.initialize( )