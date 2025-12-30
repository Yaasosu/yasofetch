import distro
import socket
import os
import psutil
from uptime import uptime
import subprocess
import shutil

#will be remade in the future update btw :D
art = [
    "      /\\        ",
    "     /  \\       ",
    "    /    \\      ",
    "   /      \\     ",
    "  /   ,,   \\    ",
    " /   |  |   \\   ",
    "/_-''    ''-_\\  "
]



#processor
command = 'cat /proc/cpuinfo | grep "model name" | cut -f 2 -d ":"'
result = os.popen(command).read().strip()

#gpu
output = subprocess.check_output("lspci | grep -i 'vga\\|3d'", shell=True, text=True)
gpu_name = output.split('[')[1].split(']')[0]

#uptime block
seconds_uptime = uptime()
days = int(seconds_uptime // 86400)
hours = int((seconds_uptime % 86400) // 3600)
minutes = int((seconds_uptime % 3600) // 60)

##package
package_managers = {
        "dpkg": "dpkg-query -f '${binary:Package}\n' -W", # Debian, Ubuntu, Kali, Mint
        "rpm": "rpm -qa",                                  # RHEL, CentOS, Fedora, OpenSUSE
        "pacman": "pacman -Q",                             # Arch Linux, Manjaro
        "apk": "apk info",                                 # Alpine Linux
        "dnf": "dnf list installed",                       # Modern RHEL/Fedora (fallback if rpm missing)
        "emerge": "qlist -I",                              # Gentoo
        "zypper": "zypper se --installed-only",            # OpenSUSE (fallback if rpm missing)
        "xbps-query": "xbps-query -l"                      # Void Linux
    }

pckg_count = 0
name_command = "unknown"

for manager, command in package_managers.items():
    if shutil.which(manager):
        output = subprocess.check_output(command, shell=True, text=True)
        lines = [line for line in output.splitlines() if line.strip()]
        pckg_count = len(lines)
        name_command = manager
        break

##ram
ram_bytes = psutil.virtual_memory().total #bytes
ram_gygabytes = round(ram_bytes / (1024**3), 2)
ram_used_gb = round(psutil.virtual_memory().used / (1024**3), 2)

#uptime
uptime_str = f"{minutes}m" if days == 0 and hours == 0 else f"{hours}h, {minutes}m" if days == 0 else f"{days}d, {hours}h, {minutes}m"

output_msg = (
    f""
    f"{art[0]} os:     {distro.name()} \n"
    f"{art[1]} host:   {socket.gethostname()} \n"
    f"{art[2]} gpu:    {gpu_name}\n"
    f"{art[3]} cpu:    {result.split('\n')[0].strip()} \n"
    f"{art[4]} uptime: {uptime_str} \n"
    f"{art[5]} pkgs:   {pckg_count} {name_command} \n"
    f"{art[6]} ram:    {ram_used_gb}gb / {ram_gygabytes}gb \n"
    f""

    #Kernel: {platform.uname().release}"
)
print(output_msg)