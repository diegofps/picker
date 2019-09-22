# Installing

```
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

```
Power off;./system-shutdown.svg;P;shutdown -h now
Restart;./system-reboot.svg;R;shutdown -r now
Exit user;./system-log-out.svg;E;logout
Lock;./system-lock-screen.svg;L;i3lock -c 000000
Hibernate;./system-suspend-hibernate.svg;H;systemctl hibernate
Sleep;./system-suspend.svg;S;systemctl suspend
```

# Run

```
picker -actions ~/.local/wespa/picker/system.picker -cols 7 -iconSize 64
```

