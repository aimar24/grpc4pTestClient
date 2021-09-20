
#include <helloworld.grpc.pb.h>
#include <helloworld.pb.h>

#include <iostream>
#include <grpcPlusPromise/grpcPlusPromise.h>
#include <grpcPlusPromise/IAsyncCall.h>
#include <thread>

int main(int, char**) {
    std::cout << "Hello, world!\n";

    auto _channel_args = ::grpc::ChannelArguments();

    auto shp_channel = ::grpc::CreateCustomChannel("127.0.0.1:50051", grpc::InsecureChannelCredentials(),
                                                   _channel_args);

    GreeterClient<helloworld::Greeter> a(shp_channel);
    std::thread thread(&GreeterClient<helloworld::Greeter>::AsyncCompleteRpc ,&a);
    //AsyncCallData<helloworld::HelloReply> _reply;
    ASyncCall<AsyncCallData<helloworld::HelloReply>> *call = new ASyncCall<AsyncCallData<helloworld::HelloReply>>() ;

    helloworld::HelloRequest _req;

    auto ptr = a.call(&helloworld::Greeter::Stub::PrepareAsyncSayHello)(_req,call);

    //std::function<std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::helloworld::HelloReply>> helloworld::Greeter::Stub::* (::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq)> aaa = &helloworld::Greeter::Stub::PrepareAsyncSayHello;
////    auto ptr = a.call<helloworld::HelloRequest,ASyncCall<AsyncCallData<helloworld::HelloReply>>,helloworld::HelloReply,
////            &helloworld::Greeter::Stub::PrepareAsyncSayHello>(_req,call);

//    ptr->then([](std::any data){
//        std::cerr << "call success! \n";
//    }).then([](std::any data){
//        try
//        {
//            std::cerr << data.type().name() << "\n";
//            const auto _data = std::any_cast<ASyncCall<AsyncCallData<helloworld::HelloReply>> *>(data);
//            std::cerr << _data->_data.reply.message() << '\n';
//        }
//        catch (const std::bad_any_cast& e)
//        {
//            std::cerr << "call failed! \n";
//            std::cerr << e.what() << '\n';
//        }
//    }).error([](){
//        std::cerr << "call failed! \n";
//    });

    thread.join();
}
