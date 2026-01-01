<img width="888" height="336" alt="image" src="https://github.com/user-attachments/assets/0f0d7f14-763d-4919-9b7f-b33566ed41aa" />
<img width="554" height="172" alt="image" src="https://github.com/user-attachments/assets/2dcffbb3-8ca5-4078-8871-7066cacd8a20" />

# yasofetch
Advantages:

      Supports custom painting (just add it in Distro_logo or remake something)
      
      Easy syntax (you can easily add what you want, or remove it depending on your needs)
      
      Code has comments, and it will be easy to figure out how the code works

Disadvantages:

      Code poorest
      
      Small list of distros
      
      There may be bugs with the color scheme
## Installation (auto)
      
      curl -fsSL https://raw.githubusercontent.com/Yaasosu/yasofetch/main/install.sh | sh
      or
      wget -qO- https://raw.githubusercontent.com/Yaasosu/yasofetch/main/install.sh | sh

What if i have "PEP 668: externally-managed-environment"
it is mean that you don't have some library

      python3 -m pip install --user distro psutil uptime

### Installation (manually)

1) Clone the repository
2) cd yasofetch

3) chmod +x yasofetch.py distro_logo.py
   
after that it is depend on your shell
      
      nano ~/.bashrc (for bash)
      
      nano ~/.zshrc (zsh)
      
      nano ~/.config/fish/config.fish (fish)

4) add this line: alias yasofetch='python ~/path/to/yasofetch.py'

That's all! after that you can type `yasofetch` (my example):

```text
      /\           yaso@EndeavourOS
     //  \\        os:     EndeavourOS
    //    \ \      gpu:    GeForce GTX 980 Ti
   / /      _) )   cpu:    AMD Ryzen 5 5600 6-Core Processor
  /_/___-- __-     uptime: 40m
  /____--          pkgs:   1441 pacman
                   ram:    6.05gb / 31.26gb (19%)
