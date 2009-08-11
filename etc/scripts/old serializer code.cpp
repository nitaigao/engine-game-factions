/*else if( elementName == "fog" )
		{
			this->LoadFog( element );
		}
		else if ( elementName == "skybox" )
		{
			this->LoadSkyBox( element );
		}*/
	}
	
	/*void XMLSerializer::LoadLink( const YAML::Node& node )
	{ 
		std::string subjectName, subjectSystem, observerName, observerSystem;
	
		node[ "subjectName" ] >> subjectName;
		node[ "subjectSystem" ] >> subjectSystem;
		node[ "observerName" ] >> observerName;
		node[ "observerSystem" ] >> observerSystem;
	
		System::Types::Type subjectSystemType = System::SystemTypeMapper::StringToType( subjectSystem );
		System::Types::Type observerSystemType = System::SystemTypeMapper::StringToType( observerSystem );

		if ( 
			Management::Get( )->GetSystemManager( )->HasSystem( subjectSystemType ) && 
			Management::Get( )->GetSystemManager( )->HasSystem( observerSystemType ) 
			)
		{
			IWorldEntity* subject = m_world->FindEntity( subjectName );
			IWorldEntity* observer = m_world->FindEntity( observerName );

			subject->AddObserver( System::Messages::SetPlayerPosition, observer );
		}
	}*/
	
	/*void XMLSerializer::LoadSkyBox( const YAML::Node& node )
	{
		if ( Management::Get( )->GetSystemManager( )->HasSystem( System::Types::RENDER ) )
		{
			std::string materialName;
			node[ "material" ] >> materialName;

			float distance;
			node[ "distance" ] >> distance;

			AnyType::AnyTypeMap parameters;
			parameters[ "material" ] = materialName;
			parameters[ "distance" ] = distance;
		
			ISystem* renderer = Management::Get( )->GetSystemManager( )->GetSystem( System::Types::RENDER );
			renderer->SetAttribute( "skyBox", parameters );
		}
	}*/

	/*void XMLSerializer::LoadFog( const YAML::Node& node )
	{
		if ( Management::Get( )->GetSystemManager( )->HasSystem( System::Types::RENDER ) )
		{
			float linearEnd, linearStart;
			node[ "linearEnd" ] >> linearEnd;
			node[ "linearStart" ] >> linearStart;

			float r, g, b;
			node[ "r" ] >> r;
			node[ "g" ] >> g;
			node[ "b" ] >> b;

			AnyType::AnyTypeMap parameters;
			parameters[ "linearEnd" ] = linearEnd;
			parameters[ "linearStart" ] = linearStart;
			parameters[ "color" ] = Renderer::Color( r, g, b );

			ISystem* renderer = Management::Get( )->GetSystemManager( )->GetSystem( System::Types::RENDER );
			renderer->SetAttribute( "fog", parameters );
		}
	}*/