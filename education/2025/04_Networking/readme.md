## HTTP at a high level
User A sends a request to User B,
User A receives a response from User B

### Message flow -> Request/Response
Send a message
Receive messages

### Server Application
Ability to send a message
Ability to receive a message

```
HTTP[UserA] >===[o]====[o]=[o]======[o]=> HTTP[UserB]
HTTP[UserA] <======[o]=========[o]======< HTTP[UserB]
```

### Client-Server Network:

    [c]       [c]
       \     /
        \   /
[c]------[S]------[c]
        /   \
       /     \
    [c]       [c]

### Peer-to-Peer (P2P) Network:

         [o]
        / | \
       /  |  \
    [o]-------[o]
       \  |  /
        \ | /
         [o]