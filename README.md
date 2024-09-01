# Esphome components

These are my own Esphome components I use in my home automation.

## Benq
This component is used to control a Benq video-projector via its serial connection.
This has been tested with the TH575 model.
The list of supported commands can be found in the video-projector manual.

This module has been inspired by this other project: https://github.com/ebfio/esphome-v7050i.
Although it works well, custom components are now deprecated in favor of External Components.

### Requirements
You will need the following:
- An Esphome compatible board
- A UART to RS232 converter (if not included on your board)
- A compatible video-projector ;-)

### Sample configuration
Refer to [the benq example](esphome/example_benq.yaml).
