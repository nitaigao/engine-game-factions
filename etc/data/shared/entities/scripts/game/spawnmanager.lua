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
	
	globals.spawnManager = spawnManager
	
	math.randomseed( os.time( ) )

end

function SpawnManager:registerSpawn( name, position )

	local spawnPoint = SpawnPoint:new( )
	spawnPoint.name = name
	spawnPoint.position = position
	
	table.insert( self.spawns, spawnPoint )

end

function SpawnManager:requestSpawn( )

	local spawnCount = table.getn( self.spawns )

	for i = 0, math.random( 10 ) do
	
		 math.random( 1, spawnCount )
	
	end

	local spawnIndex = math.random( 1, spawnCount )
	local spawnPosition = self.spawns[ spawnIndex ].position
	
	return spawnPosition

end

spawnManager = SpawnManager:new( )
spawnManager:initialize( )