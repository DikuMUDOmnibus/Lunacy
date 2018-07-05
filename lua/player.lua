
-- main player lua file

function test(ch, txt)	
	
propList = {Name = ch.name, 
            Level = ch.level}

	for k, v in pairs(propList) do
		ch:send(k .. ":" .. v)
	end


end


