--! Last updated 2025-07-19
[cite_start]repeat wait() until game.Loaded and game:GetService'Players'.LocalPlayer [cite: 1]
[cite_start]local Version = '1.82' [cite: 1]
[cite_start]local plrs = game:GetService'Players' [cite: 1]
[cite_start]local plr = plrs.LocalPlayer [cite: 1]
[cite_start]local vec0 = Vector3.new() [cite: 1]
[cite_start]local prop1000 = PhysicalProperties.new(1000,1000,0,1000,0) [cite: 1]
[cite_start]local cf0 = CFrame.new() [cite: 1]

local Settings = {
    [cite_start]['Autofarm'] = false, [cite: 1]
    [cite_start]['AutoPunch'] = false, [cite: 1]
    [cite_start]['SuperPunch'] = false, [cite: 1]
    [cite_start]['Virus'] = false, [cite: 1]
    [cite_start]['AntiAnvil'] = false, [cite: 1]
    [cite_start]['FakeAccs'] = false, [cite: 1]
    [cite_start]['AntiSpinner'] = false, [cite: 1]
    [cite_start]['AntiPunch'] = false, [cite: 1]
    [cite_start]['AntiFling'] = false, [cite: 1]
    [cite_start]['AntiVelocity'] = false, [cite: 1]
    [cite_start]['LessPing'] = false [cite: 1]
}

[cite_start]local mouse = plr:GetMouse() [cite: 1]
[cite_start]local rs = game:GetService'RunService' [cite: 1]
[cite_start]local pinga [cite: 1]
[cite_start]local points [cite: 2]
[cite_start]local vim = game:GetService'VirtualInputManager' [cite: 2]
[cite_start]local LoopFlingV1 = {} [cite: 2]
[cite_start]local LoopFlingV2 = {} [cite: 2]
[cite_start]local ts = game:GetService'TweenService' [cite: 2]
[cite_start]local duping = false [cite: 2]

local function findplr(Target)
    if game:GetService'Players':FindFirstChild(Target) then
        return game:GetService'Players':FindFirstChild(Target)
    else
        if Target ~= nil and Target ~= "" and Target ~= " " and Target then
            [cite_start]local name = Target [cite: 2]
            [cite_start]local found = false [cite: 2]
            [cite_start]for _,v in pairs(game:GetService'Players':GetPlayers()) do [cite: 3]
                [cite_start]if not found and (v.Name:lower():sub(1,#name) == name:lower() or v.DisplayName:lower():sub(1,#name) == name:lower()) then [cite: 3]
                    [cite_start]name = v [cite: 3]
                    [cite_start]found = true [cite: 3]
                end
            [cite_start]end [cite: 4]
            [cite_start]if name ~= nil and name ~= Target then [cite: 4]
                [cite_start]return name [cite: 4]
            end
        end
    end
end
pcall(function()
    [cite_start]if game:GetService('CoreGui'):FindFirstChild('PingGui') then [cite: 4]
        [cite_start]ping = game:GetService('CoreGui').PingGui.p [cite: 4]
    else
        [cite_start]local pinggui = Instance.new('ScreenGui',game:GetService('CoreGui')) [cite: 4]
        [cite_start]pinggui.Name = 'PingGui' [cite: 5]
        [cite_start]pinggui.ResetOnSpawn = false [cite: 5]
        [cite_start]ping = Instance.new('TextLabel',pinggui) [cite: 5]
        [cite_start]ping.Name = 'p' [cite: 5]
        [cite_start]ping.Text = 'Loading...' [cite: 5]
        [cite_start]ping.Size = UDim2.new(0,150,0,25) [cite: 5]
        [cite_start]ping.Position = UDim2.new(0,0,0.85,0) [cite: 5]
        [cite_start]Instance.new('UICorner',ping) [cite: 5]
        ping.BackgroundColor3 = Color3.fromRGB(0,0,0) -- Changed to black
        [cite_start]ping.BackgroundTransparency = 0.7 [cite: 5]
        [cite_start]ping.TextScaled = true [cite: 6]
        [cite_start]ping.Visible = false [cite: 6]
    end
end)
pcall(function()
    [cite_start]if game:GetService('CoreGui'):FindFirstChild('PointsGui') then [cite: 6]
        [cite_start]ping = game:GetService('CoreGui').PointsGui.p [cite: 6]
    else
        [cite_start]local pointsgui = Instance.new('ScreenGui',game:GetService('CoreGui')) [cite: 6]
        [cite_start]pointsgui.Name = 'PointsGui' [cite: 6]
        [cite_start]pointsgui.ResetOnSpawn = false [cite: 6]
        [cite_start]points = Instance.new('TextLabel',pointsgui) [cite: 6]
        [cite_start]points.Name = 'p' [cite: 6]
        [cite_start]points.Text = 'Loading...' [cite: 7]
        [cite_start]points.Size = UDim2.new(0,150,0,25) [cite: 7]
        [cite_start]points.Position = UDim2.new(0,0,0.85,50) [cite: 7]
        [cite_start]Instance.new('UICorner',points) [cite: 7]
        points.BackgroundColor3 = Color3.fromRGB(0,0,0) -- Changed to black
        [cite_start]points.BackgroundTransparency = 0.7 [cite: 7]
        [cite_start]points.TextScaled = true [cite: 7]
        [cite_start]points.Visible = false [cite: 7]
    end
end)
spawn(function()
    [cite_start]while true do wait() [cite: 7]
        pcall(function()
            [cite_start]local pingv = string.split(string.split(game.Stats.Network.ServerStatsItem['Data Ping']:GetValueString(), ' ')[1], '.') [cite: 8]
            [cite_start]ping.Text = 'Ping: '..pingv[1] [cite: 8]
        end)
        pcall(function()
            [cite_start]points.Text = 'Points: '..plr.leaderstats['Bully Points'].Value [cite: 8]
        end)
    end
end)
[cite_start]local punched = false [cite: 8]
[cite_start]local punch_anim = Instance.new('Animation') [cite: 8]
[cite_start]punch_anim.Name = 'FakePunch' [cite: 8]
[cite_start]punch_anim.AnimationId = 'rbxassetid://5193683418' [cite: 8]
mouse.KeyDown:Connect(function(key)
    [cite_start]if key == 'v' then [cite: 8]
        pcall(function()
            [cite_start]if plr.Character.Picked.Value then [cite: 9]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 9]
            end
            [cite_start]plr.Character.Picking:FireServer(mouse.Target,Vector3.new(math.huge,-math.huge,math.huge)) [cite: 9]
            [cite_start]wait(0.1) [cite: 9]
            [cite_start]plr.Character.PuttingDown:FireServer() [cite: 9]
        end)
    [cite_start]elseif key == 'b' then [cite: 9]
        pcall(function()
            [cite_start]if mouse.Target:FindFirstAncestorOfClass('Model') and mouse.Target:FindFirstAncestorOfClass('Model'):FindFirstChild('ArmAngleChange') then [cite: 10]
                [cite_start]mouse.Target:FindFirstAncestorOfClass('Model').ArmAngleChange:FireServer(CFrame.new(math.huge,math.huge,math.huge)) [cite: 10]
           end
        end)
    [cite_start]elseif key == 'q' then [cite: 10]
        pcall(function()
            [cite_start]if not plr.Character.Picked.Value then [cite: 10]
                [cite_start]plr.Character.Picking:FireServer(mouse.Target,mouse.Hit.p) [cite: 10]
            [cite_start]else [cite: 11]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 11]
            end
        end)
    [cite_start]elseif key == ' ' then [cite: 11]
        pcall(function()
            [cite_start]plr.Character:FindFirstChildOfClass('Humanoid').Jump = true [cite: 11]
        end)
    [cite_start]elseif key == 'e' and Settings['SuperPunch'] then [cite: 11]
        [cite_start]punched = true [cite: 11]
        [cite_start]pcall(function() [cite: 12]
            [cite_start]plr.Character.Humanoid:LoadAnimation(punch_anim):Play() [cite: 12]
        end)
        [cite_start]wait(0.3) [cite: 12]
        [cite_start]punched = false [cite: 12]
    end
end)

[cite_start]local connections_AutoPunch = {} [cite: 12]
[cite_start]local connections_SuperPunch = {} [cite: 12]
[cite_start]local connections_V = {} [cite: 12]

function connect_AP()
    table.insert(connections_AutoPunch,plr.Character.HumanoidRootPart.Touched:Connect(function(hit)
        [cite_start]if plr.Character:FindFirstChild('Punch') and hit.Parent:FindFirstChildOfClass('Humanoid') and hit.Parent~=plr.Character then [cite: 12]
            [cite_start]local char = hit.Parent [cite: 12]
            [cite_start]pcall(function() [cite: 13]
                [cite_start]plr.Character.Punch:Activate() [cite: 13]
                [cite_start]firetouchinterest(plr.Character.RightHand,char.Head,0) [cite: 13]
                [cite_start]firetouchinterest(plr.Character.RightHand,char.Head,1) [cite: 13]
            end)
        end
    end))
end
function connect_SP()
    table.insert(connections_SuperPunch,plr.Character.RightHand.Touched:Connect(function(hit)
        pcall(function()
            [cite_start]if punched and hit.Parent:FindFirstChildOfClass('Humanoid') then [cite: 14]
                [cite_start]local char = hit.Parent [cite: 14]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 14]
                [cite_start]plr.Character.Picking:FireServer(char.HumanoidRootPart,Vector3.new(math.huge,math.huge,math.huge)) [cite: 14]
                [cite_start]char.ArmAngleChange:FireServer(CFrame.new(9e38,-9e38,9e38)) [cite: 14]
                [cite_start]wait(0.1) [cite: 14]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 15]
            [cite_start]elseif punched and hit:IsA('BasePart') and not hit.Anchored and not hit:IsDescendantOf(plr.Character) then [cite: 15]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 15]
                [cite_start]plr.Character.Picking:FireServer(hit,Vector3.new(math.huge,math.huge,math.huge)) [cite: 15]
                [cite_start]wait(0.1) [cite: 15]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 15]
            [cite_start]end [cite: 16]
        end)
    end))
end
function infect(v)
    table.insert(connections_V,v.Touched:Connect(function(hit)
        pcall(function()
            [cite_start]if hit.Parent:FindFirstChildOfClass('Humanoid') then [cite: 16]
                [cite_start]local infected = hit.Parent [cite: 16]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 16]
                [cite_start]plr.Character.Picking:FireServer(infected.HumanoidRootPart,Vector3.new(math.huge,math.huge,math.huge)) [cite: 16]
                [cite_start]infected.ArmAngleChange:FireServer(CFrame.new(9e38,-9e38,9e38)) [cite: 17]
                [cite_start]wait(0.1) [cite: 17]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 17]
            end
        end)
    end))
end
plr.CharacterAdded:Connect(function()
    [cite_start]if Settings['AutoPunch'] then [cite: 17]
        [cite_start]pcall(function() [cite: 17]
            [cite_start]for _,v in next,connections_AutoPunch do [cite: 17]
                [cite_start]if typeof(v) == 'RBXScriptConnection' then [cite: 18]
                    [cite_start]v:Disconnect() [cite: 18]
                end
            end
        end)
        [cite_start]repeat wait() until plr.Character:FindFirstChild('HumanoidRootPart') [cite: 18]
        [cite_start]connect_AP() [cite: 18]
    end
    [cite_start]if Settings['SuperPunch'] then [cite: 18]
        [cite_start]pcall(function() [cite: 19]
            [cite_start]for _,v in next,connections_SuperPunch do [cite: 19]
                [cite_start]if typeof(v) == 'RBXScriptConnection' then [cite: 19]
                    [cite_start]v:Disconnect() [cite: 19]
                end
            end
        end)
        [cite_start]repeat wait() until plr.Character:FindFirstChild('RightHand') [cite: 20]
        [cite_start]connect_SP() [cite: 20]
    end
    [cite_start]if Settings['Virus'] then [cite: 20]
        [cite_start]pcall(function() [cite: 20]
            [cite_start]for _,v in next,connections_V do [cite: 20]
                [cite_start]if typeof(v) == 'RBXScriptConnection' then [cite: 20]
                    [cite_start]v:Disconnect() [cite: 21]
                end
            end
        end)
        [cite_start]spawn(function() [cite: 21]
            [cite_start]pcall(function() [cite: 21]
                [cite_start]repeat wait() until plr.Character:FindFirstChild('HumanoidRootPart') and plr.Character:FindFirstChildOfClass('Humanoid') [cite: 21]
                [cite_start]for _,v in next,plr.Character:GetChildren() do [cite: 21]
                    [cite_start]if v:IsA('BasePart') then [cite: 22]
                        [cite_start]infect(v) [cite: 22]
                    end
                end
            end)
        end) 
    end
end)
local function respawn()
    [cite_start]pcall(function() [cite: 23]
        [cite_start]local b = plr.PlayerGui.DeathMenu.Frame.Button.TextButton [cite: 23]
        [cite_start]b.Position = UDim2.new(0,0,0,0) [cite: 23]
        [cite_start]b.Size = UDim2.new(1,0,1,0) [cite: 23]
        [cite_start]b.Text = '' [cite: 23]
        [cite_start]b.BackgroundTransparency = 1 [cite: 23]
        [cite_start]b.ZIndex = (2^31-1) [cite: 23]
        [cite_start]local s = Instance.new('ScreenGui',game:GetService('CoreGui')) [cite: 23]
        [cite_start]b.Parent = s [cite: 23]
        [cite_start]vim:SendMouseButtonEvent(b.AbsolutePosition.X+b.AbsoluteSize.X/2,b.AbsolutePosition.Y+b.AbsoluteSize.Y/2,0,true,game,0) [cite: 23]
        [cite_start]vim:SendMouseButtonEvent(b.AbsolutePosition.X+b.AbsoluteSize.X/2,b.AbsolutePosition.Y+b.AbsoluteSize.Y/2,0,false,game,0) [cite: 23]
        [cite_start]spawn(function() [cite: 24]
            [cite_start]wait() [cite: 24]
            [cite_start]s:Destroy() [cite: 24]
        end)
    end)
end

[cite_start]local GUI = Instance.new('ScreenGui',game:GetService('CoreGui')) [cite: 24]
local function Notify(title,text,duration)
    [cite_start]local text1 = Instance.new('TextLabel',game:GetService'CoreGui') [cite: 24]
    [cite_start]text1.Size = UDim2.new(1,0,0,20) [cite: 24]
    [cite_start]text1.Position = UDim2.new(0,0,1,22) [cite: 24]
    [cite_start]text1.Text = text [cite: 24]
    text1.BackgroundColor3 = Color3.fromRGB(0,0,0) -- Changed to black
    [cite_start]text1.BackgroundTransparency = 0.3 [cite: 24]
    [cite_start]if duration and typeof(duration)=='number' then [cite: 24]
        spawn(function()
            [cite_start]wait(duration) [cite: 25]
            [cite_start]text1:Destroy() [cite: 25]
        end)
    end
end
[cite_start]local HoverTip = Instance.new('TextLabel',GUI) [cite: 25]
[cite_start]local Frame = Instance.new('Frame',GUI) [cite: 25]
[cite_start]local Open = Instance.new('TextButton',GUI) [cite: 25]
[cite_start]local Refresh = Instance.new('TextButton',GUI) [cite: 25]
[cite_start]local Respawn = Instance.new('TextButton',GUI) [cite: 25]
[cite_start]Instance.new('UICorner',Open).CornerRadius = UDim.new(0, 5) [cite: 25]
[cite_start]local Holder = Instance.new('Frame') [cite: 25]
[cite_start]GUI.Name = 'GUI' [cite: 25]
[cite_start]GUI.ZIndexBehavior = Enum.ZIndexBehavior.Sibling [cite: 25]
[cite_start]GUI.ResetOnSpawn = false [cite: 25]
Frame.BackgroundColor3 = Color3.fromRGB(0, 0, 0) -- Changed to black
[cite_start]Frame.BackgroundTransparency = 0.500 [cite: 25]
[cite_start]Frame.Position = UDim2.new(0, -200, 0.332, 0) [cite: 25]
[cite_start]Frame.Size = UDim2.new(0, 90, 0, 208) [cite: 25]
[cite_start]Frame.Visible = false [cite: 25]
[cite_start]Open.Name = "Open" [cite: 25]
Open.BackgroundColor3 = Color3.fromRGB(0, 0, 0) -- Changed to black
[cite_start]Open.BackgroundTransparency = 0.300 [cite: 25]
[cite_start]Open.Position = UDim2.new(0, 0, 0.599787831, 0) [cite: 25]
[cite_start]Open.Size = UDim2.new(0, 47, 0, 25) [cite: 25]
[cite_start]Open.Font = Enum.Font.SourceSansBold [cite: 25]
[cite_start]Open.Text = "Open" [cite: 25]
Open.TextColor3 = Color3.fromRGB(255, 255, 255) -- Changed to white for contrast
[cite_start]Open.TextScaled = true [cite: 26]
[cite_start]Open.TextSize = 14.000 [cite: 26]
[cite_start]Open.TextWrapped = true [cite: 26]
[cite_start]Holder.Name = "Holder" [cite: 26]
[cite_start]Holder.Parent = GUI [cite: 26]
Holder.BackgroundColor3 = Color3.fromRGB(0, 0, 0) -- Changed to black
[cite_start]Holder.BackgroundTransparency = 1.000 [cite: 26]
[cite_start]Holder.Position = UDim2.new(0, 180, 0.332, 0) [cite: 26]
[cite_start]Holder.Size = UDim2.new(0, 379, 0, 208) [cite: 26]
[cite_start]Refresh.Name = "Refresh" [cite: 26]
[cite_start]Refresh.AnchorPoint = Vector2.new(1,0) [cite: 26]
Refresh.BackgroundColor3 = Color3.fromRGB(0, 0, 255) -- Changed to blue
[cite_start]Refresh.Position = UDim2.new(1, 0, 0.332121223, 0) [cite: 26]
[cite_start]Refresh.Size = UDim2.new(0, 100, 0, 22) [cite: 26]
[cite_start]Refresh.Font = Enum.Font.SourceSans [cite: 26]
[cite_start]Refresh.Text = "Refresh" [cite: 26]
Refresh.TextColor3 = Color3.fromRGB(255, 255, 255) -- Changed to white for contrast
[cite_start]Refresh.TextScaled = true [cite: 26]
[cite_start]Refresh.TextSize = 14.000 [cite: 26]
[cite_start]Refresh.TextWrapped = true [cite: 26]
[cite_start]Respawn.Name = "Respawn" [cite: 26]
[cite_start]Respawn.AnchorPoint = Vector2.new(1,0) [cite: 26]
Respawn.BackgroundColor3 = Color3.fromRGB(0, 0, 255) -- Changed to blue
[cite_start]Respawn.Position = UDim2.new(1, 0, 0, Refresh.AbsolutePosition.Y+28) [cite: 26]
[cite_start]Respawn.Size = UDim2.new(0, 100, 0, 22) [cite: 26]
[cite_start]Respawn.Font = Enum.Font.SourceSans [cite: 26]
[cite_start]Respawn.Text = "Respawn" [cite: 26]
Respawn.TextColor3 = Color3.fromRGB(255, 255, 255) -- Changed to white for contrast
[cite_start]Respawn.TextScaled = true [cite: 26]
[cite_start]Respawn.TextSize = 14.000 [cite: 26]
[cite_start]Respawn.TextWrapped = true [cite: 26]
[cite_start]HoverTip.Name = 'Hover' [cite: 26]
[cite_start]HoverTip.Size = UDim2.new(0,100,0,20) [cite: 26]
[cite_start]HoverTip.Position = UDim2.new(0,0,0,0) [cite: 26]
[cite_start]HoverTip.Visible = false [cite: 27]
[cite_start]HoverTip.Text = '' [cite: 27]
[cite_start]HoverTip.ZIndex = 10 [cite: 27]
HoverTip.BackgroundColor3 = Color3.fromRGB(0,0,255) -- Changed to blue
[cite_start]local cdFrame = false [cite: 27]
Open.MouseButton1Down:Connect(function()
    [cite_start]for _,v in next,Holder:GetChildren() do [cite: 27]
        [cite_start]if v:IsA'Frame' then [cite: 27]
            [cite_start]v.Visible = false [cite: 27]
        end
    end
    [cite_start]if Frame.Visible == true and not cdFrame then [cite: 27]
        [cite_start]Open.Text = 'Open' [cite: 27]
        [cite_start]cdFrame = true [cite: 27]
        [cite_start]Frame.Position = UDim2.new(0, 0, 0.332, 0) [cite: 27]
        [cite_start]HoverTip.Visible = false [cite: 28]
        [cite_start]Frame:TweenPosition(UDim2.new(0,-100,0.332,0),Enum.EasingDirection.In,Enum.EasingStyle.Linear,0.25,true) [cite: 28]
        [cite_start]spawn(function() [cite: 28]
            [cite_start]wait(0.25) [cite: 28]
            [cite_start]cdFrame = false [cite: 28]
            [cite_start]Frame.Visible = false [cite: 28]
        end)
    [cite_start]elseif Frame.Visible == false and not cdFrame then [cite: 28]
        [cite_start]Open.Text = 'Close' [cite: 29]
        [cite_start]cdFrame = true [cite: 29]
        [cite_start]Frame.Visible = true [cite: 29]
        [cite_start]Frame.Position = UDim2.new(0, -100, 0.332, 0) [cite: 29]
        [cite_start]Frame:TweenPosition(UDim2.new(0,0,0.332,0),Enum.EasingDirection.In,Enum.EasingStyle.Linear,0.25,true) [cite: 29]
        [cite_start]spawn(function() [cite: 29]
            [cite_start]wait(0.25) [cite: 29]
            [cite_start]cdFrame = false [cite: 29]
        end)
    end
end)
Refresh.MouseButton1Up:Connect(function()
    [cite_start]pcall(function() [cite: 29]
        [cite_start]oldpos = plr.Character.HumanoidRootPart.CFrame [cite: 29]
        [cite_start]camcf = workspace.CurrentCamera.CFrame [cite: 30]
        [cite_start]respawn() [cite: 30]
        [cite_start]plr.CharacterAdded:wait() [cite: 30]
        [cite_start]repeat rs.RenderStepped:wait() until plr.Character:FindFirstChild'HumanoidRootPart' and plr.Character:FindFirstChildOfClass'Humanoid' [cite: 30]
        [cite_start]for i = 1,10 do [cite: 30]
            [cite_start]ts:Create(plr.Character.HumanoidRootPart,TweenInfo.new(0),{CFrame=oldpos}):Play() [cite: 30]
        end
        [cite_start]workspace.CurrentCamera.CFrame = camcf [cite: 30]
    end)
end)
Respawn.MouseButton1Up:Connect(function()
    [cite_start]respawn() [cite: 30]
end)
[cite_start]local lpp = 0 [cite: 30]
local function addPage(name)
    [cite_start]local Page = Instance.new('TextButton',Frame) [cite: 30]
    [cite_start]Page.Name = name [cite: 31]
    Page.BackgroundColor3 = Color3.fromRGB(0, 0, 255) -- Changed to blue
    [cite_start]Page.Position = UDim2.new(0,0,0,lpp) [cite: 31]
    [cite_start]Page.Size = UDim2.new(1, 0, 0, 22) [cite: 31]
    [cite_start]Page.Font = Enum.Font.SourceSansSemibold [cite: 31]
    [cite_start]Page.Text = name [cite: 31]
    Page.TextColor3 = Color3.fromRGB(255, 255, 255) -- Changed to white for contrast
    [cite_start]Page.TextScaled = true [cite: 31]
    [cite_start]Page.TextSize = 14.000 [cite: 31]
    [cite_start]Page.TextWrapped = true [cite: 31]
    [cite_start]lpp = lpp+28 [cite: 31]
    [cite_start]local PageFrame = Instance.new('Frame',Holder) [cite: 31]
    [cite_start]PageFrame.Name = name [cite: 31]
    PageFrame.BackgroundColor3 = Color3.fromRGB(0, 0, 0) -- Changed to black
    [cite_start]PageFrame.BackgroundTransparency = 0.5 [cite: 31]
    [cite_start]PageFrame.Size = UDim2.new(0, 409, 0, 208) [cite: 32]
    [cite_start]PageFrame.Visible = false [cite: 32]
    Page.MouseButton1Down:Connect(function()
        [cite_start]for _,v in next,Holder:GetChildren() do [cite: 32]
            [cite_start]v.Visible = false [cite: 32]
        end
        [cite_start]PageFrame.Visible = true [cite: 32]
    end)
    return PageFrame
end
[cite_start]local table = {} [cite: 32]
local function addButton(name,frame,tip)
    [cite_start]if not table[frame] then [cite: 32]
        [cite_start]table[frame] = {posX=6,posY=6} [cite: 32]
    elseif table[frame] then
        [cite_start]table[frame].posX=table[frame].posX+96 [cite: 33]
        [cite_start]if table[frame].posX>360 then [cite: 33]
            [cite_start]table[frame].posX = 6 [cite: 33]
            [cite_start]table[frame].posY=table[frame].posY+28 [cite: 33]
        end
    end
    [cite_start]local Button = Instance.new('TextButton',frame) [cite: 33]
    [cite_start]Button.Name = name [cite: 33]
    Button.BackgroundColor3 = Color3.fromRGB(0, 0, 255) -- Changed to blue
    [cite_start]Button.Position = UDim2.new(0, table[frame].posX, 0, table[frame].posY) [cite: 33]
    [cite_start]Button.Size = UDim2.new(0, 90, 0, 22) [cite: 33]
    [cite_start]Button.Font = Enum.Font.SourceSansSemibold [cite: 33]
    [cite_start]Button.Text = name [cite: 34]
    Button.TextColor3 = Color3.fromRGB(255, 255, 255) -- Changed to white for contrast
    [cite_start]Button.TextScaled = true [cite: 34]
    [cite_start]Button.TextSize = 14.000 [cite: 34]
    [cite_start]Button.TextWrapped = true [cite: 34]
    Button.MouseEnter:Connect(function()
        [cite_start]HoverTip.Visible = true [cite: 34]
        [cite_start]HoverTip.Position = UDim2.new(0,mouse.X+20,0,mouse.Y+20) [cite: 34]
        [cite_start]HoverTip.Text = tip [cite: 34]
        [cite_start]HoverTip.Size = UDim2.new(0,#tip*8,0,22) [cite: 34]
    end)
    Button.MouseLeave:Connect(function()
        [cite_start]HoverTip.Visible = false [cite: 35]
        [cite_start]HoverTip.Text = '' [cite: 35]
    end)
    return Button
end
local function addBox(name,frame,tip)
    [cite_start]if not table[frame] then [cite: 35]
        [cite_start]table[frame] = {posX=6,posY=6} [cite: 35]
    [cite_start]elseif table[frame] then [cite: 35]
        [cite_start]table[frame].posX=table[frame].posX+96 [cite: 35]
        [cite_start]if table[frame].posX>360 then [cite: 35]
            [cite_start]table[frame].posX = 6 [cite: 35]
            [cite_start]table[frame].posY=table[frame].posY+28 [cite: 35]
        end
    end
    [cite_start]local Box = Instance.new('TextBox',frame) [cite: 35]
    [cite_start]Box.Name = name [cite: 36]
    Box.BackgroundColor3 = Color3.fromRGB(0, 0, 255) -- Changed to blue
    [cite_start]Box.BackgroundTransparency = 0.500 [cite: 36]
    [cite_start]Box.Position = UDim2.new(0, table[frame].posX, 0, table[frame].posY) [cite: 36]
    [cite_start]Box.Size = UDim2.new(0, 90, 0, 22) [cite: 36]
    [cite_start]Box.Font = Enum.Font.SourceSans [cite: 36]
    [cite_start]Box.Text = name [cite: 36]
    Box.TextColor3 = Color3.fromRGB(255, 255, 255) -- Changed to white for contrast
    [cite_start]Box.TextSize = 14.000 [cite: 36]
    Box.MouseEnter:Connect(function()
        [cite_start]HoverTip.Visible = true [cite: 36]
        [cite_start]HoverTip.Position = UDim2.new(0,mouse.X+20,0,mouse.Y+20) [cite: 36]
        [cite_start]HoverTip.Text = tip [cite: 36]
        [cite_start]HoverTip.Size = UDim2.new(0,#tip*8,0,22) [cite: 37]
    end)
    Box.MouseLeave:Connect(function()
        [cite_start]HoverTip.Visible = false [cite: 37]
        [cite_start]HoverTip.Text = '' [cite: 37]
    end)
    return Box
end
[cite_start]local Main = addPage('Main') [cite: 37]
[cite_start]local Global = addPage('Global') [cite: 37]
[cite_start]local Misc = addPage('Misc') [cite: 37]
[cite_start]local UI = addPage('UI') [cite: 37]
[cite_start]local Info = addPage('Info') [cite: 37]
[cite_start]local credits = Instance.new('TextLabel',Info) [cite: 37]
[cite_start]local version = Instance.new('TextLabel',Info) [cite: 37]
[cite_start]credits.Position = UDim2.new(0,6,0,6) [cite: 37]
[cite_start]credits.Size = UDim2.new(1,-12,0,22) [cite: 37]
[cite_start]credits.Text = 'Made by KAKOYTO_LOXX and JusttChrxs' [cite: 37]
[cite_start]version.Position = UDim2.new(0,6,0,34) [cite: 37]
[cite_start]version.Size = UDim2.new(1,-12,0,22) [cite: 37]
[cite_start]version.Text = 'Version: '..Version [cite: 37]

[cite_start]local b = addButton('AntiFling: Off',Main,'Prevents your character from being flung') [cite: 37]
b.MouseButton1Down:Connect(function()
    [cite_start]Settings['AntiFling'] = not Settings['AntiFling'] [cite: 37]
    [cite_start]if Settings['AntiFling'] == true then [cite: 38]
        [cite_start]b.Text = 'AntiFling: On' [cite: 38]
        [cite_start]for _,v in next,plr.Character:GetChildren() do [cite: 38]
            [cite_start]if v.Name == 'Stabler' or v.Name == 'VelocityDamage' or v.Name == 'GetPicked' or v.Name == 'ArmAngleUpdate' or v.Name == 'ArmAngle' then [cite: 38]
                [cite_start]v:Destroy() [cite: 38]
            end
        end
    else
        [cite_start]b.Text = 'AntiFling: Off' [cite: 39]
    end
end)
[cite_start]local b0 = addButton('AntiVelocity: Off',Main,'Resets velocity') [cite: 39]
b0.MouseButton1Down:Connect(function()
    [cite_start]Settings['AntiVelocity'] = not Settings['AntiVelocity'] [cite: 39]
    [cite_start]if Settings['AntiVelocity'] == true then [cite: 39]
        [cite_start]b0.Text = 'AntiVelocity: On' [cite: 39]
    else
        [cite_start]b0.Text = 'AntiVelocity: Off' [cite: 39]
    end
end)
[cite_start]local b1 = addButton('AntiAnvil: Off',Main,'Flings anvils') [cite: 39]
b1.MouseButton1Down:Connect(function()
    [cite_start]Settings['AntiAnvil'] = not Settings['AntiAnvil'] [cite: 39]
    [cite_start]if Settings['AntiAnvil'] == true then [cite: 39]
        [cite_start]b1.Text = 'AntiAnvil: On' [cite: 39]
    else
        [cite_start]b1.Text = 'AntiAnvil: Off' [cite: 40]
    end
end)
[cite_start]local b2 = addButton('AntiPunch: Off',Main,'Prevents from getting punched') [cite: 40]
b2.MouseButton1Down:Connect(function()
    [cite_start]Settings['AntiPunch'] = not Settings['AntiPunch'] [cite: 40]
    [cite_start]if Settings['AntiPunch'] == true then [cite: 40]
        [cite_start]b2.Text = 'AntiPunch: On' [cite: 40]
        [cite_start]pcall(function() [cite: 40]
            [cite_start]plr.Character.Ragdoll:Destroy() [cite: 40]
        end)
    else
        [cite_start]b2.Text = 'AntiPunch: Off' [cite: 40]
    end
end)
[cite_start]local b3 = addButton('AntiSpinner: Off',Main,'Prevents from getting flung by spinners') [cite: 40, 41]
b3.MouseButton1Down:Connect(function()
    [cite_start]Settings['AntiSpinner'] = not Settings['AntiSpinner'] [cite: 41]
    [cite_start]if Settings['AntiSpinner'] == true then [cite: 41]
        [cite_start]b3.Text = 'AntiSpinner: On' [cite: 41]
        [cite_start]pcall(function() [cite: 41]
            [cite_start]for _,v in next,plr.Character:GetChildren() do [cite: 41]
                [cite_start]if v:IsA'BasePart' then [cite: 41]
                    [cite_start]v.CustomPhysicalProperties = prop1000 [cite: 42]
                end
            end
        end)
    else
        [cite_start]b3.Text = 'AntiSpinner: Off' [cite: 42]
        [cite_start]pcall(function() [cite: 42]
            [cite_start]for _,v in next,plr.Character:GetDescendants() do [cite: 42]
                pcall(function()
                    [cite_start]if v:IsA'BasePart' then [cite: 43]
                        [cite_start]v.CustomPhysicalProperties = PhysicalProperties.new(0.3,0.2,0,0.2,0.2) [cite: 43]
                    end
                end)
            end
        end)
    end
end)
addButton('Godmode',Main,'Gives you infinite hp (makes bald)').MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 44]
        [cite_start]for _,v in next,plr.Character:GetChildren() do [cite: 44]
            [cite_start]if v.Name == 'VelocityDamage' or v.Name == 'GetPicked' or v.Name == 'ArmAngleUpdate' then [cite: 44]
                [cite_start]v:Destroy() [cite: 44]
            end
        end
    end)
    [cite_start]pcall(function() [cite: 44]
        [cite_start]local hum = plr.Character.Humanoid [cite: 44]
        [cite_start]local cl = hum:Clone() [cite: 45]
        [cite_start]cl.Parent = plr.Character [cite: 45]
        [cite_start]hum.Parent = nil [cite: 45]
        cl:GetPropertyChangedSignal('Health'):Connect(function()
            [cite_start]if cl.Health<=0 then [cite: 45]
                [cite_start]hum.Parent = plr.Character [cite: 45]
                [cite_start]wait(1) [cite: 45]
                [cite_start]hum:Destroy() [cite: 46]
            end
        end)
        [cite_start]workspace.CurrentCamera.CameraSubject = plr.Character [cite: 46]
    end)
end)
addButton('AntiBring',Main,'Prevents from getting brought').MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 46]
        [cite_start]plr.Character.RightHand:Destroy() [cite: 46]
    end)
end)
[cite_start]local b4 = addButton('FakeAccs: Off',Main,'Prevents from getting flung') [cite: 46]
b4.MouseButton1Down:Connect(function()
    [cite_start]Settings['FakeAccs'] = not Settings['FakeAccs'] [cite: 47]
    [cite_start]if Settings['FakeAccs'] == true then [cite: 47]
        [cite_start]b4.Text = 'FakeAccs: On' [cite: 47]
        [cite_start]for _,v in next,plr.Character:GetChildren() do [cite: 47]
            [cite_start]if v:IsA'Accessory' and v:FindFirstChild'Handle' and v.Name ~= 'FakeAcc' then [cite: 47]
                [cite_start]local clone = v:Clone() [cite: 47]
                [cite_start]v:Destroy() [cite: 47]
                [cite_start]clone.Name = 'FakeAcc' [cite: 47]
                [cite_start]clone.Parent = plr.Character [cite: 47]
            end
        [cite_start]end [cite: 48]
    else
        [cite_start]b4.Text = 'FakeAccs: Off' [cite: 48]
    end
end)
[cite_start]local f1_box = addBox('Fling Player',Main,'Fling Player') [cite: 48]
f1_box.FocusLost:Connect(function()
    [cite_start]pcall(function() [cite: 48]
        [cite_start]local tar = findplr(f1_box.Text) [cite: 48]
        [cite_start]local accs = tar.Character:FindFirstChildOfClass'Accessory' [cite: 48]
        [cite_start]if accs then [cite: 48]
            [cite_start]if accs:FindFirstChild'Handle' then [cite: 48]
                [cite_start]plr.Character.Picking:FireServer(accs.Handle,Vector3.new(8.99999981e+37, -8.99999981e+37, 8.99999981e+37, 1, 0, 0, 0, 1, 0, 0, 0, 1)) [cite: 49]
                [cite_start]wait(0.1) [cite: 49]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 49]
            [cite_start]elseif accs:IsA'BasePart' then [cite: 49]
                [cite_start]plr.Character.Picking:FireServer(accs,Vector3.new(8.99999981e+37, -8.99999981e+37, 8.99999981e+37, 1, 0, 0, 0, 1, 0, 0, 0, 1)) [cite: 49]
                [cite_start]wait(0.1) [cite: 49]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 50]
            end
            [cite_start]wait(0.1) [cite: 50]
            [cite_start]plr.Character.PuttingDown:FireServer() [cite: 50]
        else
            [cite_start]plr.Character.Picking:FireServer(tar.Character.HumanoidRootPart,Vector3.new(9e37,-9e37,9e37)) [cite: 50]
            [cite_start]wait(0.1) [cite: 50]
            [cite_start]plr.Character.PuttingDown:FireServer() [cite: 50]
        end
    [cite_start]end) [cite: 51]
    [cite_start]f1_box.Text = 'Fling Player' [cite: 51]
end)
[cite_start]local lf1_box = addBox('Loop Fling',Main,'Loop fling player') [cite: 51]
lf1_box.FocusLost:Connect(function()
    [cite_start]local tar = findplr(lf1_box.Text) [cite: 51]
    [cite_start]if tar and not LoopFlingV1[tar.Name] then [cite: 51]
        [cite_start]LoopFlingV1[tar.Name] = tar [cite: 51]
    end
    [cite_start]lf1_box.Text = 'Loop Fling' [cite: 51]
end)
[cite_start]local f2_box = addBox('Fling v2',Main,'Fling player') [cite: 51]
f2_box.FocusLost:Connect(function()
    [cite_start]pcall(function() [cite: 51]
        [cite_start]findplr(f2_box.Text).Character.ArmAngleChange:FireServer(CFrame.new(math.huge,math.huge,math.huge)) [cite: 51]
    end)
    [cite_start]f2_box.Text = 'Fling v2' [cite: 51]
end)
[cite_start]local lf2_box = addBox('Loop Fling v2',Main,'Loop fling player') [cite: 51]
lf2_box.FocusLost:Connect(function()
    [cite_start]local tar = findplr(lf2_box.Text) [cite: 51]
    [cite_start]if tar and not LoopFlingV2[tar.Name] then [cite: 52]
        [cite_start]LoopFlingV2[tar.Name] = tar [cite: 52]
    end
    [cite_start]lf2_box.Text = 'Loop Fling v2' [cite: 52]
end)
addButton('Clear LoopFling',Main,'Stop loop fling').MouseButton1Down:Connect(function()
    [cite_start]LoopFlingV1 = {} [cite: 52]
    [cite_start]LoopFlingV2 = {} [cite: 52]
end)
[cite_start]local b5 = addButton('AutoPunch: Off',Main,'Equip punch tool and touch player to punch') [cite: 52]
b5.MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 52]
        [cite_start]Settings['AutoPunch'] = not Settings['AutoPunch'] [cite: 53]
        [cite_start]if Settings['AutoPunch'] == true then [cite: 53]
            [cite_start]b5.Text = 'AutoPunch: On' [cite: 53]
            [cite_start]connect_AP() [cite: 53]
        else
            [cite_start]b5.Text = 'AutoPunch: Off' [cite: 53]
            [cite_start]pcall(function() [cite: 53]
                [cite_start]for _,v in next,connections_AutoPunch do [cite: 53]
                    [cite_start]if typeof(v) == 'RBXScriptConnection' then [cite: 54]
                        [cite_start]v:Disconnect() [cite: 54]
                    end
                end
            end)
        end
    end)
end)
[cite_start]local b6 = addButton('SuperPunch: Off',Main,'Press e to punch') [cite: 54]
b6.MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 54]
        [cite_start]Settings['SuperPunch'] = not Settings['SuperPunch'] [cite: 54]
        [cite_start]if Settings['SuperPunch'] == true then [cite: 55]
            [cite_start]b6.Text = 'SuperPunch: On' [cite: 55]
            [cite_start]connect_SP() [cite: 55]
        else
            [cite_start]b6.Text = 'SuperPunch: Off' [cite: 55]
            [cite_start]pcall(function() [cite: 55]
                [cite_start]for _,v in next,connections_SuperPunch do [cite: 55]
                    [cite_start]if typeof(v) == 'RBXScriptConnection' then [cite: 56]
                        [cite_start]v:Disconnect() [cite: 56]
                    end
                end
            end)
        end
    end)
end)
[cite_start]local b7 = addButton('Virus: Off',Main,'Touch player to fling') [cite: 56]
b7.MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 57]
        [cite_start]Settings['Virus'] = not Settings['Virus'] [cite: 57]
        [cite_start]if Settings['Virus'] == true then [cite: 57]
            [cite_start]b7.Text = 'Virus: On' [cite: 57]
            [cite_start]for _,v in next,plr.Character:GetChildren() do [cite: 57]
                [cite_start]if v:IsA'BasePart' then [cite: 57]
                    [cite_start]infect(v) [cite: 57]
                [cite_start]end [cite: 58]
            end
        else
            [cite_start]b7.Text = 'Virus: Off' [cite: 58]
            [cite_start]pcall(function() [cite: 58]
                [cite_start]for _,v in next,connections_V do [cite: 58]
                    [cite_start]if typeof(v) == 'RBXScriptConnection' then [cite: 59]
                        [cite_start]v:Disconnect() [cite: 59]
                    end
                end
            end)
        end
    end)
end)
addButton('Crash Server',Global,'Crash Server').MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 59]
        [cite_start]for _,v in next,workspace.Map:GetDescendants() do [cite: 60]
            [cite_start]if v:IsA'SpawnLocation' then [cite: 60]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 60]
                [cite_start]wait(0.1) [cite: 60]
                [cite_start]plr.Character.Picking:FireServer(v,Vector3.new(9e37,-9e37,9e37)) [cite: 60]
            end
        end
    end)
end)
addButton('Crash Others',Global,'Crash Players').MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 60]
        [cite_start]if workspace:FindFirstChild'Map' and workspace.Map:FindFirstChildOfClass'Model' and workspace.Map:FindFirstChildOfClass'Model':FindFirstChild'Noob' then [cite: 61]
            [cite_start]if workspace.Map:FindFirstChildOfClass'Model'.Noob:FindFirstChild'Sword' then [cite: 61]
                [cite_start]plr.Character.Picking:FireServer(workspace.Map:FindFirstChildOfClass'Model'.Noob.Sword,Vector3.new(math.huge,-math.huge,math.huge)) [cite: 61]
                [cite_start]wait(0.1) [cite: 61]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 61]
            [cite_start]elseif workspace.Map:FindFirstChildOfClass'Model'.Noob:FindFirstChild'Handle' then [cite: 61, 62]
                [cite_start]plr.Character.Picking:FireServer(workspace.Map:FindFirstChildOfClass'Model'.Noob.Handle,Vector3.new(math.huge,-math.huge,math.huge)) [cite: 62]
                [cite_start]wait(0.1) [cite: 62]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 62]
            else
                [cite_start]Notify('CRASH OTHERS','Error! Try again later.',3) [cite: 63]
            end
        else
            [cite_start]Notify('CRASH OTHERS','Error! Try again later.',3) [cite: 63]
        end
    end)
end)
addButton('Lag Others',Global,'Lag Players (may crash players or crash server)').MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 63]
        [cite_start]for _,v in next,workspace.Map:GetDescendants() do [cite: 63]
            [cite_start]if v.Name == 'Donate' and v.Parts.Part1.Color == Color3.fromRGB(17,17,17) then [cite: 63, 64]
                [cite_start]plr.Character.Picking:FireServer(v.Detect,Vector3.new(math.huge,-math.huge,math.huge)) [cite: 64]
                [cite_start]wait(0.1) [cite: 64]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 64]
            [cite_start]elseif workspace:FindFirstChild'Map' and workspace.Map:FindFirstChildOfClass'Model' and workspace.Map:FindFirstChildOfClass'Model':FindFirstChild'Noob' and workspace.Map:FindFirstChildOfClass'Model'.Noob:FindFirstChild'Drink' then [cite: 64]
                [cite_start]plr.Character.Picking:FireServer(workspace.Map:FindFirstChildOfClass'Model'.Noob.Drink,Vector3.new(math.huge,-math.huge,math.huge)) [cite: 64]
                [cite_start]wait(0.1) [cite: 64]
                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 65]
            [cite_start]elseif v.Name == 'Donate' and v.Parts.Part1.Color ~= Color3.fromRGB(17,17,17) then [cite: 65]
                [cite_start]Notify('LAG OTHERS','Error! Try again later.',3) [cite: 66]
            end
        end
    end)
end)
addButton('SafeZone',Misc,'Teleport to safe zone').MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 66]
        [cite_start]if not workspace:FindFirstChild'SafeZone' then [cite: 66]
            [cite_start]local sp = Instance.new('Part',workspace) [cite: 66]
            [cite_start]sp.Name = 'SafeZone' [cite: 66]
            [cite_start]sp.Size = Vector3.new(500,3,500) [cite: 66]
            [cite_start]sp.CFrame = CFrame.new(2000,workspace.FallenPartsDestroyHeight+2,2000) [cite: 67]
            [cite_start]sp.Anchored = true [cite: 67]
        end
        [cite_start]plr.Character.HumanoidRootPart.CFrame = CFrame.new(2000,workspace.FallenPartsDestroyHeight+10,2000) [cite: 67]
    end)
end)
addButton('TPSpawn',Misc,'Teleport to spawn').MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 67]
        [cite_start]for _,v in next,workspace.Map:GetDescendants() do [cite: 67]
            [cite_start]if v:IsA'SpawnLocation' then [cite: 67]
                [cite_start]plr.Character.HumanoidRootPart.CFrame = v.CFrame*CFrame.new(0,5,0) [cite: 67]
            end
        [cite_start]end [cite: 68]
    end)
end)
[cite_start]local b8 = addButton('LessPing: Off',Misc,'Boost internet') [cite: 68]
b8.MouseButton1Down:Connect(function()
    [cite_start]Settings['LessPing'] = not Settings['LessPing'] [cite: 68]
    [cite_start]if Settings['LessPing'] == true then [cite: 68]
        [cite_start]b8.Text = 'LessPing: On' [cite: 68]
        [cite_start]pcall(function() [cite: 68]
            [cite_start]plr.Character.BodyFollowMouse.Disabled = true [cite: 68]
            [cite_start]plr.Character.HeadWaist:FireServer(CFrame.new(0,0.8,0),CFrame.new(0,0.2,0)) [cite: 68]
        end)
    else
        [cite_start]b8.Text = 'LessPing: Off' [cite: 69]
        [cite_start]pcall(function() [cite: 69]
            [cite_start]plr.Character.BodyFollowMouse.Disabled = false [cite: 69]
        end)
    end
end)
[cite_start]local fa_box = addBox('Fake Accessory Id',Misc,'Gives client sided accessory') [cite: 69]
fa_box.FocusLost:Connect(function()
    [cite_start]pcall(function() [cite: 69]
        [cite_start]local hat_id = tonumber(fa_box.Text) [cite: 69]
        [cite_start]local hat = game:GetObjects('rbxassetid://'..hat_id)[1] [cite: 69]
        [cite_start]plr.Character.Humanoid:AddAccessory(hat) [cite: 69]
        [cite_start]local type = hat.Handle:FindFirstChildOfClass'Attachment'.Name [cite: 69]
        [cite_start]local attachment = nil [cite: 69]
        [cite_start]for _,v in next,plr.Character:GetDescendants() do [cite: 70]
            [cite_start]if v.Name == type and v.Parent.Name ~= 'Handle' then [cite: 70]
                [cite_start]attachment = v [cite: 70]
            end
        end
        [cite_start]local weld = Instance.new('Weld',hat.Handle) [cite: 70]
        [cite_start]weld.Name = 'AccessoryWeld' [cite: 70]
        [cite_start]weld.Part0 = hat.Handle [cite: 70]
        [cite_start]weld.Part1 = attachment.Parent [cite: 71]
        [cite_start]weld.C1 = attachment.CFrame-hat.Handle:FindFirstChildOfClass'Attachment'.CFrame.p [cite: 71]
    end)
    [cite_start]fa_box.Text = 'Fake Accessory Id' [cite: 71]
end)
addButton('Legs Fling',Misc,'Removes your torso and makes you heavy').MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 71]
        [cite_start]for _,v in next,plr.Character:GetChildren() do [cite: 71]
            [cite_start]if v:IsA'BasePart' and v.Name~='HumanoidRootPart' then [cite: 71]
                [cite_start]v.Massless = true [cite: 71]
            end
        [cite_start]end [cite: 72]
        [cite_start]pcall(function() [cite: 72]
            [cite_start]plr.Character.BodyFollowMouse.Disabled = true [cite: 72]
        end)
        [cite_start]plr.Character.HeadWaist:FireServer(CFrame.new(0,9e37,-9e37),CFrame.new(0,-9e37,9e37)) [cite: 72]
    end)
end)
addButton('Big jacket',Misc,'Must have layered clothing (jacket, shirt or tshirt)').MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 72]
        [cite_start]local char = plr.Character [cite: 72]
        [cite_start]for _,v in next,char:GetChildren() do [cite: 72]
            [cite_start]if v:IsA'BasePart' and v.Name~='HumanoidRootPart' then [cite: 73]
                [cite_start]v.Massless = true [cite: 73]
            end
        end
        [cite_start]pcall(function() [cite: 73]
            [cite_start]char.BodyFollowMouse.Disabled = true [cite: 73]
        end)
        [cite_start]local old = Settings['AntiFling'] [cite: 73]
        [cite_start]Settings['AntiFling'] = false [cite: 73]
        [cite_start]char.RagdollEvent:FireServer() [cite: 73]
        [cite_start]wait() [cite: 74]
        [cite_start]char.HeadWaist:FireServer(CFrame.new(0,0,9e37),CFrame.new(0,0,9e37)) [cite: 74]
        [cite_start]wait() [cite: 74]
        [cite_start]char.HeadWaist:FireServer(CFrame.new(0,0,-9e37),CFrame.new(0,0,-9e37)) [cite: 74]
        [cite_start]wait() [cite: 74]
        [cite_start]char.GetUpEvent:FireServer() [cite: 74]
        [cite_start]Settings['AntiFling'] = old [cite: 74]
        [cite_start]wait() [cite: 74]
        [cite_start]char.HeadWaist:FireServer(CFrame.new(0,0.8,0),CFrame.new(0,0.2,0)) [cite: 74]
        [cite_start]char.Humanoid:ChangeState(Enum.HumanoidStateType.Running) [cite: 74]
        [cite_start]char.HumanoidRootPart.CFrame = char.HumanoidRootPart.CFrame+Vector3.new(0,5,0) [cite: 74]
    end)
end)
[cite_start]local dupe_box = addBox('Dupe to player',Misc,'Give duped tools to player (requires gamepass)') [cite: 75]
dupe_box.FocusLost:Connect(function(enterpressed)
    [cite_start]if enterpressed then [cite: 75]
        [cite_start]pcall(function() [cite: 75]
            [cite_start]local target = findplr(dupe_box.Text) [cite: 75]
            [cite_start]duping = target [cite: 75]
            [cite_start]while target and duping==target and duping~=nil do [cite: 75]
                [cite_start]repeat wait() until plr.Character and plr.Character:FindFirstChildOfClass'Humanoid' [cite: 75]
                [cite_start]wait(0.5) [cite: 76]
                [cite_start]local hum = plr.Character.Humanoid [cite: 76]
                [cite_start]local cl = hum:Clone() [cite: 76]
                [cite_start]cl.Parent = plr.Character [cite: 76]
                [cite_start]hum:Destroy() [cite: 76]
                [cite_start]for _,v in next,plr.Backpack:GetChildren() do [cite: 76]
                    [cite_start]if v:FindFirstChild'Handle' then [cite: 77]
                        [cite_start]v.Parent = plr.Character [cite: 77]
                        [cite_start]for i = 1,5 do [cite: 77]
                            [cite_start]firetouchinterest(v.Handle,target.Character.HumanoidRootPart,0) [cite: 77]
                            [cite_start]firetouchinterest(v.Handle,target.Character.HumanoidRootPart,1) [cite: 78]
                        end
                    end
                end
                [cite_start]respawn() [cite: 79]
                [cite_start]plr.CharacterAdded:wait() [cite: 79]
            end
        end)
    end
    [cite_start]dupe_box.Text = 'Dupe to player' [cite: 79]
end)
addButton('Stop duping',Misc,'Stop duping').MouseButton1Down:Connect(function()
    [cite_start]duping = false [cite: 79]
end)
addButton('Spam bombs',Misc,'Spam bombs (requires duped bombs)').MouseButton1Down:Connect(function()
    [cite_start]for _,v in next,plr.Backpack:GetChildren() do [cite: 79]
        [cite_start]if v.Name == 'Bomb' then [cite: 79]
            [cite_start]v.Parent = plr.Character [cite: 80]
            [cite_start]v:Activate() [cite: 80]
            [cite_start]v.Parent = plr.Backpack [cite: 80]
        end
    end
end)
addButton('Spam anvils',Misc,'Spam anvils (requires duped anvils)').MouseButton1Down:Connect(function()
    [cite_start]for _,v in next,plr.Backpack:GetChildren() do [cite: 80]
        [cite_start]if v.Name == 'Anvil' then [cite: 80]
            [cite_start]v.Parent = plr.Character [cite: 80]
            [cite_start]v:Activate() [cite: 80]
            [cite_start]v.Parent = plr.Backpack [cite: 81]
        end
    end
end)
[cite_start]local af_button = addButton('Autofarm: Off',Misc,'Autofarm') [cite: 81]
af_button.MouseButton1Down:Connect(function()
    [cite_start]Settings['Autofarm'] = not Settings['Autofarm'] [cite: 81]
    [cite_start]if Settings['Autofarm'] then [cite: 81]
        [cite_start]af_button.Text = 'Autofarm: On' [cite: 81]
        [cite_start]while Settings['Autofarm'] do [cite: 81]
            [cite_start]pcall(function() [cite: 81]
                [cite_start]local char = plr.Character [cite: 81]
                [cite_start]repeat rs.RenderStepped:wait() until plr.PlayerGui.DeathMenu.Frame.Button:FindFirstChild'TextButton' and char:FindFirstChild'HumanoidRootPart' and (plr.Backpack:FindFirstChild'Punch' or char:FindFirstChild'Punch') [cite: 82]
                [cite_start]local tool = plr.Backpack:FindFirstChild'Punch' or plr.Character:FindFirstChild'Punch' [cite: 82]
                [cite_start]tool.Parent = plr.Character [cite: 82]
                [cite_start]tool:Activate() [cite: 82]
                [cite_start]plr.Character.RagdollEvent:FireServer() [cite: 82]
                [cite_start]wait() [cite: 82]
                [cite_start]firetouchinterest(char.RightHand,char.HumanoidRootPart,0) [cite: 83]
                [cite_start]firetouchinterest(char.RightHand,char.HumanoidRootPart,1) [cite: 83]
                [cite_start]respawn() [cite: 83]
                [cite_start]spawn(function() [cite: 83]
                    pcall(function()
                        [cite_start]wait(0.5) [cite: 84]
                        [cite_start]if char then [cite: 84]
                            [cite_start]repeat respawn() wait(0.5) until not char or not char.Parent [cite: 84]
                        end
                    [cite_start]end) [cite: 85]
                end)
                [cite_start]plr.CharacterAdded:wait() [cite: 85]
            end)
        end
    else
        [cite_start]af_button.Text = 'Autofarm: Off' [cite: 85]
    end
end)
[cite_start]local trap_box = addBox('Trap player',Misc,'Traps player untill you respawn') [cite: 85]
trap_box.FocusLost:Connect(function()
    [cite_start]pcall(function() [cite: 85]
        [cite_start]local target = findplr(trap_box.Text) [cite: 86]
        [cite_start]if target and target.Character:FindFirstChild'GetPicked' and target.Character:FindFirstChild'HumanoidRootPart' then [cite: 86]
            [cite_start]plr.Character.RightHand.Anchored = true [cite: 86]
            [cite_start]plr.Character.HumanoidRootPart.Anchored = true [cite: 86]
            [cite_start]plr.Character.Picking:FireServer(target.Character.HumanoidRootPart,target.Character.HumanoidRootPart.Position) [cite: 86]
            [cite_start]plr.Character:WaitForChild('Stabler',5).Transparency = 0 [cite: 86]
            [cite_start]plr.Character.RightHand:Destroy() [cite: 86]
            [cite_start]plr.Character.HumanoidRootPart.Anchored = false [cite: 86]
        end
    [cite_start]end) [cite: 87]
    [cite_start]trap_box.Text = 'Trap player' [cite: 87]
end)
addButton('Show Ping',UI,'Show ping').MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 87]
        [cite_start]ping.Visible = not ping.Visible [cite: 87]
    end)
end)
addButton('Show Points',UI,'Show bully points').MouseButton1Down:Connect(function()
    [cite_start]pcall(function() [cite: 87]
        [cite_start]points.Visible = not points.Visible [cite: 87]
    end)
end)
pcall(function()
    [cite_start]for _,v in next,workspace.Map:GetDescendants() do [cite: 87]
        [cite_start]if v.Name == 'Donate' then [cite: 87]
            [cite_start]for _,x in next,v:GetDescendants() do [cite: 88]
                [cite_start]if x:IsA'BasePart' then [cite: 88]
                    [cite_start]x.Anchored = false [cite: 88]
                end
            end
            break
        end
    end
end)
pcall(function()
    [cite_start]for _,v in next,workspace.Map:FindFirstChildOfClass'Model'.Noob:GetDescendants() do [cite: 88]
        [cite_start]if v.Name == 'Sword' or v.Name == 'Drink' or v.Name == 'Handle' then [cite: 89, 101]
            [cite_start]v.Anchored = false [cite: 89]
        end
    end
end)
spawn(function()
    [cite_start]while true do wait(0.1) [cite: 89]
        [cite_start]spawn(function() [cite: 89]
            [cite_start]pcall(function() [cite: 89]
                [cite_start]if LoopFlingV1~={} then [cite: 89]
                    [cite_start]for _,v in next,LoopFlingV1 do [cite: 90]
                        [cite_start]pcall(function() [cite: 90]
                            [cite_start]local accs = v.Character:FindFirstChildOfClass'Accessory' [cite: 90]
                            [cite_start]if accs then [cite: 90]
                                [cite_start]if accs:FindFirstChild'Handle' then [cite: 91]
                                    [cite_start]plr.Character.Picking:FireServer(accs.Handle,Vector3.new(8.99999981e+37, -8.99999981e+37, 8.99999981e+37, 1, 0, 0, 0, 1, 0, 0, 0, 1)) [cite: 91]
                                [cite_start]elseif accs:IsA'BasePart' then [cite: 92]
                                    [cite_start]plr.Character.Picking:FireServer(accs,Vector3.new(8.99999981e+37, -8.99999981e+37, 8.99999981e+37, 1, 0, 0, 0, 1, 0, 0, 0, 1)) [cite: 92]
                                end
                                [cite_start]wait(0.1) [cite: 93]
                                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 93]
                            else
                                [cite_start]plr.Character.Picking:FireServer(v.Character.HumanoidRootPart,Vector3.new(8.99999981e+37, -8.99999981e+37, 8.99999981e+37, 1, 0, 0, 0, 1, 0, 0, 0, 1)) [cite: 94]
                                [cite_start]wait(0.1) [cite: 94]
                                [cite_start]plr.Character.PuttingDown:FireServer() [cite: 94]
                            [cite_start]end [cite: 95]
                        end)
                    end
                end
            end)
        end)
        [cite_start]spawn(function() [cite: 96]
            [cite_start]pcall(function() [cite: 96]
                [cite_start]if LoopFlingV2~={} then [cite: 96]
                    [cite_start]for _,v in next,LoopFlingV2 do [cite: 96]
                        pcall(function()
                            [cite_start]v.Character.ArmAngleChange:FireServer(CFrame.new(8.99999981e+37, -8.99999981e+37, 8.99999981e+37, 1, 0, 0, 0, 1, 0, 0, 0, 1)) [cite: 97]
                        end)
                    end
                end
            end)
        [cite_start]end) [cite: 98]
    end
end)
workspace.DescendantAdded:Connect(function(v)
    [cite_start]pcall(function() [cite: 98]
        [cite_start]if Settings['AntiFling'] then [cite: 98]
            [cite_start]if v.Name=='Stabler' and v.Parent~=plr.Character then [cite: 98]
                [cite_start]v:Destroy() [cite: 98]
            end
        end
        [cite_start]if Settings['AntiSpinner'] and v:IsA('Model') and plrs:GetPlayerFromCharacter(v) and v~=plr.Character then [cite: 98]
            [cite_start]for _,x in next,v:GetChildren() do [cite: 99]
                [cite_start]if x:IsA('BasePart') then [cite: 99]
                    [cite_start]v.Massless = true [cite: 99]
                end
            end
        end
        [cite_start]if v.Name == 'Donate' then [cite: 99]
            [cite_start]for _,x in next,v:GetDescendants() do [cite: 100]
                [cite_start]if x:IsA'BasePart' then [cite: 100]
                    [cite_start]x.Anchored = false [cite: 100]
                end
            end
        end
        [cite_start]if v.Name == 'Sword' or v.Name == 'Drink' or v.Name == 'Handle' then [cite: 101]
            [cite_start]v.Anchored = false [cite: 101]
        end
    end)
end)
spawn(function()
    [cite_start]while true do rs.RenderStepped:wait() [cite: 101]
        [cite_start]if Settings['AntiVelocity'] then [cite: 101]
            [cite_start]pcall(function() [cite: 101]
                [cite_start]plr.Character.RagdollDetect:Destroy() [cite: 101]
            end)
            [cite_start]pcall(function() [cite: 102]
                [cite_start]if plr.Character.HumanoidRootPart.Velocity.X>=30 or plr.Character.HumanoidRootPart.Velocity.X<=-30 or plr.Character.HumanoidRootPart.Velocity.Y>=100 or plr.Character.HumanoidRootPart.Velocity.Z>=30 or plr.Character.HumanoidRootPart.Velocity.Z<=-30 then [cite: 102]
                    [cite_start]plr.Character.HumanoidRootPart.Velocity = vec0 [cite: 102]
                end
                [cite_start]if plr.Character.HumanoidRootPart.RotVelocity.magnitude>100 then [cite: 102]
                    [cite_start]plr.Character.HumanoidRootPart.RotVelocity = vec0 [cite: 103]
                end
            end)
        end
        [cite_start]if Settings['AntiPunch'] then [cite: 103]
            [cite_start]pcall(function() [cite: 103]
                [cite_start]plr.Character.Ragdoll:Destroy() [cite: 103]
            end)
        end
        [cite_start]if Settings['FakeAccs'] then [cite: 104]
            [cite_start]for _,v in next,plr.Character:GetChildren() do [cite: 104]
                [cite_start]if v:IsA'Accessory' and v:FindFirstChild'Handle' and v.Name ~= 'FakeAcc' then [cite: 104]
                    [cite_start]local clone = v:Clone() [cite: 104]
                    [cite_start]v:Destroy() [cite: 104]
                    [cite_start]clone.Name = 'FakeAcc' [cite: 105]
                    [cite_start]clone.Parent = plr.Character [cite: 105]
                end
            end
        end
        [cite_start]if Settings['AntiFling'] then [cite: 105]
            [cite_start]pcall(function() [cite: 105]
                [cite_start]if plr.Character.Ragdoll.Value then [cite: 106]
                    [cite_start]plr.Character.GetUpEvent:FireServer() [cite: 106]
                end
            end)
            [cite_start]for _,v in next,plr.Character:GetChildren() do [cite: 106]
                [cite_start]if v.Name == 'Stabler' or v.Name == 'VelocityDamage' or v.Name == 'GetPicked' or v.Name == 'ArmAngleUpdate' or v.Name == 'ArmAngle' then [cite: 107]
                    [cite_start]v:Destroy() [cite: 107]
                end
            end
        end
        [cite_start]if Settings['AntiAnvil'] then [cite: 107]
            [cite_start]for _,v in next,plrs:GetPlayers() do [cite: 107]
                [cite_start]pcall(function() [cite: 108]
                    [cite_start]if v.Character:FindFirstChild'Anvil' then [cite: 108]
                        [cite_start]v.Character.Anvil.send:FireServer(v.Character.HumanoidRootPart.CFrame.p+Vector3.new(0,10,0)) [cite: 108]
                    end
                end)
            [cite_start]end [cite: 109]
        end
    end
end)
plr.CharacterAdded:Connect(function()
    [cite_start]pcall(function() [cite: 109]
        [cite_start]if Settings['AntiSpinner'] then [cite: 109]
            [cite_start]repeat wait() until plr.Character:FindFirstChild'HumanoidRootPart' and plr.Character:FindFirstChild'Head' [cite: 109]
            [cite_start]for _,v in next,plr.Character:GetChildren() do [cite: 109]
                [cite_start]if v:IsA'BasePart' then [cite: 109]
                    [cite_start]v.CustomPhysicalProperties = prop1000 [cite: 110]
                end
            end
        end
        [cite_start]if Settings['LessPing'] then [cite: 110]
            [cite_start]spawn(function() [cite: 110]
                [cite_start]pcall(function() [cite: 110]
                    [cite_start]repeat rs.RenderStepped:wait() until plr.Character:FindFirstChild'BodyFollowMouse' and plr.Character:FindFirstChild'HeadWaist' [cite: 111]
                    [cite_start]plr.Character.BodyFollowMouse.Disabled = true [cite: 111]
                    [cite_start]plr.Character.HeadWaist:FireServer(CFrame.new(0,0.8,0),CFrame.new(0,0.2,0)) [cite: 111]
                end)
            end)
        end
    end)
end)
Notify('Script Loaded!','Script made by KAKOYTO_LOXX and JusttChrxs\nKeybinds:\nv - Fling things\nq - Pick up things',5)
