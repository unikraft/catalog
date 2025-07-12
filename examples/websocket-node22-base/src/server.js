import { WebSocketServer } from 'ws';

const port = 8080;
const wss = new WebSocketServer({ port: port });

wss.on('connection', function connection(ws, req) {
    const ip = req.socket.remoteAddress;

    console.log('Client connected from %s', ip);
    ws.send('Connection received. Waiting for messages.');

    ws.on('error', console.error);

    ws.on('message', function message(data) {
        console.log('received: %s', data);
        ws.send(data);
    });

    ws.on('close', function close() {
        console.log('Client disconnected from %s', ip);
    });
});

console.log('WebSocket server is running on ws://localhost:%d', port);
