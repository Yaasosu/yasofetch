#!/bin/bash

# Stop the script if any errors occur
set -e

APP_NAME="yasofetch"
INSTALL_DIR="$HOME/.local/share/$APP_NAME"
BIN_DIR="$HOME/.local/bin"
MAIN_SCRIPT="yasofetch.py" # Ensure your main code is saved under this exact name

echo "========================================"
echo "    Starting Yasofetch installation...  "
echo "========================================"

# --- 1. Detect OS distribution and install system dependencies ---
echo "[*] Detecting OS distribution..."

if [ -f /etc/os-release ]; then
    . /etc/os-release
    DISTRO=$ID
elif [ "$(uname)" == "FreeBSD" ] || [ "$(uname)" == "OpenBSD" ]; then
    DISTRO=$(uname | tr '[:upper:]' '[:lower:]')
else
    DISTRO="unknown"
fi

# Group package managers using logical "OR" (|)
case $DISTRO in
    debian|ubuntu|linuxmint|pop|kali|elementary|zorin|deepin|mx)
        echo "[*] Debian/Ubuntu-based system detected. Using apt..."
        sudo apt update
        sudo apt install -y python3 python3-venv python3-pip pciutils
        ;;
    arch|manjaro|artix|endeavouros|garuda)
        echo "[*] Arch-based system detected. Using pacman..."
        sudo pacman -Sy --noconfirm python python-pip pciutils
        ;;
    fedora|centos|rhel)
        echo "[*] RHEL/Fedora system detected. Using dnf..."
        sudo dnf install -y python3 python3-pip pciutils
        ;;
    opensuse*|suse)
        echo "[*] openSUSE detected. Using zypper..."
        sudo zypper install -y python3 python3-pip pciutils
        ;;
    alpine)
        echo "[*] Alpine Linux detected. Using apk..."
        sudo apk add python3 py3-pip pciutils
        ;;
    gentoo)
        echo "[*] Gentoo detected. Using emerge..."
        sudo emerge --ask=n dev-lang/python sys-apps/pciutils
        ;;
    void)
        echo "[*] Void Linux detected. Using xbps..."
        sudo xbps-install -Sy python3 python3-pip pciutils
        ;;
    solus)
        echo "[*] Solus detected. Using eopkg..."
        sudo eopkg install -y python3 pciutils
        ;;
    freebsd|openbsd)
        echo "[*] BSD system detected. Using pkg..."
        sudo pkg install -y python3 pciutils
        ;;
    *)
        echo "[!] Could not automatically determine the package manager for $DISTRO."
        echo "[!] Please ensure python3, python3-venv, and pciutils (lspci) are installed manually."
        ;;
esac

# --- 2. Prepare directories and copy files ---
echo "[*] Creating directories in $INSTALL_DIR..."
mkdir -p "$INSTALL_DIR"
mkdir -p "$BIN_DIR"

echo "[*] Copying source code files..."
if [ ! -f "$MAIN_SCRIPT" ]; then
    echo "[Error] The main file $MAIN_SCRIPT was not found in the current directory!"
    exit 1
fi

cp *.py "$INSTALL_DIR/"

# If requirements.txt doesn't exist, create it on the fly with known libraries
if [ -f "requirements.txt" ]; then
    cp requirements.txt "$INSTALL_DIR/"
else
    echo "[*] requirements.txt not found, generating a basic one..."
    echo "distro" > "$INSTALL_DIR/requirements.txt"
    echo "psutil" >> "$INSTALL_DIR/requirements.txt"
    echo "uptime" >> "$INSTALL_DIR/requirements.txt"
fi

# --- 3. Create venv and install Python libraries ---
echo "[*] Creating virtual environment (venv)..."
python3 -m venv "$INSTALL_DIR/venv"

echo "[*] Installing libraries from requirements.txt..."
"$INSTALL_DIR/venv/bin/pip" install -r "$INSTALL_DIR/requirements.txt"

# --- 4. Create the global command (Wrapper) ---
echo "[*] Creating the executable wrapper for $APP_NAME..."
WRAPPER_SCRIPT="$BIN_DIR/$APP_NAME"

cat << EOF > "$WRAPPER_SCRIPT"
#!/bin/bash
# Run Python from the isolated venv and pass all arguments
"$INSTALL_DIR/venv/bin/python" "$INSTALL_DIR/$MAIN_SCRIPT" "\$@"
EOF

chmod +x "$WRAPPER_SCRIPT"

echo "========================================"
echo " Installation successfully completed! 🚀"
echo "========================================"
echo "You can now run the program by simply typing in your terminal:"
echo "  $APP_NAME"
echo ""
echo "(If the command is not found, make sure ~/.local/bin is added to your \$PATH)"
