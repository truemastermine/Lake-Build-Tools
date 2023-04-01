local meta = {}

-- Create Project Data Structure
--------------------------------
local function create(lang)
    local temp = {
        lang = lang,
        src = {},
        incs = {},
        defs = {},
        lnks = {},
    }

    return setmetatable(temp, meta)
end

function meta:version(ver)
end

-- Build
--------

local function StaticLib(project)
end

function meta:build(out)
    for _, ln in ipairs(self.lnks) do
    end
end

-- Add Source Files
-------------------
function meta:source(...)
    for _, v in ipairs({ ... }) do
        if (type(v) ~= "string") then return error("Usage: project:source(file...: string)"); end
        table.insert(self.src, v);
    end
end

function meta:sourceDir(dir, ext)
    local srcF = API.listDir(dir, ext)
    for _, f in ipairs(srcF) do
        table.insert(self.src, f)
    end
end

-- Include Dirs
---------------
function meta:includeDir(...)
    for _, v in ipairs({ ... }) do
        if type(v) ~= "string" then error("Usage: project:includeDir(dir...: string)") end
        table.insert(self.incs, v)
    end
end

-- Link Other Projects
----------------------

local function l(par, chi, t)
    if par == chi then error("Link targets Parent and Child are the same!") end

    if t == "shared" then
        table.insert(par.lnks, { chi, true }) -- Not yet supported
    else                                      -- MODULE?
        table.insert(par.lnks, { chi })
    end
end

function meta:link(t, ...)
    if t and type(t) ~= "string" then
        l(self, t)
        t = nil
    end

    for _, v in ipairs({ ... }) do
        l(self, v, t)
    end
end

-- Define & Undefine
--------------------
function meta:define(key)
    table.insert(self.defs, key)
end

-- Tests
--------

function meta:testDir(dir)
end

function meta:buildTest() -- ?????
end

return create
