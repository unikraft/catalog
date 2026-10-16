// swift-tools-version: 6.3
import PackageDescription

import PackageDescription

let package = Package(
    name: "swift-http",
    dependencies: [
        .package(url: "https://github.com/apple/swift-nio.git", from: "2.100.0")
    ],
    targets: [
        .executableTarget(
            name: "swift-http",
            dependencies: [
                .product(name: "NIOCore", package: "swift-nio"),
                .product(name: "NIOPosix", package: "swift-nio"),
                .product(name: "NIOHTTP1", package: "swift-nio")
            ])
    ]
)

