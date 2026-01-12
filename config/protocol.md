# RType project protocol documentation

# PACKET FORMAT
```
ENDIANESS : BIG
PREAMBLE : 4 BYTES : 0000
PACKETSIZE : 4 BYTES : INT  -> Size of incoming bytes to read (including code with its data)
DATETIME : NO
EOP : NO
```

---

# SENDING CODES
Every code (1 ... 255) is on ONE BYTE only

## Client codes to server

### 01 ... 19 → connexions codes
```
2   DISCONNEXION            [NO DATA]   ->  Sent from client unlink/erase connexion
4   PACKET LOSS             [1B code]   ->  Ask to send back a specific code
5   I MISSED SOMETHING      [NO DATA]   ->  Asks Server to send all datas needed
6   PING                    [NO DATA]   ->  Will be responded by 7
7   PONG                    [NO DATA]   ->  Calculate delay, it means client sent PING before
```

### 20 ... 29 → accounts codes
```
20  LOGIN   [X bytes username]      ->  Contains a username to set for user, will be responded by 22 or 25 (only alphanumerical values)
21  LOGOUT  [NO DATA]               ->  Reset username to empty
```

### 30 ... 49 → lobby codes
```
30  JOIN LOBBY          [6 bytes lobby_code]        ->  Lobby code is a 6 numbers random value created by server
31  LEAVE LOBBY         [NO DATA]                   ->  Disconnects client from lobby
32  CREATE LOBBY        [NO DATA]                   ->  Will be responded with 33, and server needs to register admin
35  ADMIN START GAME    [NO DATA]                   ->  Sent by client, server needs to check if client is admin
```

### 50 ... 69 → in game codes
```
50  CLIENT INPUTS       [1B x 102]        ->  Client inputs, just a list of booleans that correspond to keys pressed (ex: [false, false, false, true, false, true, ...])
68  ADMIN PAUSE GAME    [NO DATA]         ->  Player asks to pause the game / Player asks to play the game, responded by 37 if you are not admin, 61 if ok
```


## Server codes to client

### 01 ... 19 → connexions codes
```
1   CONNECTED                      [X times (1B code + 4B timestamp)]      ->  All codes needed in an interval
2   DISCONNEXION                   [NO DATA]                               ->  Server force disconnected client
3   ERROR TOO MANY CLIENTS         [NO DATA]                               ->  Wait and try later
6   PING                           [NO DATA]                               ->  Will be responded by 7
7   PONG                           [NO DATA]                               ->  Calculate delay, it means server sent PING before
```

### 20 ... 29 → accounts codes
```
22  LOGGED IN               [4B id]             ->  Respond to 20 if ok
23  LOGGED OUT              [4B id]             ->  Send it in responde to 21 or when  the client leaves the lobby
25  USERNAME ALREADY TAKEN  [NO DATA]           ->  Respond to 20 if username already taken
```

### 30 ... 49 → lobby codes
```
33  LOBBY CREATED   [6 bytes lobby_code]                        ->  Response to 32, send the created lobby code
34  BAD LOBBY CODE  [NO DATA]                                   ->  Respond to 30 if invalid code given
36  GAME STARTING   [NO DATA]                                   ->  Broadcast to all lobby clients
37  NOT ADMIN       [NO DATA]                                   ->  Send if client that sent 35 is not admin of the lobby
38  PLAYERS LIST    [X times (4B id + 32B username)]            ->  Send all players names, separated by \n
39  LOBBY DESTROYED [NO DATA]                                   ->  Send to all clients in the destroyed lobby
49  GAME END        [NO DATA]                                   ->  Send when game finishes, send back all clients to lobby
```

### 50 ... 69 → in game codes
**these fields have fixed size, thus do not need parsing of any kind, and values are all packet together without separators**

```
51  PLAYERS STATES      [X times (4B id + 4B x + 4B y + 8B health + 8B shield + 8B mana)]       ->  Send all players important infos
52  PLAYERS INFO        [X times (4B id + 1B weapon + 4B level + 1B status)]                    ->  Send all players less important infos
53  PROJECTILES POS     [X times (4B id + 1B type + 4B x + 4B y)]                               ->  Send all projectiles positions
54  NEW WAVE            [4B wave_id]                                                            ->  Send code to create ennemy wave
55  ENEMIES STATES      [X times (4B id + 4B x + 4B y + 8B health + 8B shield + 8B mana)]       ->  Send all enemies important infos
56  ENEMIES INFO        [X times (4B id + 1B weapon + 4B level + 1B status)]                    ->  Send all enemies less important infos
57  GAME DURATION       [4B duration]                                                           ->  Send game duration since started in seconds
58  GAME LEVEL          [4B level]                                                              ->  Send current game level
60  PLAYER DEAD         [NO DATA]                                                               ->  Client's player is dead
61  ADMIN GAME PAUSED   [NO DATA]                                                               ->  A player has set the game on pause / play
```
