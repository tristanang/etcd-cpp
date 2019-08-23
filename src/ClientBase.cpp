#include "ClientBase.h"

namespace etcd
{

// Constructors
ClientBase::ClientBase(const std::vector<std::string> &nodes, unsigned int port)
{
    for (const std::string &node : nodes)
        mNodes.push_back(node + ":" + std::to_string(port));
}

ClientBase::ClientBase(const std::string &single_node, unsigned int port)
{
    mNodes.push_back(single_node + ":" + std::to_string(port));
}

ClientBase::ClientBase(unsigned int port)
{
    mNodes.push_back("localhost:" + std::to_string(port));
}

ClientBase::ClientBase(const std::vector<std::string> &nodes)
{
    for (const std::string &node : nodes)
        mNodes.push_back(node);
}

ClientBase::ClientBase(const std::string &single_node)
{
    mNodes.push_back(single_node);
}

// Channel Connection Methods
bool ClientBase::ConnectChannel(
    unsigned int connectTime,
    const std::shared_ptr<grpc::ChannelCredentials> &creds)
{
    std::lock_guard<std::mutex> lock(mChannelMutex);

    for (const auto &host : mNodes)
    {
        channel = grpc::CreateChannel(host, creds);

        if (!channel->WaitForConnected(timeSpec(connectTime))) continue;

        return true;
    }

    return false;
}

bool ClientBase::ReconnectChannel(unsigned int connectTime)
{
    std::lock_guard<std::mutex> lock(mChannelMutex);
    channel->GetState(true);

    return channel->WaitForConnected(timeSpec(connectTime));
}

gpr_timespec timeSpec(unsigned int seconds)
{
    return gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                        gpr_time_from_seconds(seconds, GPR_TIMESPAN));
}

}
