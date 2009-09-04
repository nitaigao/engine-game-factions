script:include( '/data/entities/scripts/entities/character.lua' )

----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

Player = {
	actions = { }
}

extend( Player, Character )

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------

----------------------------------------------------------------
-- Player Functions
----------------------------------------------------------------

function Player:initialize( )

	self.super( ):initialize( )

	script:subscribeMessage( '+attack_primary', Player.onMessage )
	script:subscribeMessage( '-attack_primary', Player.onMessage )
	script:subscribeMessage( '+strafe_right', Player.onMessage )
	script:subscribeMessage( '-strafe_right', Player.onMessage )
	script:subscribeMessage( '+strafe_left', Player.onMessage )
	script:subscribeMessage( '-strafe_left', Player.onMessage )
	script:subscribeMessage( '+move_forward', Player.onMessage )
	script:subscribeMessage( '-move_forward', Player.onMessage )
	script:subscribeMessage( '+move_backward', Player.onMessage )
	script:subscribeMessage( '-move_backward', Player.onMessage )
	
	sfx:triggerEvent( 'game/environment/ambience' )
	animation:startAnimation( 'stopped', true )
		
	self.super( ):spawn( )

end

function Player.onMessage( message, var1, var2 )
	
	if ( message == 'ACTOR_DEAD' ) then 
	
		print( 'player just died' )
			
	end
	
	if ( message == 'ACTOR_HIT' ) then
		
		player:onHit( var2 )
		--script:broadcastEvent( 'PLAYER_HIT', player.health )
	
	end
	
	-- Attack --
	
	attackSet = false
	
	if ( message == '+attack_primary' ) then 
	
		player:fireWeapon( )
		animation:startAnimation( 'shoot', true )
		
		return
	
	end
	
	if ( message == '-attack_primary' ) then 
		
		player:stopFiringWeapon( );
		animation:stopAnimation( 'shoot' )
	
	end
	
	-- Movement --
	
	movementSet = false
	
	if( message == '-strafe_right' ) then
	
		animation:stopAnimation( 'strafe_right' )
		sfx:keyOutEvent( 'game/biped/running' )
	
	end
	
	if( message == '+strafe_right' ) then

		animation:startAnimation( 'strafe_right', true )
		sfx:triggerEvent( 'game/biped/running' )
		
		return
	
	end
	
	if( message == '-strafe_left' ) then
	
		animation:stopAnimation( 'strafe_left' )
		sfx:keyOutEvent( 'game/biped/running' )
	
	end
	
	if( message == '+strafe_left' ) then
	
		animation:startAnimation( 'strafe_left', true )
		sfx:triggerEvent( 'game/biped/running' )
		
		return
	
	end
	
	if( message == '-move_forward' ) then
		
		animation:stopAnimation( 'run_forward' )
		sfx:keyOutEvent( 'game/biped/running' )
	
	end
	
	if( message == '+move_forward' ) then
		
		animation:startAnimation( 'run_forward', true )
		sfx:triggerEvent( 'game/biped/running' )
	
	end
	
	if( message == '-move_backward' ) then
	
		animation:stopAnimation( 'run_backward' )
		sfx:keyOutEvent( 'game/biped/running' )
	
	end
	
	if( message == '+move_backward' ) then
	
		animation:startAnimation( 'run_backward', true )
		sfx:triggerEvent( 'game/biped/running' )
		
		return
	
	end

end

player = Player:new( )
player:initialize( )