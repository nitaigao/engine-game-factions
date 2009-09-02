script:include( '/data/entities/scripts/base/object.lua' )

----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

SpawnPoint = {
	
	name = '',
	position = ''
	
}

extend( SpawnPoint, Object )

SpawnManager = {

	spawns = { }

}

extend( SpawnManager, Object )

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------

----------------------------------------------------------------
-- SpawnManager Functions
----------------------------------------------------------------

function SpawnManager:initialize( )

	script:registerEventHandler( SpawnManager.onEvent )

end

function SpawnManager:registerSpawn( name, position )

	local spawnPoint = SpawnPoint:new( )
	spawnPoint.name = name
	
	table.insert( self.spawns, spawnPoint )

end

function SpawnManager:requestSpawn( characterName )

	local spawnCount = table.getn( self.spawns )
	local spawnIndex = math.random( 1, spawnCount )
	local spawnPosition = self.spawns[ spawnIndex ].position
	
	script:broadcastEvent( 'SPAWN_RESPONSE', characterName )

end

function SpawnManager.onEvent( eventName, var1, var2 )

	if ( eventName == 'SPAWN_REGISTER' ) then
	
		spawnManager:registerSpawn( var1, var2 )
	
	end
	
	if ( eventName == 'SPAWN_REQUEST' ) then
	
		spawnManager:requestSpawn( var1 )
	
	end
	
end

spawnManager = SpawnManager:new( )
spawnManager:initialize( )