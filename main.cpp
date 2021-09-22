
#include <helloworld.grpc.pb.h>
#include <helloworld.pb.h>

#include <grpcPlusPromise/grpcPlusPromise.h>
#include <grpcPlusPromise/IAsyncCall.h>

#include <iostream>
#include <thread>

int main(int, char**) {

    auto _channel_args = ::grpc::ChannelArguments();

    auto shp_channel = ::grpc::CreateCustomChannel("127.0.0.1:50051", grpc::InsecureChannelCredentials(),
                                                   _channel_args);

    GrcpPlusPromise<helloworld::Greeter> asyncGrpc(shp_channel);
    std::thread thread(&GrcpPlusPromise<helloworld::Greeter>::AsyncCompleteRpc ,&asyncGrpc);
    ASyncCall<AsyncCallData<helloworld::HelloReply>> *call = new ASyncCall<AsyncCallData<helloworld::HelloReply>>() ;

    helloworld::HelloRequest _req;

    auto ptr = asyncGrpc.call(&helloworld::Greeter::Stub::PrepareAsyncSayHello)(_req,call);


    ptr->then([](std::any data){
        std::cerr << "call success! \n";
    }).then([](std::any data){
        try
        {
            const auto _data = std::any_cast<ASyncCall<AsyncCallData<helloworld::HelloReply>> *>(data);
            std::cerr << _data->_data.reply.message() << '\n';
        }
        catch (const std::bad_any_cast& e)
        {
            std::cerr << "call failed! \n";
            std::cerr << e.what() << '\n';
        }
    }).error([](){
        std::cerr << "call failed! \n";
    });

    thread.join();
}
