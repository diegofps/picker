# Installing

```bash
git clone https://github.com/diegofps/picker.git
cd picker
mkdir build
cd -set PREFIX=/usr/local/bin build
qmake ..
make
strip ./picker
cp ./picker ~/.local/bin/picker
```

# Configuration Example

```csv
Power off;./system-shutdown.svg;P;shutdown -h now
Restart;./system-reboot.svg;R;shutdown -r now
Exit user;./system-log-out.svg;E;logout
Lock;./system-lock-screen.svg;L;i3lock -c 000000
Hibernate;./system-suspend-hibernate.svg;H;systemctl hibernate
Sleep;./system-suspend.svg;S;systemctl suspend
```

# Run

```bash
# minimal usage
picker -actions ~/.local/wespa/picker/system.picker 

# Setting the number of columns (default=5) and icon size (default=64)
picker -actions ~/.local/wespa/picker/system.picker -cols 7 -iconSize 32

# Fullscreen with system background
picker -actions ~/.local/wespa/picker/system.picker -fullscreen

# Fullscreen with solid background color (ARGB format)
picker -actions ~/.local/wespa/picker/system.picker -fullscreen ff222222
```

# Create a shortcut to easily launch it

In i3wm, edit the file ''~/.config/i3/config'' and add the following:

```
bindsym $mod+F12 exec "picker -actions ~/.local/wespa/picker/system/system.picker -cols 7 -fullscreen"
```
