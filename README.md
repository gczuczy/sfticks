# sfticks
Fun project to see how fast I can tick satisfactory belts.

Current state: Graphs are built. Growing too large for current build environment, cmake would be nice. Entity/component associations should be revised, now that I see how they are.

Regarding the implementation details, it's early to say anything, I have a bunch of ideas for this, and I yet have to see how each thing is performing.

But for sure, so far it looks like that the computation can be split up into parts suitable for parallel computation. Reason is quite simple, generally speaking, in each game there are multiple bases/plans which are connected by various transportation (wheeled, trains, drones, etc), and this means that these are not connected by any kind of belts. This means that each of these separate plans can be handled individually, not being affected by each others' belts. So based on this, multiple separate DCGs can be used to represent the ingame structure.

Apart from that, longer direct multi-segment belts can be simplified into a single virtual entity, reducing computing requirement.

Well, the graph building, optimization and execution is yet to be done, however as seeing the game data during the save's parsing, there's a lot of fun to be have here.

I would like to thank [u/AnthorNet](https://www.reddit.com/user/AnthorNet/)'s help on quite a few things around dealing with the savegame data. His help definitely saved a lot of time and effort.

# Optimization points

A quick list what I came across during implementation, possible points of optimization, what I should focus on, once basic ticking works:

 - SuperBelts: Mentioned above. This could save the FactoryConnectionInventory calls between adjecent belts.
 - Circular buffer for belt contents: This would get rid of the repeated allocation+deallocation happening during transfers
 - InventoryComponent::store() sub-implementations: Depending of the usecase of the InventoryComponent, the logic is sufficiently different to be a deterministic condition of its configurational nature. This could be optimized by splitting these implementations apart, and directly calling the needed logic.
 