# On Windows:

Invoke-WebRequest -Uri https://downloads.arduino.cc/arduino-cli/arduino-cli_latest_Windows_64bit.zip -OutFile arduino-cli.zip
Expand-Archive arduino-cli.zip -DestinationPath $env:LOCALAPPDATA\ArduinoCLI -Force
setx PATH "$($env:LOCALAPPDATA)\ArduinoCLI;$env:PATH"
arduino-cli version
arduino-cli config init
arduino-cli config add board_manager.additional_urls https://espressif.github.io/arduino-esp32/package_esp32_index.json
arduino-cli core update-index
arduino-cli core install arduino:esp32

## Upload

arduino-cli upload --fqbn arduino:esp32:nano_nora -p COM3 --input-file '\\wsl$\Ubuntu-24.04\home\gabriel\dev\codex\education\2025\99_IoT\binaryCounter\build\arduino.esp32.nano_nora\binaryCounter.ino.bin'

# On WSL:

curl -fsSL https://downloads.arduino.cc/arduino-cli/arduino-cli_1.3.1_Linux_64bit.tar.gz | sudo tar -xz -C /usr/local/bin arduino-cli
arduino-cli version

arduino-cli config init
arduino-cli config add board_manager.additional_urls https://espressif.github.io/arduino-esp32/package_esp32_index.json
arduino-cli core update-index
arduino-cli core install arduino:esp32

## Compile

arduino-cli compile
