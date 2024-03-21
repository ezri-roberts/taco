local log = require "log"
local inspect = require "pprint"

Script = {}
Script.vars = {}

local prefix_symbols = {
	['@'] = "location",
	['-'] = "choice",
	['>'] = "jump",
	['('] = "expression",
	['{'] = "condition",
	['}'] = "condition_end",
	['#'] = "comment",
}

local function parse_line(line_str)

	local line = {}

	local first = line_str:sub(1, 1)

	-- Ignore commented lines.
	if (first == "#") then return nil end

	-- log.info(line_str)
	-- Check if its a text line.
	if (prefix_symbols[first] ~= nil) then -- Not a text line.

		line.type = prefix_symbols[first]

		if (first == "(") then

			if (line_str:sub(#line_str, #line_str) ~= ")") then

				log.fatal("Missing ')' at end of line.")
				os.exit(-1)
			end

			line.contents = line_str:sub(2, #line_str - 1)
		else

			line.contents = line_str:sub(2, #line_str)
		end

		line.contents:gsub('^%s*(.-)%s*$', '%1')

	else -- Text line.

		line.type = "text"

		local colon_pos = line_str:find(":")

		if (colon_pos ~= nil) then
			line.name = line_str:sub(1, colon_pos - 1)
			line.contents = line_str:sub(colon_pos + 1, #line_str)
				:gsub('^%s*(.-)%s*$', '%1')
		else
			line.contents = line_str
		end

	end

	-- inspect(line)
	return line
end

function Script.load(file)

	local file_data = io.open(file, "r")
	io.input(file_data)

	local contents = io.read("a*")
	-- log.info(contents)

	io.close(file_data)

	local tree = {
		["_default"] = {},
	}
	local current_location = "_default" -- Default dialogue location.
	local current_condition

	for line in contents:gmatch("[^\r\n]+") do

		line = line:gsub('^%s*(.-)%s*$', '%1') -- Remove trailing whitespace.
		local first = line:sub(1, 1)

		local line_data = parse_line(line)
		if (not line_data) then goto ignore_line end

		if (line_data.type == "location") then

			tree[line_data.contents] = {}
			current_location = line_data.contents

		else

			if (line_data.type == "expression") then

				local expr = line_data.contents:gsub("%$", "Script.vars.")
				line_data.expr = expr

				local block, err = load(expr)

				if (block) then
					block()
				end

				if (err) then
					log.error(err)
				end

			elseif (line_data.type == "condition") then

				local expr = line_data.contents:gsub("%$", "Script.vars.")
				expr = "return " .. expr

				line_data.expr = expr
				current_condition = line_data

				local block, err = load(expr)

				if (block) then
					block()
				end

				if (err) then
					log.error(err)
				end

			elseif (line_data.type == "condition_end") then
				current_condition = nil
			end

			if (current_condition) and (line_data.type ~= "condition") then
				line_data.condition = current_condition
			end

			table.insert(tree[current_location], line_data)

		end

		::ignore_line::

	end

	inspect(Script.vars)
	inspect(tree)

end

Script.load("test.script")
