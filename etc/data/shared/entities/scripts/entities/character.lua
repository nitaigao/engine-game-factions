script:include( '/data/entities/scripts/entities/actor.lua' )
script:include( '/data/entities/scripts/entities/weapon.lua' )

----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

Character = { 
	health = 100,
	weapon = Weapon:create( 'fsg400', 5, 2 ),
	isdead = false,
	eyeLevel = Vector( 0, 1.73, 0 )
}

extend( Character, Actor )

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------

----------------------------------------------------------------
-- Character Functions
----------------------------------------------------------------

function Character:initialize( )

	script:registerEventHandler( 'SPAWN_RESPONSE', Character.onEvent )
	script:broadcastEvent( 'SPAWN_REQUEST', script:getName( ) )

end

function Character:fireWeapon( )
	
	self.weapon:fireAt( script:getPosition( ) + self.eyeLevel, script:getLookAt( ) + self.eyeLevel )

end

function Character:stopFiringWeapon( )

	self.weapon:stopFiring( )

end

function Character:spawn( )

	local spawnPosition = globals.spawnManager:requestSpawn( )
	
	script:setPosition( spawnPosition )

end

function Character:onHit( damage )

	if ( not self.isdead ) then

		self.health = self.health - damage

		if ( self.health <= 0 ) then
		
			self:onDie( )
		
		end
		
	end
	
end

function Character:onDie( )

	self.isdead = true
	script:broadcastEvent( 'ACTOR_DEAD', script:getName( ) )
	
end

function Character.onEvent( eventName, var1, var2 )

	if ( eventName == 'SPAWN_RESPONSE' ) then
	
		if ( var1:getActorName( ) == script:getName( ) ) then
		
			print( 'spawn response received' )
		
		end
	
	end

end
