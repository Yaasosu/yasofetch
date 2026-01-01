import distro
import os
import psutil
from uptime import uptime
import subprocess
import shutil
import distro_logo

# The logo is automatically detected based on your distro. You can:
# - Change the distro name to update the logo
# - Add your own custom logo by creating a new entry in the distro_logo dictionary

##collor
class Colors:
    # Basic colors
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    MAGENTA = '\033[95m'
    CYAN = '\033[96m'
    WHITE = '\033[97m'

    # Bright colors
    BRIGHT_RED = '\033[91m'
    BRIGHT_GREEN = '\033[92m'
    BRIGHT_YELLOW = '\033[93m'
    BRIGHT_BLUE = '\033[94m'
    BRIGHT_MAGENTA = '\033[95m'
    BRIGHT_CYAN = '\033[96m'

    # Style
    BOLD = '\033[1m'
    RESET = '\033[0m'


# Color scheme for different distros
DISTRO_COLORS = {
    'ubuntu': Colors.BRIGHT_RED,
    'debian': Colors.RED,
    'arch': Colors.CYAN,
    'manjaro': Colors.GREEN,
    'fedora': Colors.BLUE,
    'centos': Colors.MAGENTA,
    'opensuse': Colors.GREEN,
    'mint': Colors.GREEN,
    'pop': Colors.CYAN,
    'kali': Colors.BLUE,
    'gentoo': Colors.MAGENTA,
    'void': Colors.GREEN,
    'nixos': Colors.BLUE,
    'elementary': Colors.CYAN,
    'endeavouros': Colors.MAGENTA,
    'alpine': Colors.BLUE,
    'artix': Colors.CYAN,
    'linuxmint': Colors.GREEN,
    'slackware': Colors.BLUE,
    'freebsd': Colors.RED,
    'openbsd': Colors.YELLOW,
    'mx': Colors.BLUE,
    'solus': Colors.BLUE,
    'garuda': Colors.BRIGHT_BLUE,
    'zorin': Colors.BLUE,
    'deepin': Colors.CYAN,
}

# The logo is automatically detected based on your distro

distro_id = str(distro.id()).lower() #here change "distro.id()" to name which you wanna see
art = distro_logo.DISTRO_ARTS[distro_id]
logo_color = DISTRO_COLORS.get(distro_id, Colors.CYAN)


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
ram_procent = round((ram_used_gb * 100) / ram_gygabytes)

#uptime
uptime_str = f"{minutes}m" if days == 0 and hours == 0 else f"{hours}h, {minutes}m" if days == 0 else f"{days}d, {hours}h, {minutes}m"

#shell
user_shell = os.environ.get('SHELL')

#WM (DE)
WM = os.environ.get('XDG_CURRENT_DESKTOP')


output_msg = (
    f""
    f"{logo_color}{art[0]}{Colors.RESET} {Colors.BOLD}{Colors.CYAN}{os.getenv('USER')}{Colors.WHITE}@{Colors.CYAN}{distro.name()}{Colors.RESET}\n"
    f"{logo_color}{art[1]}{Colors.RESET} {Colors.BOLD}{Colors.BLUE}os:{Colors.RESET}     {distro.name()}\n"
    f"{logo_color}{art[2]}{Colors.RESET} {Colors.BOLD}{Colors.BLUE}gpu:{Colors.RESET}    {gpu_name}\n"
    f"{logo_color}{art[3]}{Colors.RESET} {Colors.BOLD}{Colors.BLUE}cpu:{Colors.RESET}    {result.split(chr(10))[0].strip()}\n"
    f"{logo_color}{art[4]}{Colors.RESET} {Colors.BOLD}{Colors.BLUE}uptime:{Colors.RESET} {uptime_str}\n"
    f"{logo_color}{art[5]}{Colors.RESET} {Colors.BOLD}{Colors.BLUE}pkgs:{Colors.RESET}   {pckg_count} {name_command}{Colors.RESET}\n"
    f"{logo_color}{art[6]}{Colors.RESET} {Colors.BOLD}{Colors.BLUE}ram:{Colors.RESET}    {ram_used_gb}gb{Colors.RESET} / {ram_gygabytes}gb ({Colors.YELLOW}{ram_procent}%)\n"

    #here is the additional thing, which you can print
    #Kernel: {platform.uname().release}"
    #host:   {socket.gethostname()}
    #shell:  {os.path.basename(user_shell)}
    #WM:     {WM}
)

print(output_msg)