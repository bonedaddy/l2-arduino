#! /bin/bash

# installs dependencies


# examples: https://github.com/HelTecAutomation/Heltec_ESP32
# api reference: https://github.com/HelTecAutomation/Heltec_ESP32#api-reference

sudo apt install python-pip
pip install pyserial
sudo usermod -aG dialout $(whoami)