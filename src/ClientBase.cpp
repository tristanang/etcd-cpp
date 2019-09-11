#include "ClientBase.h"
#include <grpc++/grpc++.h>

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
    const std::shared_ptr<grpc_impl::ChannelCredentials> &creds)
{
    std::lock_guard<std::mutex> lock(mChannelMutex);

    for (const std::string &host : mNodes)
    {
        channel = grpc::CreateChannel(host, creds);

        if (!channel->WaitForConnected(timeSpec(connectTime))) continue;

        return true;
    }

    return false;
}

bool ClientBase::ReconnectChannel(unsigned int connectTime)
{
    if (!channel) ConnectChannel(connectTime);

    std::lock_guard<std::mutex> lock(mChannelMutex);
    channel->GetState(true);

    return channel->WaitForConnected(timeSpec(connectTime));
}

const std::shared_ptr<grpc::ChannelInterface>& ClientBase::GetChannel()
{
    std::lock_guard<std::mutex> lock(mChannelMutex);
    return channel;
}

const std::vector<std::string>& ClientBase::GetNodes() const
{
    return mNodes;
}

gpr_timespec timeSpec(unsigned int seconds)
{
    return gpr_time_add(gpr_now(GPR_CLOCK_REALTIME),
                        gpr_time_from_seconds(seconds, GPR_TIMESPAN));
}

}
