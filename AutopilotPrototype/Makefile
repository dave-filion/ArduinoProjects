PROJECT_DIR       = $(shell dirname $(shell pwd))

### ARDMK_DIR
### Path to the Arduino-Makefile directory.
ARDMK_DIR         = $(HOME)/.arduino_mk

### ARDUINO_DIR
### Path to the Arduino application and resources directory.
ARDUINO_DIR       = $(HOME)/.arduino_ide

BOARD_TAG         = uno
BOARD_SUB         = uno

MONITOR_PORT      = /dev/ttyACM*

MONITOR_BAUDRATE  = 9600

### USER_LIB_PATH
### Path to where the your project's libraries are stored.
USER_LIB_PATH     :=  $(PROJECT_DIR)/lib

### path to Arduino.mk, inside the ARDMK_DIR, don't touch.
include $(ARDMK_DIR)/Arduino.mk

