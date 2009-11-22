/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   SystemType.hpp
*  @date   2009/04/25
*/
#pragma once
#ifndef SYSTEMTYPES_H
#define SYSTEMTYPES_H

#include <string>

namespace System
{
	namespace Types
	{
		enum Type
		{
			NONE = 0,
			SCRIPT = 1,
			RENDER = 2,
			GEOMETRY = 3,
			INPUT = 4,
			PHYSICS = 5,
			AI = 6,
			UX = 7,
			SOUND = 8,
			ANIMATION = 9,
			NETWORK = 10,
			ENTITY = 11,
			TEST = 12,
			SYSTEMTYPES_MAX = 13
		};
	};

	namespace TypeStrings
	{
		static const std::string RENDERER				= "graphics";
		static const std::string SCRIPT					= "script";
		static const std::string GEOMETRY				= "geometry";
		static const std::string PHYSICS				= "physics";
		static const std::string INPUT					= "input";
		static const std::string AI						= "ai";
		static const std::string SOUND					= "sound";
		static const std::string ANIMATION				= "animation";
		static const std::string NETWORK				= "network";
		static const std::string UX						= "ux";
		static const std::string ENTITY					= "entity";
	};

	namespace Queues
	{
		enum Queue
		{
			LOGIC = 0,
			HOUSE = 1,
			RENDER = 2
		};
	};

	namespace Options
	{
		static const std::string LevelName				=	"levelName";
		static const std::string DedicatedServer		=	"dedicated";
	}

	typedef std::string Attribute;

	namespace Attributes
	{
		static const Attribute Name						=	"name";
		static const Attribute LookAt					=	"lookAt";
		static const Attribute POI						=	"poi";
		static const Attribute Position					=	"position";
		static const Attribute Orientation				=	"orientation";
		static const Attribute Scale					=	"scale";
		static const Attribute FilePath					=	"filePath";
		static const Attribute SystemType				=	"system";
		static const Attribute Parent					=	"parent";
		static const Attribute Message					=	"message";
		static const Attribute ComponentType			=	"type";
		static const Attribute EntityType				=	"entityType";
		
		namespace Animation
		{
			static const Attribute Animations			=	"animations";
			static const Attribute DefaultAnimation		=	"defaultAnimation";
			static const Attribute BindPose				=	"bindPose";
		}

		namespace Network
		{
			static const Attribute IsServer				=	"isServer";
		}
	};

	typedef std::string Parameter;

	namespace Parameters
	{
		static const Parameter DeltaX					=	"deltaX";
		static const Parameter DeltaY					=	"deltaY";
		static const Parameter ScriptPath				=	"scriptPath";
		static const Parameter Model					=	"model";
		static const Parameter Body						=	"body";
		static const Parameter PlayerPosition			=	"playerPosition";
		static const Parameter PlayerOrientation		=	"playerOrientation";
		static const Parameter SoundEventPath			=	"soundEventPath";
		static const Parameter Mouse					=	"mouse";
		static const Parameter Keyboard					=	"keyboard";
		static const Parameter ScriptState				=	"scriptState";
		static const Parameter Binding					=	"binding";
		static const Parameter InvertYAxis				=	"invertYAxis";
		static const Parameter SmoothMouse				=	"smoothMouse";
		static const Parameter NavMeshPath				=	"navMeshPath";
		static const Parameter NavigationMesh			=	"navMesh";
		static const Parameter MouseSensitivity			=	"mouseSensitivity";
		static const Parameter Vertices					=	"vertices";
		static const Parameter Origin					=	"origin";
		static const Parameter Destination				=	"destination";
		static const Parameter GlobalObject				=	"globalObject";
		static const Parameter GlobalName				=	"globalName";
		static const Parameter SortByyDistance			=	"sortByDistance";
		static const Parameter MaxResults				=	"maxResults";
		static const Parameter AnimationName			=	"animationName";
		static const Parameter LoopAnimation			=	"loopAnimation";
		static const Parameter AnimationWeight			=	"animationWeight";
		static const Parameter AnimationController		=	"animationController";

		namespace Input
		{
			static const Parameter MouseButtonId		=	"mouseButtonId";
		}

		namespace Network
		{
			static const Parameter HostAddress			=	"hostAddress";
			static const Parameter Port					=	"hostPort";
			static const Parameter ComponentId			=	"componentId";
			static const Parameter ComponentMessage		=	"componentMessage";
			static const Parameter EndOfParameters		=	"endOfParameters";
			static const Parameter Sender				=	"sender";

			namespace Client
			{
				static const Parameter CharacterName	=	"characterName";
				static const Parameter ServerCacheIndex =	"serverCacheIndex";
			}

			namespace Server
			{
				static const Parameter ServerName		=	"serverName";
				static const Parameter LevelName		=	"levelname";
				static const Parameter MaxPlayers		=	"maxPlayers";
				static const Parameter PlayerCount		=	"playerCount";
				static const Parameter Ping				=	"ping";
			}
		}

		namespace Game
		{
			static const Parameter LevelName			=	"levelName";
		}

		namespace Graphics
		{
			static const Parameter Width				=	"width";
			static const Parameter Height				=	"height";
			
			
			static const Parameter FullScreen			=	"fullScreen";
			static const Parameter CameraName			=	"cameraName";
		}

		namespace IO
		{
			static const Parameter Stream				=	"stream";
			static const Parameter Progress				=	"progress";
		}
	};

	typedef std::string MessageType;

	namespace Messages
	{
		// Geometry
		static const MessageType All_Messages				=	"all_messages";
		static const MessageType SetPosition				=	"set_position";
		static const MessageType SetOrientation				=	"set_orientation";
		static const MessageType SetLookAt					=	"set_lookAt";
		static const MessageType SetPlayerPosition			=	"set_player_position";

		//Sound
		static const MessageType PlayMusic					=	"playMusic";
		static const MessageType TriggerSoundEvent			=	"trigger_soundevent";
		static const MessageType KeyOutSoundEvent			=	"keyout_soundevent";

		//Input
		static const MessageType Move_Forward_Pressed		=	"+move_forward";
		static const MessageType Move_Forward_Released		=	"-move_forward";
		static const MessageType Move_Backward_Pressed		=	"+move_backward";
		static const MessageType Move_Backward_Released		=	"-move_backward";
		static const MessageType Strafe_Left_Pressed		=	"+strafe_left";
		static const MessageType Strafe_Left_Released		=	"-strafe_left";
		static const MessageType Strafe_Right_Pressed		=	"+strafe_right";
		static const MessageType Strafe_Right_Released		=	"-strafe_right";
		static const MessageType Turn_Left_Pressed			=	"+turn_left";
		static const MessageType Turn_Left_Released			=	"-turn_left";
		static const MessageType Turn_Right_Pressed			=	"+turn_right";
		static const MessageType Turn_Right_Released		=	"-turn_right";

		static const MessageType Attack_Primary_Pressed		=	"+attack_primary";
		static const MessageType Attack_Primary_Released	=	"-attack_primary";

		static const MessageType Mouse_Moved				=	"mouse_moved";
		static const MessageType Jump						=	"jump";

		static const MessageType GetBindingForMessage		=	"getBindingForMessage";
		static const MessageType SetBindingForMessage		=	"setBindingForMessage";
		static const MessageType SetInvertYAxis				=	"setInvertYAxis";

		//Game
		static const MessageType Pause_Game					=	"pause";
		
		//AI
		static const MessageType FindPath					=	"findPath";
		
		//Renderer
		static const MessageType LoadMesh					=	"loadNavMesh";
		static const MessageType RenderMesh					=	"renderMesh";
		static const MessageType DestroyMesh				=	"destroy";

		//Physics
		static const MessageType RayQuery					=	"castRay";

		//Script
		static const MessageType LoadScript					=	"loadScript";
		static const MessageType SetScriptGlobal			=	"setScriptGlobal";
		static const MessageType GetState					=	"getState";
		static const MessageType RunScript					=	"runScript";
		static const MessageType RegisterScriptFunctions	=	"registerScriptFunctions";
		static const MessageType UnloadComponent			=	"unloadComponent";

		//Animation
		static const MessageType PlayAnimation				=	"playAnimation";
		static const MessageType StartAnimation				=	"startAnimation";
		static const MessageType StopAnimation				=	"stopAnimation";
		static const MessageType GetAnimationState			=	"getAnimationState";

		//Entity
		static const MessageType AddedToComponent			=	"added_to_component";
		static const MessageType PreInitialize				=	"preInitialize";
		static const MessageType PostInitialize				=	"postInitialize";

		//Service
		static const MessageType RegisterService			=	"registerService";

		namespace General
		{
			static const MessageType MessageScene			=	"messageScene";
		}

		namespace Entity
		{
			static const MessageType CreateEntity			=	"createEntity";
			static const MessageType DestroyEntity			=	"destroyEntity";
			static const MessageType SerializeWorld			=	"serializeWorld";
			static const MessageType DeSerializeWorld		=	"deserializeWorld";
			static const MessageType LoadingStarted			=	"loadingStarted";
			static const MessageType LoadingProgress		=	"loadingProgress";
			static const MessageType LoadingFinished		=	"loadingFinished";
		}

		namespace AI
		{
			
		}

		namespace Network
		{
			static const MessageType Connect				=	"connect";
			static const MessageType Disconnect				=	"disconnect";
			static const MessageType ComponentUpdate		=	"updateComponent";
			static const MessageType NetwokSetPosition		=	"networkSetPosition";
			static const MessageType NetworkSetOrientation	=	"networkSetOrientation";
			static const MessageType CreateServer			=	"createServer";

			namespace Client
			{
				static const MessageType LevelLoaded		=	"levelLoaded";
				static const MessageType CharacterSelected	=	"characterSelelected";
				static const MessageType FindServers		=	"findServers";
				static const MessageType GetServerAd		=	"getServerAd";
			}

			namespace Server
			{
				static const MessageType ClientDisconnected	=	"clientDisconnected";
				static const MessageType WorldUpdate		=	"worldUpdate";
				static const MessageType SetServerPosition	=	"setServerPosition";
			}
		}

		namespace Input
		{
			static const MessageType GetTextForMessage				=	"getTextForMessage";
			static const MessageType GetMessageBindings				=	"getMessageBindings";
			static const MessageType SetInputAllowed				=	"setInputAllowed";
			static const MessageType SetDefaultBindingForMessage	=	"setDefaultBindingForMessage";
			static const MessageType MouseReleased					=	"mouseReleased";
			static const MessageType MousePressed					=	"mousePressed";
		}

		namespace Game
		{
			static const MessageType ChangeLevel			=	"changeLevel";
			static const MessageType GameInitialized			=	"gameInitialized";
		}

		namespace Graphics
		{
			static const MessageType ChangeResolution		=	"changeResolution";
			static const MessageType GetRenderWindow		=	"getRenderWindow";
			static const MessageType GetRootSingleton		=	"getRootSingleton";
			static const MessageType ScreenShot				=	"screenShot";
			static const MessageType SetCamera				=	"setCamera";
		}
	}
};

#endif

