#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

# COMPONENT_DIRS := $(PROJECT_PATH)/components $(COMPONENT_DIRS) $(IDF_PATH)/components $(PROJECT_PATH)/main $(PROJECT_PATH)/main/modules
# COMPONENT_DIRS := $(PROJECT_PATH)/components $(EXTRA_COMPONENT_DIRS) $(IDF_PATH)/components $(PROJECT_PATH)/main $(IDF_PATH)/KairOS
ifdef CONFIG_KAIROS_BASE_ON_BMP180 
COMPONENT_DIRS += $(PROJECT_PATH)/main/modules/bmp180
endif

ifdef CONFIG_KAIROS_BASE_ON_BMX280 
COMPONENT_DIRS += $(PROJECT_PATH)/main/modules/bmx280
endif

ifdef CONFIG_KAIROS_BASE_ON_DS1307
COMPONENT_DIRS += $(PROJECT_PATH)/main/modules/ds1307
endif

ifdef CONFIG_KAIROS_BASE_ON_HMC5883L
COMPONENT_DIRS += $(PROJECT_PATH)/main/modules/hmc5883l
endif

ifdef CONFIG_KAIROS_BASE_ON_i2cdev
COMPONENT_DIRS += $(PROJECT_PATH)/main/modules/i2cdev
endif

ifdef CONFIG_KAIROS_BASE_ON_MAX30100
COMPONENT_DIRS += $(PROJECT_PATH)/main/modules/max30100
endif

EXTRA_COMPONENT_DIRS += modules/sh1106

COMPONENT_ADD_INCLUDEDIRS := .

