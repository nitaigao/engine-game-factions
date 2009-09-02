----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

Interface = { }

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------
----------------------------------------------------------------
-- Interface Functions
----------------------------------------------------------------

function Interface.initialize( )

	print( 'Loading Interface' )
	
	--sfx:playMusic( 'game/ux/title_loaded' )
	
	--script:unregisterEventHandler( Interface.onEvent )
	ux:showMouse( )

	ux:loadComponent( 'title' )
	--ux:loadComponent( 'menu' )
	--ux:loadComponent( 'options' )
	--ux:loadComponent( 'console' )
	--ux:loadComponent( 'loading' )
	--ux:loadComponent( 'hud' )
--	-ux:loadComponent( 'statistics' )
	--ux:loadComponent( 'actor_hit' )
--	ux:loadComponent( 'key_binder' )
--	ux:loadComponent( 'characterselect' )
--	ux:loadComponent( 'servers' )
--	ux:loadComponent( 'disconnected' )
	
end

function Interface.onEvent( eventName )

	if ( eventName == 'GAME_INITIALIZED' ) then
	
		
	
	end

end

--script:registerEventHandler( Interface.onEvent )
Interface.initialize( )