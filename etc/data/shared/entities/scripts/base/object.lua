----------------------------------------------------------------
-- Global Variables
----------------------------------------------------------------

Object = { }

function extend( derivedClass, superClass )
	setmetatable( derivedClass, { __index = superClass } )
	
	function derivedClass:super( )
        return superClass
	end
end

----------------------------------------------------------------
-- Local Variables
----------------------------------------------------------------

----------------------------------------------------------------
-- Object Functions
----------------------------------------------------------------

function Object:new( )
	o = { }
	setmetatable( o, self )
	self.__index = self	
	return o
end

function Object:getType( )
	return 'object'
end
