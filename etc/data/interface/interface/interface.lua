----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

Interface = { }

Screens = {
	CONSOLE = 'console',
	STATISTICS = 'statistics',
	TITLE = 'title',
	MENU = 'menu',
	OPTIONS = 'options',
	KEY_BINDER = 'key_binder',
	CREATE = 'create',
	LOADING = 'loading',
	CHARACTER_SELECT = 'characterselect',
	SERVERS = 'servers',
	DISCONNECTED = 'disconnected',
	HUD = 'hud'
}
----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------
----------------------------------------------------------------
-- Interface Functions
----------------------------------------------------------------

function Interface.initialize( )

	print( 'Loading Interface' )
	
	--sfx:playMusic( 'game/ux/title_loaded' )
	
	ux:showMouse( )

	for k in pairs( Screens ) do
		
		ux:loadComponent( Screens[ k ] )
	
	end
	
end

Interface.initialize( )