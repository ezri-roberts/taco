local function choice(text, label)
	print(text)
	pcall("local function f() goto " .. label .. " end")
end

choice ("So what?", "Mad")

:: Mad ::
print ("Hey!")
