
TO_ROOM = 0

function do_color(txt)
	buf = txt
	colors = {}
	-- light fg colors
	colors["{x"] = "\27[0m"
	colors["{r"] = "\27[0;31m"
	colors["{g"] = "\27[0;32m"
	colors["{y"] = "\27[0;33m"
	colors["{b"] = "\27[0;34m"
	colors["{m"] = "\27[0;35m"
	colors["{c"] = "\27[0;36m"
	colors["{w"] = "\27[0;37m"
	colors["{d"] = "\27[1;30m"
	-- dark fg colors
	colors["{R"] = "\27[1;31m"
	colors["{G"] = "\27[1;32m"
	colors["{Y"] = "\27[1;33m"
	colors["{B"] = "\27[1;34m"
	colors["{M"] = "\27[1;35m"
	colors["{C"] = "\27[1;36m"
	colors["{W"] = "\27[1;37m"
	colors["{D"] = "\27[1;30m"
	-- light bg colors
	colors["#R"] = "\27[1;41m"
	colors["#G"] = "\27[1;42m"
	colors["#Y"] = "\27[1;43m"
	colors["#B"] = "\27[1;44m"
	colors["#M"] = "\27[1;45m"
	colors["#C"] = "\27[1;46m"
	colors["#W"] = "\27[1;47m"
	colors["#D"] = "\27[1;40m"
	-- dark  bg colors
	colors["#r"] = "\27[0;41m"
	colors["#g"] = "\27[0;42m"
	colors["#y"] = "\27[0;43m"
	colors["#b"] = "\27[0;44m"
	colors["#m"] = "\27[0;45m"
	colors["#c"] = "\27[0;46m"
	colors["#w"] = "\27[0;47m"
	colors["#d"] = "\27[0;40m"

	for k,v in pairs(colors) do buf = string.gsub(buf, k, v) end
	return buf
end


	



