
# VPNator
*VPNator* is a program which automatically selects a random ProtonVPN config file.

## Installation
To install **VPNator**, first git clone this repository with `$ git clone https://github.com/d3vboi/VPNator.git`.
Then go to [Protonvpn downloads](https://account.protonvpn.com/downloads) to download as many OpenVPN config files as you'd like.
After you've downloaded the config files, move them to their respective **nl**, **us**, and **jp** folders in this directory.
Then you need to append the line `auth-user-pass $HOME/.config/vpnator/.pass` to each config file, this is easily done with the **append_pass_conf.sh** script.
Now just run the **install.sh** script, and copy/paste the *OpenVPN* username/password found at [your ProtonVPN account](https://account.protonvpn.com/account).

## Usage
To use **VPNator**, simply run the command:
`$ vpnator -c <nl/us/jp>`

### Credits
This program was written by [d3vboi](https://github.com/d3vboi).
