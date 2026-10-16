import NIOCore
import NIOPosix
import NIOHTTP1

final class HTTPHandler: ChannelInboundHandler {
    typealias InboundIn = HTTPServerRequestPart
    typealias OutboundOut = HTTPServerResponsePart

    func channelRead(context: ChannelHandlerContext, data: NIOAny) {
        let reqPart = self.unwrapInboundIn(data)

        if case .head(let head) = reqPart {
            var headers = HTTPHeaders()
            headers.add(name: "Content-Type", value: "text/plain")
            headers.add(name: "Connection", value: "close")

            let responseHead = HTTPResponseHead(version: head.version, status: .ok, headers: headers)
            context.write(self.wrapOutboundOut(.head(responseHead)), promise: nil)

            var buffer = context.channel.allocator.buffer(capacity: 64)
            buffer.writeString("Bye, World!\n")
            context.write(self.wrapOutboundOut(.body(.byteBuffer(buffer))), promise: nil)

            context.writeAndFlush(self.wrapOutboundOut(.end(nil))).whenComplete { _ in
                context.close(promise: nil)
            }
        }
    }
}

let eventLoopGroup = MultiThreadedEventLoopGroup(numberOfThreads: 1)
defer {
    try! eventLoopGroup.syncShutdownGracefully()
}

let bootstrap = ServerBootstrap(group: eventLoopGroup)
    .serverChannelOption(ChannelOptions.socketOption(.so_reuseaddr), value: 1)
    .childChannelInitializer { channel in
        channel.pipeline.configureHTTPServerPipeline().flatMap {
            channel.pipeline.addHandler(HTTPHandler())
        }
    }

let host = "0.0.0.0"
let port = 8080

let channel = try bootstrap.bind(host: host, port: port).wait()
print("Server running on \(channel.localAddress!)...")

try channel.closeFuture.wait()

