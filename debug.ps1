if (Test-Path ".\build") {  
  Write-Host "Build folder already exists"
}
else {
  New-Item "build" -ItemType Directory
  Write-Host "Build folder created successfully"
}
Set-Location build
cmake ..
cmake --build .
./Debug/fyi-app.exe
Set-Location ..