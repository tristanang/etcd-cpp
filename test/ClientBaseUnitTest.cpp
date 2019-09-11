#include "gtest/gtest.h"
#include "ClientBase.h"

using namespace etcd;

TEST(ClientBaseUnitTest, BasicConnect)
{
    ClientBase client;

    ASSERT_TRUE(client.ConnectChannel());
    ASSERT_TRUE(client.ReconnectChannel());
}

TEST(ClientBaseUnitTest, BadFirstNode)
{
    std::vector<std::string> nodes;
    nodes.push_back("localhost:1");
    nodes.push_back("localhost:2379");
    nodes.push_back("localhost:2");

    ClientBase client(nodes);

    ASSERT_TRUE(client.ConnectChannel());
    ASSERT_TRUE(client.ReconnectChannel());
}
