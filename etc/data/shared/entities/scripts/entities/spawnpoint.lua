script:include( '/data/entities/scripts/base/object.lua' )

----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

SpawnPoint = {

}

extend( SpawnPoint, Object )

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------

----------------------------------------------------------------
-- SpawnPoint Functions
----------------------------------------------------------------

function SpawnPoint:initialize( )

	script:registerEventHandler( 'WORLD_LOADING_FINISHED', SpawnPoint.onEvent )

end

function SpawnPoint.onEvent( eventName, var1 )

	if ( eventName == 'WORLD_LOADING_FINISHED' ) then
	
		globals.spawnManager:registerSpawn( script:getName( ), script:getPosition( ) )
	
	end

end

spawnPoint = SpawnPoint:new( )
spawnPoint:initialize( )