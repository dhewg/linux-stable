# Linux for the TP-Link VX830v - xDSL board (EcoNet EN751627)

This is the downstream kernel v3.18.21 for the TP-Link VX830v - xDSL board (EcoNet EN751627).

Sources are taken from [this vendor GPL drop](https://static.tp-link.com/upload/gpl-code/2026/202607/20260724/VX830vITWIND_GPL.tar.gz).

## Goals

- Modify the vendor firmware for the xDSL board in a non-destructive way (no need to flash it)
- Replace its kernel with your own to enable debug output and enable login over serial
- Keep binary compatibility for the vendor binary kernel modules
- Embed the vendor squashfs rootfs as initramfs (allows rootfs changes without flashing)
- Single file TFTP upload

## Howto

### Prepare the busybox replacement

The vendor busybox has a very limited feature set. To get e.g. `telnetd` we need to build our own replacement.

To build userland binaries we need to use the vendor toolchain, so our binaries are binary compatible to the shipped `libc`.

You can find it under `VX830v_GPL/bba_3_0_platform/sdk/en7516/mips-linux-uclibc-4.6.3-kernel3.18.tgz` in the GPL vendor drop.

- Download a busybox source tarball, v1.38.0 as of this writing, and extract it
- Start with the vendor busybox config

  `cp /somedir/VX830v_GPL/bba_3_0_platform/platform/build/model/VX830v/EU1/remote_board/remote_board_profile/busybox.config .config`
- Configure it

  `ARCH=mips LD_LIBRARY_PATH=/somedir/mips-linux-uclibc-4.6.3-kernel3.18/usr/lib CROSS_COMPILE=/somedir/mips-linux-uclibc-4.6.3-kernel3.18/usr/bin/mips-buildroot-linux-uclibc- make config`
  
  Note that some features will fail to compile and/or link
- Build and install it

  Same command as above, but replace `config` with `install`
- The installed tree will be located in the `_install` directory

### Prepare the rootfs

  - Download the [firmware](https://static.tp-link.com/upload/firmware/2026/202610/20261013/VX800v(DE)v1_0.21.0_Build%20260908.zip)
  - Extract it according to [these docs](https://github.com/hitech95/openwrt_tplink_vx830v_rbctrl-dsl/tree/master/fwextract)
  - Extract the squashfs image using `binwalk -e remote_board.bin` (remove the extracted squashfs contents, device nodes will be missing)
  - As root (due to devices nodes):
    ```
    umask 022
    unsquashfs _remote_board.bin.extracted/1B4CCA.squashfs
    cd squashfs-root
    ln -s bin/busybox init
    rm etc
    ln -s usr/etc etc
    cp -r /somedir/busybox-1.38.0/_install/* .
    find . -print0 | cpio -ov0H newc > ../remote_board.cpio
    ```

  We finally have a `remote_board.cpio` rootfs to embed into kernel as initramfs.

### Build the kernel

- Build or grab a usable toolchain, [like this binary one from bootlin](https://toolchains.bootlin.com/downloads/releases/toolchains/mips32/tarballs/mips32--uclibc--stable-2017.05-toolchains-1-1.tar.bz2)
- Use the vendor kernel config
  `cp kernel_config .config`
- Configure your kernel

  `ARCH=mips CROSS_COMPILE=/somedir/mips32--uclibc--stable/bin/mips-buildroot-linux-uclibc- make nconfig`
  - Under `TP-LINK Configure` disable `disable UART` (`CONFIG_TP_DISABLE_UART`)
  - Under `Kernel hacking` / `printk and dmesg options` enable `Show timing information on printks` (`CONFIG_PRINTK_TIME`)
  - Under `General setup` enable `Initial RAM filesystem and RAM disk (initramfs/initrd) support` and set `Initramfs source file(s)` to the path to `remote_board.cpio` (`CONFIG_INITRAMFS_SOURCE`)
- Build the kernel

  Same command as above, but remove `nconfig`

  The kernel with its embedded rootfs will be available as `arch/mips/boot/vmlinux.bin`.

## Load the kernel

- Get OpenWrt including the packages `curl` (enabling TFTP support) and `telnet-bsd` [running](https://github.com/openwrt/openwrt/pull/24108) on the main MediaTek Filogic (arm64)
- Connect serial to the `EN7516` pins
- Power up the board and hit any key to interrupt the boot process
- Let the main arm64 board boot up and ssh in
- Transfer the kernel to the main board:

  `scp -O arch/mips/boot/vmlinux.bin root@hostname:/tmp`
- Give the switch port `lan0` an IP, the xDSL board will have the IP 192.168.1.1:

  `ip a add 192.168.1.2/24 dev lan0`
- Upload the kernel to the bootloader on the xDSL board:

  `curl -T /tmp/vmlinux.bin tftp://192.168.1.1`
- Once the upload is done, the bootloader on the xDSL board will display an error. Ignore it, the binary is loaded in RAM
- Enter the bootloader command `jump 80020000` and hit return to boot it up

Your should see the usual kernel output. Eventually it will give you a login prompt over serial. Log in using `admin` / `1234`.

[Boot log](https://pastebin.com/raw/BzPqBUP6)

## Gaining remote access

On the xDSL serial shell:
- Give the switch port `eth0.1` an IP:

  `ip a add 192.168.1.1/24 dev eth0.1`
- Start the busybox telnet daemon:

  `telnetd`

On the ssh connection to the main board:
- Give the switch port `lan0` an IP:

  `ip a add 192.168.1.2/24 dev lan0`
- Login over telnet using `admin` / `1234`:
   ```
   telnet 192.168.1.1
   Trying 192.168.1.1...
    Connected to 192.168.1.1.
    Escape character is '^]'.
    (none) login: admin
    Password:
    ~ # head -n 1 /proc/cpuinfo
    system type             : EcoNet EN751627 SOC
   ```

Happy Hacking!
