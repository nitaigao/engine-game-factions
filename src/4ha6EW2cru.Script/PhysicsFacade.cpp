#include "precompiled.h"

#include "PhysicsFacade.h"

#include <luabind/table_policy.hpp>
#include <luabind/operator.hpp>
using namespace luabind;

using namespace Maths;

#include "System/AnyType.hpp"
#include "System/SystemType.hpp"

#include "Service/IService.hpp"
using namespace Services;

namespace Script
{
  luabind::scope PhysicsFacade::RegisterFunctions()
  {
    return
      class_< PhysicsFacade >("PhysicsFacade")
      .def("rayQuery", &PhysicsFacade::RayQuery, copy_table(result))
      ;
  }

   std::vector< std::string > PhysicsFacade::RayQuery(const Maths::MathVector3& origin, const Maths::MathVector3& direction, float length, bool sortByDistance, int maxResults)
   {
     AnyType::AnyTypeMap parameters;

     MathVector3 originToDestination = direction - origin;
     MathVector3 destination = origin + originToDestination * length;

     parameters[ System::Parameters::Origin ] = origin;
     parameters[ System::Parameters::Destination ] = destination;
     parameters[ System::Parameters::SortByyDistance ] = sortByDistance;
     parameters[ System::Parameters::MaxResults ] = maxResults;

     /*AnyType::AnyTypeMap debugParameters;
     debugParameters[ "origin" ] = origin;
     debugParameters[ "destination" ] = destination;

     IService* renderService = Management::Get()->GetServiceManager()->FindService(System::Types::RENDER);
     renderService->MessageType("drawLine", debugParameters);*/

     IService* rayService = m_serviceManager->FindService(System::Types::PHYSICS);
     return rayService->ProcessMessage(System::Messages::RayQuery, parameters) [ "hits" ].As< std::vector< std::string > >();
   }
}