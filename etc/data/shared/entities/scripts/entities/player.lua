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

	script:subscribeMessage( '+attack_primary', Player.onAttackPrimary )
	script:subscribeMessage( '-attack_primary', Player.afterAttackPrimary )
	script:subscribeMessage( '+strafe_right', Player.onStrafeRight )
	script:subscribeMessage( '-strafe_right', Player.afterStrafeRight )
	script:subscribeMessage( '+strafe_left', Player.onStrafeLeft )
	script:subscribeMessage( '-strafe_left', Player.afterStrafeLeft )
	script:subscribeMessage( '+move_forward', Player.onMoveForward )
	script:subscribeMessage( '-move_forward', Player.afterMoveForward )
	script:subscribeMessage( '+move_backward', Player.onMoveBackward )
	script:subscribeMessage( '-move_backward', Player.afterMoveBackward )
	
	sfx:triggerEvent( 'game/environment/ambience' )
	animation:startAnimation( 'stopped', true )
		
	self.super( ):spawn( )

end

function Player.onActorDead( message, data )

end

function Player.onActorHit( message, data )

end

function Player.onAttackPrimary( message, data )

	player:fireWeapon( )
	animation:startAnimation( 'shoot', true )

end

function Player.afterAttackPrimary( message, data )

	player:stopFiringWeapon( );
	animation:stopAnimation( 'shoot' )

end

function Player.onStrafeRight( message, data )

	animation:startAnimation( 'strafe_right', true )
	sfx:triggerEvent( 'game/biped/running' )

end

function Player.afterStrafeRight( message, data )

	animation:stopAnimation( 'strafe_right' )
	sfx:keyOutEvent( 'game/biped/running' )

end

function Player.onStrafeLeft( message, data )

	animation:startAnimation( 'strafe_left', true )
	sfx:triggerEvent( 'game/biped/running' )

end

function Player.afterStrafeLeft( message, data )

	animation:stopAnimation( 'strafe_left' )
	sfx:keyOutEvent( 'game/biped/running' )

end

function Player.onMoveForward( message, data )

	animation:startAnimation( 'run_forward', true )
	sfx:triggerEvent( 'game/biped/running' )

end

function Player.afterMoveForward( message, data )

	animation:stopAnimation( 'run_forward' )
	sfx:keyOutEvent( 'game/biped/running' )

end


function Player.onMoveBackward( message, data )

	animation:startAnimation( 'run_backward', true )
	sfx:triggerEvent( 'game/biped/running' )

end

function Player.afterMoveBackward( message, data )

	animation:stopAnimation( 'run_backward' )
	sfx:keyOutEvent( 'game/biped/running' )
	
end

function Player.onMessage( message, var1, var2 )
	
	if ( message == 'ACTOR_DEAD' ) then 
	
		print( 'player just died' )
			
	end
	
	if ( message == 'ACTOR_HIT' ) then
		
		player:onHit( var2 )
		--script:broadcastEvent( 'PLAYER_HIT', player.health )
	
	end

end

player = Player:new( )
player:initialize( )