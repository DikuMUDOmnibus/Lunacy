


-- local terrain types
local FOREST   = "{G;{D"
local WATER    = "{B~{D"
local MOUNTAIN = "{y^{D"

-- local character types
local PLAYER = "{M@{D"
local MOB    = "{r@{D"

-- obvious
endLine = "\r\n" 

-- main map constructor
map = {
a1={t=" ",c=" "}, a2={t=" ",c=" "}, a3={t=" ",c=" "}, a4={t=" ",c=" "}, a5={t=" ",c=" "},
b1={t=" ",c=" "}, b2={t=" ",c=" "}, b3={t=" ",c=" "}, b4={t=" ",c=" "},
c1={t=" ",c=" "}, c2={t=" ",c=" "}, c3={t=" ",c=" "}, c4={t=" ",c=" "}, c5={t=" ",c=" "},
d1={t=" ",c=" "}, d2={t=" ",c=" "}, d3={t=" ",c=" "}, d4={t=" ",c=" "},
e1={t=" ",c=" "}, e2={t=" ",c=" "}, e3={t=" ",c=" "}, e4={t=" ",c=" "}, e5={t=" ",c=" "},
f1={t=" ",c=" "}, f2={t=" ",c=" "}, f3={t=" ",c=" "}, f4={t=" ",c=" "},
g1={t=" ",c=" "}, g2={t=" ",c=" "}, g3={t=" ",c=" "}, g4={t=" ",c=" "}, g5={t=" ",c=" "},
h1={t=" ",c=" "}, h2={t=" ",c=" "}, h3={t=" ",c=" "}, h4={t=" ",c=" "},
i1={t=" ",c=" "}, i2={t=" ",c=" "}, i3={t=" ",c=" "}, i4={t=" ",c=" "}, i5={t=" ",c=" "},
} 

map.a1.t = FOREST
map.a2.t = FOREST
map.a3.t = MOUNTAIN
map.a4.t = MOUNTAIN
map.a5.t = MOUNTAIN
map.c1.t = FOREST
map.c3.t = WATER
map.e4.t = FOREST
map.e3.t = FOREST
map.e3.c = PLAYER 
map.b1.t = FOREST
map.b1.c = MOB
map.b2.c = MOB
map.b3.t = WATER
map.b4.t = WATER
map.c4.t = WATER
map.c5.t = WATER

map.g3.t = MOUNTAIN
map.g3.c = MOB
map.d3.t = WATER
map.d4.t = WATER
map.d2.t = FOREST

map.c2.t = FOREST
map.b2.t = FOREST

-- drawMap()
-- main drawing function, returns a string of current map values
function drawMap()
	bMap = "\r\n"
	bMap = bMap .. "{Bo--------------------------------o{D" .. endLine
	bMap = bMap .. "{B|{D   __    __    __    __    __   {B|{D" .. endLine
	bMap = bMap .. "{B|{D  /"..map.a1.t .. map.a1.c .."\\__/"..map.a2.t .. map.a2.c .."\\__/"..map.a3.t .. map.a3.c
	bMap = bMap .. "\\__/"..map.a4.t .. map.a4.c .."\\__/"..map.a5.t .. map.a5.c .."\\  {B|{D"..endLine
	bMap = bMap .. "{B|{D  \\__/"..map.b1.t .. map.b1.c .."\\__/"..map.b2.t .. map.b2.c .."\\__/"..map.b3.t .. map.b3.c
	bMap = bMap .. "\\__/"..map.b4.t .. map.b4.c .."\\__/  {B|{D" .. endLine
	bMap = bMap .. "{B|{D  /"..map.c1.t .. map.c1.c .."\\__/"..map.c2.t .. map.c2.c .."\\__/"..map.c3.t .. map.c3.c
	bMap = bMap .. "\\__/"..map.c4.t .. map.c4.c .."\\__/"..map.c5.t .. map.c5.c .."\\  {B|{D"..endLine
	bMap = bMap .. "{B|{D  \\__/"..map.d1.t .. map.d1.c .."\\__/"..map.d2.t .. map.d2.c .."\\__/"..map.d3.t .. map.d3.c
	bMap = bMap .. "\\__/"..map.d4.t .. map.d4.c .."\\__/  {B|{D" .. endLine
	bMap = bMap .. "{B|{D  /"..map.e1.t .. map.e1.c .."\\__/"..map.e2.t .. map.e2.c .."\\__/"..map.e3.t .. map.e3.c 
	bMap = bMap .. "\\__/"..map.e4.t .. map.e4.c .."\\__/"..map.e5.t .. map.e5.c .."\\  {B|{D"..endLine
	bMap = bMap .. "{B|{D  \\__/"..map.f1.t .. map.f1.c .."\\__/"..map.f2.t .. map.f2.c .."\\__/"..map.f3.t .. map.f3.c 
	bMap = bMap .. "\\__/"..map.f4.t .. map.f4.c .."\\__/  {B|{D" .. endLine
	bMap = bMap .. "{B|{D  /"..map.g1.t .. map.g1.c .."\\__/"..map.g2.t .. map.g2.c .."\\__/"..map.g3.t .. map.g3.c
	bMap = bMap .. "\\__/"..map.g4.t .. map.g4.c .."\\__/"..map.g5.t .. map.g5.c .."\\  {B|{D"..endLine
	bMap = bMap .. "{B|{D  \\__/"..map.h1.t .. map.h1.c .."\\__/"..map.h2.t .. map.h2.c .."\\__/"..map.h3.t .. map.h3.c
	bMap = bMap .. "\\__/"..map.h4.t .. map.h4.c .."\\__/  {B|{D" .. endLine
	bMap = bMap .. "{B|{D  /"..map.i1.t .. map.i1.c .."\\__/"..map.i2.t .. map.i2.c .."\\__/"..map.i3.t .. map.i3.c
	bMap = bMap .. "\\__/"..map.i4.t .. map.i4.c .."\\__/"..map.i5.t .. map.i5.c .."\\  {B|{D"..endLine
	bMap = bMap .. "{B|{D  \\__/  \\__/  \\__/  \\__/  \\__/  {B|{D" .. endLine
	bMap = bMap .. "{B|                                |" .. endLine
	bMap = bMap .. "o--------------------------------o{D" 
return bMap
end


function do_battle(ch, argument)
	ch:send(drawMap())
end

