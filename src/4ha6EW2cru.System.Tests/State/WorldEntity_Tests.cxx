#include <gtest/gtest.h>
using namespace testing;

#include "State/WorldEntity.h"
using namespace State;

#include "../Mocks/MockStream.h"
#include "../Mocks/MockSystemComponent.hpp"

#include "Maths/MathVector3.hpp"
#include "Maths/MathQuaternion.hpp"
using namespace Maths;

class WorldEntity_Tests : public TestHarness< WorldEntity >
{

protected:

  std::string m_entityName;

  void EstablishContext()
  {
    m_entityName = "test";
  }


  void DestroyContext()
  {

  }

  WorldEntity* CreateSubject()
  {
    return new WorldEntity(m_entityName);
  }
};

TEST_F(WorldEntity_Tests, should_serialize_an_entity_with_a_name)
{
  MockStream stream;
  EXPECT_CALL(stream, Write(m_entityName));
  EXPECT_CALL(stream, Write(A< int >()));
  EXPECT_CALL(stream, Write(""));

  m_subject->Serialize(&stream);
}

TEST_F(WorldEntity_Tests, should_serialize_an_entity_with_a_type_attribute)
{
  std::string type = "test";

  MockStream stream;
  EXPECT_CALL(stream, Write(A< const std::string& >()))
    .Times(2);

  EXPECT_CALL(stream, Write(1)); 

  m_subject->SetAttribute(System::Attributes::EntityType, type);
  m_subject->Serialize(&stream);
}

TEST_F(WorldEntity_Tests, should_serialize_sub_components)
{
  MockStream stream;

  MockSystemComponent component;
  EXPECT_CALL(component, Observe(0, A< const System::MessageType& >(), A< AnyType::AnyTypeMap >())).WillOnce(Return(AnyType()));
  EXPECT_CALL(component, Serialize(&stream));

  m_subject->SetAttribute(System::Attributes::EntityType, "something");
  m_subject->AddComponent(&component);
  m_subject->Serialize(&stream);
}

void ReturnSystem(int& data) { data = (int) System::Types::GEOMETRY; };

TEST_F(WorldEntity_Tests, should_deserialize_subcomponents)
{
  MockStream stream;

  EXPECT_CALL(stream, Read(An< int& >())).WillOnce(Invoke(ReturnSystem)); 

  AnyType::AnyTypeMap attributes;
  attributes[ System::Attributes::SystemType ] = System::Types::GEOMETRY;

  MockSystemComponent component;
  EXPECT_CALL(component, GetAttributes()).WillOnce(Return(attributes));
  EXPECT_CALL(component, Observe(0, A< const System::MessageType& >(), A< AnyType::AnyTypeMap >())).WillOnce(Return(AnyType()));
  EXPECT_CALL(component, DeSerialize(&stream));

  m_subject->AddComponent(&component);
  m_subject->DeSerialize(&stream);
}