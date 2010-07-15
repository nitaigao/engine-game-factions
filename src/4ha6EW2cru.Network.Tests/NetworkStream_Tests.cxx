#include <gtest/gtest.h>
using namespace testing;

#include "NetworkStream.h"
using namespace Network;

#include <BitStream.h>
using namespace RakNet;

#include "Maths/MathVector3.hpp"
#include "Maths/MathQuaternion.hpp"
using namespace Maths;

class NetworkStream_Tests : public TestHarness<NetworkStream>
{

protected:

  BitStream* m_underlyingStream;

  void EstablishContext()
  {
    m_underlyingStream = new BitStream();
  }


  void DestroyContext()
  {
    delete m_underlyingStream;
  }

  NetworkStream* CreateSubject()
  {
    return new NetworkStream(m_underlyingStream); 
  }
};


TEST_F(NetworkStream_Tests, should_write_strings_to_the_underlying_bit_stream)
{
  std::string expected = "test";

  m_subject->Write(expected);

  RakString result;
  m_underlyingStream->Read(result);

  EXPECT_EQ(expected, result.C_String());
}


TEST_F(NetworkStream_Tests, should_write_integers_to_the_underlying_bit_stream)
{
  int expected = 99;

  m_subject->Write(expected);

  int result;
  m_underlyingStream->Read(result);

  EXPECT_EQ(expected, result);
}

TEST_F(NetworkStream_Tests, should_read_strings_from_the_underlying_bit_stream)
{
  std::string expected = "hello";

  m_underlyingStream->Write(RakString(expected));

  std::string result;
  m_subject->Read(result);

  EXPECT_EQ(expected, result);
}

TEST_F(NetworkStream_Tests, should_read_integers_from_the_underlying_bit_stream)
{
  int expected = 99;

  m_underlyingStream->Write(expected);

  int result;
  m_subject->Read(result);

  EXPECT_EQ(expected, result);
}

TEST_F(NetworkStream_Tests, should_write_vectors_to_the_underlying_bit_stream)
{
  MathVector3 expected = MathVector3::Forward();

  m_subject->Write(expected);

  MathVector3 result;
  m_underlyingStream->Read(result.X);
  m_underlyingStream->Read(result.Y);
  m_underlyingStream->Read(result.Z);

  EXPECT_EQ(expected, result);
}

TEST_F(NetworkStream_Tests, should_read_vectors_from_the_underlying_bit_stream)
{
  float X = 1.0f;
  float Y = 2.0f;
  float Z = 3.0f;

  m_underlyingStream->Write(X);
  m_underlyingStream->Write(Y);
  m_underlyingStream->Write(Z);

  MathVector3 result;
  m_subject->Read(result);

  EXPECT_EQ(X, result.X);
  EXPECT_EQ(Y, result.Y);
  EXPECT_EQ(Z, result.Z);
}


TEST_F(NetworkStream_Tests, should_write_quaternions_to_the_underlying_bit_stream)
{
  MathQuaternion expected = MathQuaternion(1.0f, 2.0f, 3.0f, 4.0f);

  m_subject->Write(expected);

  MathQuaternion result;
  m_underlyingStream->Read(result.X);
  m_underlyingStream->Read(result.Y);
  m_underlyingStream->Read(result.Z);
  m_underlyingStream->Read(result.W);

  EXPECT_EQ(expected, result);
}

TEST_F(NetworkStream_Tests, should_read_quaternions_from_the_underlying_stream)
{
  float X = 1.0f;
  float Y = 2.0f;
  float Z = 3.0f;
  float W = 4.0f;

  m_underlyingStream->Write(X);
  m_underlyingStream->Write(Y);
  m_underlyingStream->Write(Z);
  m_underlyingStream->Write(W);

  MathQuaternion result;
  m_subject->Read(result);

  EXPECT_EQ(X, result.X);
  EXPECT_EQ(Y, result.Y);
  EXPECT_EQ(Z, result.Z);
  EXPECT_EQ(W, result.W);
}