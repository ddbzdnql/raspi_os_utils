# Shaoze's Raspian OS Util Scripts

## Tl;DR
This directory contains a list of scripts that help improving different functionalities of the Raspberry PI OS.

## Entries
- **Carousel**

  `carousel/` contains the script that enables the OS to periodically change wallpaper from a selected folder.
- `my_startup.sh` 

  This is the entry point for adding an util into the list of start up scripts.

  The actual config for auto start is located at `/etc/xdg/autostart/my_startup.desktop`, which is symlinked in `ref/my_startup.desktop`.

## Tips
The section contains useful tips I found out when programming the utils.

- **Aliasing**

  The command to do so is `alias my_alias="ls -a"`. To have an alias work on startup of a terminal, simply place the alias in `~/.bashrc`.

  - *Aliasing in fish*

    When using the fish shell, the bare aliases in `~/.bashrc` will not be picked up. Instead, we can create a file `~/.bash_alias` for all aliases and `source` it in the config file of `fish`, located at `~/.config/fish/config.fish`. Both files symlinked in `ref`.

- **Apps on Startup**

  There are three ways to launch an app automatically on startup:

  1. Using bare scripts and `/etc/init.d`, see [instructions online](https://gist.github.com/drmalex07/298ab26c06ecf401f66c).
  2. Using `sudo crontab -e` with `@reboot` flag, see [instructions online](https://phoenixnap.com/kb/crontab-reboot).
  3. Using Desktop Manager by adding a `.desktop` file in `/etc/xdg/autostart`. See `ref/my_startup.desktop` for a sample config file.

- **High-Level OS Interaction**

  Actions such as changing the wallpaper of the desktop etc., can be achieved through [PC Man File Manager](https://en.wikipedia.org/wiki/PCMan_File_Manager) that comes out-of-the-box with `LxDE`. The `carousel` util uses `pcmanfm --set-wallpaper=` to change the wallpaper periodically. See `man pcmanfm` for more utilities.