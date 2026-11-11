#
# Makefile for USB Core files and filesystem
#

usbcore-y := usb.o ecnt_core.o usbphy.o hub.o hcd.o urb.o message.o driver.o
usbcore-y += config.o file.o buffer.o sysfs.o endpoint.o
usbcore-y += devio.o notify.o generic.o quirks.o devices.o
usbcore-y += port.o

ifeq ($(strip $(TCSUPPORT_MUH_TEST)),)
ifeq ($(strip $(TCSUPPORT_CPU_EN7580)),)
ifeq ($(strip $(TCSUPPORT_CPU_EN7528)),)
usbcore-$(CONFIG_PCI)		+= hcd-pci.o
endif
endif
endif
usbcore-$(CONFIG_ACPI)		+= usb-acpi.o

obj-$(CONFIG_USB)		+= usbcore.o
