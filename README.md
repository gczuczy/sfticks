# sfticks
Fun project to see how fast I can tick satisfactory belts.

Currently it's in the phase of parsing the dumpfile, and verifying that all the needed data is available.

Regarding the implementation details, it's early to say anything, I have a bunch of ideas for this, and I yet have to see how each thing is performing.

But for sure, so far it looks like that the computation can be split up into parts suitable for parallel computation. Reason is quite simple, generally speaking, in each game there are multiple bases/plans which are connected by various transportation (wheeled, trains, drones, etc), and this means that these are not connected by any kind of belts. This means that each of these separate plans can be handled individually, not being affected by each others' belts. So based on this, multiple separate DCGs can be used to represent the ingame structure.

Apart from that, longer direct multi-segment belts can be simplified into a single virtual entity, reducing computing requirement.

Well, the graph building, optimization and execution is yet to be done, however as seeing the game data during the save's parsing, there's a lot of fun to be have here.

