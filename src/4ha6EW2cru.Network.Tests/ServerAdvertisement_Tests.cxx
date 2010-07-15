#include <gtest/gtest.h>
using namespace testing;

#include "ServerAdvertisement.hpp"
using namespace Network;

TEST(ServerAdvertisement_Tests, should_return_serverName)
{
  std::string expected = "server";
  ServerAdvertisement adv(expected, "", 0, 0, 0, "", 0);
  std::string result = adv.GetServerName();
  EXPECT_EQ(expected, result);
}

TEST(ServerAdvertisement_Tests, should_return_levelname)
{
  std::string expected = "level";
  ServerAdvertisement adv("", expected, 0, 0, 0, "", 0);
  std::string result = adv.GetLevelName();
  EXPECT_EQ(expected, result);
}

TEST(ServerAdvertisement_Tests, should_return_maxplayers)
{
  int expected = 10;
  ServerAdvertisement adv("", "", expected, 0, 0, "", 0);
  int result = adv.GetMaxPlayers();
  EXPECT_EQ(expected, result);
}

TEST(ServerAdvertisement_Tests, should_return_playercount)
{
  int expected = 5;
  ServerAdvertisement adv("", "", 10, expected, 0, "", 0);
  int result = adv.GetPlayerCount();
  EXPECT_EQ(expected, result);
}

TEST(ServerAdvertisement_Tests, should_return_ping)
{
  int expected = 50;
  ServerAdvertisement adv("", "", 0, 0, expected, "", 0);
  int result = adv.GetPing();
  EXPECT_EQ(expected, result);
}

TEST(ServerAdvertisement_Tests, should_return_server_address)
{
  std::string expected = "192.168.0.1";
  ServerAdvertisement adv("", "", 0, 0, 0, expected, 0);
  std::string actual = adv.GetServerAddress();
  EXPECT_EQ(expected, actual);
}

TEST(ServerAdvertisement_Tests, should_return_server_port)
{
  int expected = 8098;
  ServerAdvertisement adv("", "", 0, 0, 0, "", expected);
  int actual = adv.GetServerPort();
  EXPECT_EQ(expected, actual);
}