
mobProps = {
{p="name",  lbl="  Name: ", typ="string"},
{p="title", lbl=" Title:" , typ="Fstring"},
{p="level", lbl=" Level: ", typ="number"},
{p="short", lbl=" Short: ", typ="Fstring"},
{p="long",  lbl="  Long: ", typ="Fstring"},
{p="desc",  lbl="  Desc: ", typ="Fstring"}
}

-- multiArgs(string)
-- returns a table of arguments split by white space
local function multiArgs(str)
	t = {}
	string.gsub(str, "(%w+)", function(w) table.insert(t, w) end)
	return t
end

-- longArg(list)
-- returns a string which is each word in an argument list but the
-- first, which is usually the command.
local function longArg(args)
	arg2 = ""
	
	for i,w in ipairs(args) do 
		if i > 1 then 
			if i == #args then
				arg2 = arg2 .. w
			else
				arg2 = arg2 .. w .. " "
			end
		end
	end

	return arg2
end

-- wrap things up with the olc session
local function quit(ch, olcObject)
	ch:quitOlc()
	olcObject = nil
end

-- generic property handler for all modes: 
-- (R-EDIT, M-EDIT, O-EDIT) etc.
local function setProp(ch, obj, list, argument)
	
	args = multiArgs(argument)
	arg2 = longArg(args)

	for k,v in pairs(list) do
		if args[1] == v.p then
			
			if v.typ == "string" or v.typ == "number" then
				obj[v.p] = args[2]
				ch:send("Set the value of " .. v.p .. " to: " .. args[2])
				return true
			end

			if v.typ == "Fstring" then
				obj[v.p] = arg2
				ch:send("Set the value of " .. v.p .. " to: " .. arg2)
				return true
			end

		end

	end
	-- if we made it this far, then we weren't able to find
	-- a matching property in our generic obj
	return false
end

function olcMedit(ch, argument)
	
	if argument == " " then
		ch:send("#B---- M-EDIT ----{w\r\n")
		for k,v in pairs(mobProps) do
			ch:send(v.lbl .. ch[v.p])
		end
		return
	end

	if argument == "done" then
		ch:send("{gQuitting R-EDIT{w")
		quit(ch, argument)	
		return
	end

	-- checks our generic setProp routine that takes
	-- any list of properties, if returns true then we are done here
	if setProp(ch, ch, mobProps, argument) then
		return
	else
		ch:send("That is not an M-EDIT command or property")
	end


end
