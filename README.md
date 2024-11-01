# hldiscord_rpc

Haxe/HL wrapper of the Discord-RPC library

## Important Notice

#### For some reason it just stopped working, I'm already solving this problem and would welcome any help!
Note: the problem solved... itself?

The library uses UTF8 `hl.Bytes`, make sure you convert strings correctly

## Features

The so-called rich presence contains the following fields for you to fill in:

Name           | Type       | Description
-------------- | ---------- | ---------------------------------------------------------------------------------------------------
state          | hl.Bytes   | The general state the current play-session is in (Waiting, Playing, Watching some leaderboards, etc)
details        | hl.Bytes   | Details to the current play-session, like the location, or current score
startTimestamp | haxe.Int64 | Play-session start time (in seconds)
endTimestamp   | haxe.Int64 | Play-session end time (in seconds)
largeImageKey  | hl.Bytes   | Large image asset key
largeImageText | hl.Bytes   | Text displayed when hovering over a large image
smallImageKey  | hl.Bytes   | Small image asset key
smallImageText | hl.Bytes   | Text displayed when hovering over a small image
partyId        | hl.Bytes   | In-game party ID
partySize      | Int        | Number of people in the party
partyMax       | Int        | Max number of peoply in the party
matchSecret    | hl.Bytes   | _Deprecated field_
joinSecret     | hl.Bytes   | Code for other players to join the party
spectateSecret | hl.Bytes   | Code for other players to spectate the game
instance       | hl.UI8     | _Deprecated field_

## TO DO
- [x] documentation
- [ ] buttons
- [ ] fix presence content displaying