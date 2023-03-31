local meta = {}

-- Create Project Data Structure
local function create()
    return setmetatable({}, meta)
end

-- Add A Single Sources File
function meta:source(...)
    for _, v in ipairs({ ... }) do
        if (type(v) ~= "string") then return error("Expected string, got " .. v); end
        table.insert(self.src, v);
    end
end

-- Add All Files in a Dir to Sources


return create
