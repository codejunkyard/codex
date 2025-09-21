const net = require("net");

const PORT = 5002;
let peers = [];

// Handle incoming connections
const server = net.createServer((socket) => {
  console.log("Peer connected:", socket.remoteAddress + ":" + socket.remotePort);
  peers.push(socket);

  socket.on("data", (data) => {
    console.log("Received:", data.toString());
    // Broadcast to other peers
    peers.forEach((p) => {
      if (p !== socket) p.write(data);
    });
  });

  socket.on("close", () => {
    console.log("Peer disconnected");
    peers = peers.filter((p) => p !== socket);
  });
});

server.listen(PORT, () => {
  console.log(`Listening on port ${PORT}`);
});

// Connect to a peer
const readline = require("readline").createInterface({
  input: process.stdin,
  output: process.stdout,
});

readline.question("Connect to peer (host:port) or leave empty: ", (answer) => {
  if (answer) {
    const [host, port] = answer.split(":");
    const socket = net.createConnection({ host, port: Number(port) }, () => {
      console.log("Connected to peer");
      peers.push(socket);
    });

    socket.on("data", (data) => {
      console.log("Received:", data.toString());
    });
  }

  // Send messages
  readline.on("line", (line) => {
    peers.forEach((p) => p.write(line));
  });
});
