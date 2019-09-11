#pragma once

#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/security/credentials_impl.h>

namespace etcd {

class ClientBase
{
public:
    // Constructors where we specify the port separately
    ClientBase(const std::vector<std::string> &nodes, unsigned int port);
    ClientBase(const std::string &single_node, unsigned int port);
    ClientBase(unsigned int port = 2379);

    // Constructors where the port is specified in nodes and single_node
    ClientBase(const std::vector<std::string> &nodes);
    ClientBase(const std::string &single_node);

    bool ConnectChannel(unsigned int connectTimeInSeconds = 5,
                        const std::shared_ptr<grpc_impl::ChannelCredentials> &creds =
                        grpc_impl::InsecureChannelCredentials());
    bool ReconnectChannel(unsigned int connectTimeInSeconds = 5);
    // void DisconnectChannel(); // probably something to do with resetting ptr.

    // Accessors
    const std::shared_ptr<grpc::ChannelInterface>& GetChannel();
    const std::vector<std::string>& GetNodes() const;

protected:
    std::shared_ptr<grpc::ChannelInterface> channel;

private:
    std::vector<std::string> mNodes;
    std::mutex mChannelMutex;
};

// Utility function to convert seconds into timespec. Needs work
gpr_timespec timeSpec(unsigned int seconds);

}
