<img width="608" height="273" alt="image" src="https://github.com/user-attachments/assets/9af01f2f-1d7a-46a1-98ef-263e1a2c3c50" />


## 📦 Installation

Follow these steps to install the program:

1. Clone the repository:
   ```sh
   git clone https://github.com/Yaasosu/yasofetch
   ```

2. Navigate into the project directory:
   ```sh
   cd yasofetch
   ```

3. Make the install script executable:
   ```sh
   chmod +x install.sh
   ```

4. Run the install script (may require root privileges):
   ```sh
   ./install.sh
   # or
   sudo ./install.sh
   ```

5. Done — the program is now installed!
(can be bug with logo)

---
> ### ⚠️ Warning
> There may be issues with some **init systems** (e.g. `sysvinit`, `s6`) and certain **distributions** (e.g. Manjaro).
> On affected systems, you may need to **compile the fetch manually**.
> Some bugs are possible on unsupported configurations.
---

## ⚙️ Available Functions

| Function | Description |
|---|---|
| `get_names` | Displays your machine's hostname |
| `get_distro` | Displays the name of your Linux distribution |
| `get_kernel` | Displays the kernel version |
| `get_desktop` | Displays the desktop environment or window manager in use |
| `get_init_system` | Displays the name of the init system |
| `packetManagerDefinder` | Displays your package manager and total package count *(Snap and Flatpak are not supported)* |
| `get_uptime` | Displays time elapsed since the system was last booted |
| `get_ram` | Displays used RAM / total RAM |
| `get_gpu` | Displays the GPU model |
| `get_cpu` | Displays the CPU model |
| `get_space` | Displays free disk space / total disk space |
| `get_session` | Displays whether the session is Wayland or X11 |

---

## 🗂 Project Structure

```
src/
├── main.c                    # Custom output and display logic
├── system_info.c             # System information retrieval
└── packetManagerDefinder.c   # Package manager and package count info

inc/
└── distro_arts.h             # Distro logos and color customization
```
---

