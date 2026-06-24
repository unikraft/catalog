# PowerShell module auto-discovery doesn't work on Unikraft's cpiofs,
# so we explicitly import the module that provides Write-Host.
Import-Module "$PSHome/Modules/Microsoft.PowerShell.Utility/Microsoft.PowerShell.Utility.psd1"

Write-Host "Hello, World! From PowerShell on Hyperlight!"
