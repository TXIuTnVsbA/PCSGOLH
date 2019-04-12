pEngine = Interfaces:GetEngine()
pEntityList = Interfaces:GetEntityList()
pLocalPlayer = null
function bhop(pcmd)
    flags = pLocalPlayer:GetFlags()
    if ((pcmd.Buttons & 2) > 0) and (not(flags & 1 > 0)) then
        pcmd.Buttons = (pcmd.Buttons & -3)
    end
end

function OnCreateMove(pcmd)
    pLocalPlayer = pEntityList:GetEntityFromIndex(pEngine:GetLocalPlayer()) --sets local player variable
    bhop(pcmd)
end

Hooks:Register(HOOK_CREATEMOVE, OnCreateMove) --createmove thing
