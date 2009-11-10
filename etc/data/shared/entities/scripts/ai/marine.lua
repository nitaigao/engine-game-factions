script:include( '/data/entities/scripts/base/object.lua' )

script:include( '/data/entities/scripts/ai/behaviorselector.lua' )

----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

Marine = { 
	behaviorTree = BehaviorSelector:new( )
}

extend( Marine, Object )

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------



----------------------------------------------------------------
-- Marine Functions
----------------------------------------------------------------

function Marine:initialize( )
	
	script:registerUpdateHandler( Marine.onUpdate )
	script:registerEventHandler( 'ACTOR_DEAD', Marine.onActorDead )
	script:registerEventHandler( 'WORLD_LOADING_FINISHED', Marine.onWorldLoadingFinished )
	
end

function Marine.onWorldLoadingFinished( eventName, eventData )

	marine.behaviorTree:initialize( )

end

function Marine.onActorDead( eventName, eventData )

	if ( eventData:getActorName( ) == ai:getName( ) ) then
		
			script:unregisterEventHandler( 'ACTOR_DEAD', Marine.onActorDead )
			script:unregisterEventHandler( 'WORLD_LOADING_FINISHED', Marine.onWorldLoadingFinished )
			script:unregisterUpdateHandler( Marine.onUpdate )
		
	end

end

function Marine.onUpdate( deltaMilliseconds )

	marine.behaviorTree:update( deltaMilliseconds )

end

marine = Marine:new( )
marine:initialize( )
